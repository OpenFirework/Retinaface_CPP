#include "retinaface.h"

#include <string.h>
#include <errno.h>
#include <string>
#include <vector>
#include <sys/time.h>

int32_t NowMicros() {
    struct timeval tv;
    gettimeofday(&tv,nullptr);
    return static_cast<int32_t>(tv.tv_sec)*1000+tv.tv_usec/1000;
}

float intersection_area(const FaceObject& a, const FaceObject& b) {
    cv::Rect_<float> inter = a.rect & b.rect;
    return inter.area();
}

void generate_anchors(int height,int width,vector<Anchor> &Anchors) {
  int steps[3] = {8,16,32};
	int min_sizes[3][2] = {{16,32},{64,128},{256,512}};
	int feature_maps[3][2] = {0};
	for(int i=0;i<3;i++) {
		feature_maps[i][0] = ceil(height*1.0/steps[i]);  
		feature_maps[i][1] = ceil(width*1.0/steps[i]);   
	}
  Anchors.clear();
  for(int i=0;i<3;i++) {
		int *min_size =  min_sizes[i];
    for(int id_y=0;id_y<feature_maps[i][0];id_y++) {
			for(int id_x=0;id_x<feature_maps[i][1];id_x++)
				for(int k = 0;k<2;k++) {
					float s_kx = min_size[k]*1.0/width;
					float s_ky = min_size[k]*1.0/height;
					float dense_cx = (id_x + 0.5)*steps[i]/width;
					float dense_cy = (id_y + 0.5)*steps[i]/height;
					Anchor a;
					a.cx = dense_cx;
					a.cy = dense_cy;
					a.s_kx = s_kx;
					a.s_ky = s_ky;
					Anchors.push_back(a);
				}
		}
  }
}

void decode(float *loc,vector<Anchor> &Anchors, float *out_loc, int width, int height) {
  float variance[2] = {0.1,0.2};
  for (int q=0; q<1; q++) {
    for (int y=0; y<16800; y++) {
      out_loc[y*4] = Anchors[y].cx + loc[0]*variance[0]*Anchors[y].s_kx;
      out_loc[y*4+1] = Anchors[y].cy + loc[1]*variance[0]*Anchors[y].s_ky;

      out_loc[y*4+2] = (Anchors[y].s_kx*exp(loc[2]*variance[1]))*width;  //width
      out_loc[y*4+3] = (Anchors[y].s_ky*exp(loc[3]*variance[1]))*height;  //height
      out_loc[y*4] = out_loc[y*4]*width - out_loc[y*4+2]/2;          //x0
      out_loc[y*4+1] = out_loc[y*4+1]*height - out_loc[y*4+3]/2;      //y0
      loc += 4;
    }
  }
}

void nms_sorted_bboxes(const std::vector<FaceObject>& faceobjects, std::vector<int>& picked, float nms_threshold) {
  picked.clear();
  const int n = faceobjects.size();
  vector<float> areas(n);
  for (int i = 0; i < n; i++) {
    areas[i] = faceobjects[i].rect.area();
  }
  for (int i = 0; i < n; i++) {
    const FaceObject& a = faceobjects[i];
    int keep = 1;
    for (int j = 0; j < (int)picked.size(); j++) {
      const FaceObject& b = faceobjects[picked[j]];
      // intersection over union
      float inter_area = intersection_area(a, b);
      float union_area = areas[i] + areas[picked[j]] - inter_area;
      //float IoU = inter_area / union_area
      if (inter_area / union_area > nms_threshold)
        keep = 0;
    }
    if (keep)
      picked.push_back(i);
  }

}

bool FaceLargerScore(FaceObject  a, FaceObject b) {
  if ( a.prob > b.prob) {
    return true;
  } else {
    return false;
  }
}

RetinaFace::RetinaFace() {
  width_ = 640;
  height_ = 640;
  mean_vals_[0] = 104.0f;
  mean_vals_[1] = 117.0f;
  mean_vals_[2] = 123.0f;
  conf_ = 0.7;
  top_k_ = 100;
  generate_anchors(width_,height_,Anchors_);
}

RetinaFace::~RetinaFace() {
  if(net_ != nullptr) {
    net_->releaseModel();
    net_->releaseSession(sess_facenet_);
  }
  Anchors_.clear();
}

int RetinaFace::Initial(std::string model_path) {
  std::string modelpath = model_path + "icarton_re18.mnn";
  net_ = MNN::Interpreter::createFromFile(modelpath.c_str());
  MNN::ScheduleConfig netConfig;
  netConfig.type      = MNN_FORWARD_CPU;
  netConfig.numThread = 4;
  session_ = net_->createSession(netConfig);
  input_ = net_->getSessionInput(session_, "input0");
 
  net_->resizeTensor(input_, {1, 3, width_, height_});
  net_->resizeSession(session_);
  
  cls_ = net_->getSessionOutput(session_, "486");
  loc_ = net_->getSessionOutput(session_, "output0");
  ::memcpy(preProcessConfig_.mean, mean_vals_, sizeof(mean_vals_));
  preProcessConfig_.sourceFormat = MNN::CV::BGR;
  preProcessConfig_.destFormat = MNN::CV::BGR;
  return 0;
}


int RetinaFace::DetectFace(const cv::Mat img,vector<FaceObject> &faces) {
  //先pad将图像填补为正方形,pre-process
  
  cv::Mat pad_img;
  int long_size = max(img.cols,img.rows);
  if (long_size == img.cols) {
    int top = (long_size - img.rows)/2;
    int bottom = long_size - top - img.rows;
    cv::copyMakeBorder(img,pad_img,top,bottom,0,0,cv::BORDER_CONSTANT,0);
  } else {
    int left = (long_size - img.cols)/2;
    int right = long_size - left - img.cols;
    cv::copyMakeBorder(img,pad_img,0,0,left,right,cv::BORDER_CONSTANT,0);
  }
  //pad为正方形后，再resize为模型的固定输入大小（640,640）
  cv::Mat bgr;
  cv::resize(pad_img,bgr,cv::Size(width_,height_));
  net_->resizeTensor(input_, {1, 3, width_, height_});
  net_->resizeSession(session_);
  //mnn 输入
  MNN::CV::ImageProcess *pretreat_ = MNN::CV::ImageProcess::create(preProcessConfig_);
  pretreat_->convert(bgr.data, width_, height_, bgr.step[0], input_);
  net_->runSession(session_);
  
  MNN::Tensor clsHost(cls_, MNN::Tensor::CAFFE);
  MNN::Tensor locHost(loc_, MNN::Tensor::CAFFE);

  cls_->copyToHostTensor(&clsHost);
  loc_->copyToHostTensor(&locHost);
  
  std::vector<int> shape0 = clsHost.shape();
  std::vector<int> shape1 = locHost.shape();
  int c = shape0[0];
  int length = shape0[1];
  float *out_loc = new float[length*4];
  auto cls_data = clsHost.host<float>();
  auto loc_data = locHost.host<float>();

  decode(loc_data, Anchors_, out_loc, width_, height_);

  
  vector<FaceObject> tempfaces;
  //将大于阈值的框存进temfaces，准备下一步的nms
  for (int q=0; q<c; q++) {
    for (int y=0; y<length;y++) {
        if(cls_data[2*y+1] > conf_) {
          FaceObject face;
          face.prob = cls_data[2*y+1];
          face.rect.x = out_loc[4*y];
          face.rect.y = out_loc[4*y+1];
          face.rect.width = out_loc[4*y+2];
          face.rect.height = out_loc[4*y+3];
          tempfaces.push_back(face);
        }
    }
  }
  //根据分数排序，保留top_k
  std::sort(tempfaces.begin(), tempfaces.end(),FaceLargerScore);
  if (tempfaces.size() > top_k_)
    tempfaces.resize(top_k_);
  
  //执行nms
  std::vector<int> picked;
  int start = NowMicros();
  nms_sorted_bboxes(tempfaces, picked, 0.4);
  int end = NowMicros();
  std::cout<<"nms:"<<(end-start)<<"ms"<<std::endl;
  //上面的操作是在640×640的图片上做的（先pad图片到正方形，再resize到640*640)
  //因此下面的操作是将检测框，反映射回到原图像的尺寸
  float scale = long_size*1.0/width_; //width_与height_相等

  for (int i = 0; i < picked.size(); i++) {
    FaceObject face = tempfaces[picked[i]];
    //反映射回pad_img
    int real_x = face.rect.x*scale;
    int real_y = face.rect.y*scale;
    int real_width = face.rect.width*scale;
    int real_height = face.rect.height*scale;
    
    //反映射回实际原图尺寸
    real_x = real_x - (long_size - img.cols)/2;
    real_y = real_y - (long_size - img.rows)/2;

    //如果检测框超出了原始图像的边界，则将检测框拉回边界
    real_x = (real_x > 0) ? real_x :0;
    real_y = (real_y > 0) ? real_y :0;
    real_width = ((real_x + real_width) < img.cols ) ? real_width : (img.cols - real_x);
    real_height = ((real_y + real_height) < img.rows ) ? real_height : (img.rows - real_y);

    face.rect.x = real_x;
    face.rect.y = real_y;
    face.rect.width = real_width;
    face.rect.height = real_height;
    faces.push_back(face);
 } 
 return 0;
}
