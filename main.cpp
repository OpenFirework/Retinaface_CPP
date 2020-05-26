#include "retinaface.h"

#include <stdio.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>
 
int32_t NowMicros();

//判断目录是否存在
int IsFolderExist(const char* path) {
  DIR *dp;
  if ((dp = opendir(path)) == NULL) {
    return 0;
  }
  closedir(dp);
  return -1;
}
//判断文件是否存在
int IsFileExist(const char* path) {
    return !access(path, F_OK);
}

//从一个文件列表的文本文件中，获取文件路径
int GetFilePathList(const std::string &list_file_path,
                    std::vector<std::string>* lists_vec,
                    const std::string &item_root_path=std::string("")) {
  FILE* fp = fopen(list_file_path.c_str(), "r");
  if (fp == NULL) {
    printf("ERROR: open file failed\n");
    return -1;
  }
  char filename[512];
  memset(filename, 0, 512);
  while (fscanf(fp, "%s", filename) != EOF) {
    std::string path = item_root_path + std::string(filename);
    lists_vec->push_back(path);
    memset(filename, 0, 512);
  }
  return 0;
}


int main(int argc, char** argv) {
  
  RetinaFace facedetect;
  string modelpath = "models/";  //model path
  facedetect.Initial(modelpath); 
  string results_path = "test_results/";  //result path
  string test_file = argv[1];
  std::vector<std::string> list_test_vec;

  GetFilePathList(test_file, &list_test_vec);
  if (IsFolderExist(results_path.c_str())== 0) {
    mkdir(results_path.c_str(),S_IRWXU|S_IRWXO);   //create result path
  }

  //process each image
  for (int i=0;i<list_test_vec.size();i++) {
    cv::Mat bgr;
    std::cout<<"test "<<i<<"/"<<list_test_vec.size()<<std::endl;
    int pos = list_test_vec[i].rfind('/');
    string filename = list_test_vec[i].substr(pos+1,list_test_vec[i].length()-pos);
    bgr = cv::imread(list_test_vec[i]);
    vector<FaceObject> faces;
    int start = NowMicros();
    facedetect.DetectFace(bgr,faces);
    int end = NowMicros();
    std::cout<<"all spend:"<<(end-start)<<"ms"<<std::endl;
    for (int i=0;i<faces.size();i++) {
      FaceObject face = faces[i];
      cv::rectangle(bgr, cv::Point(face.rect.x, face.rect.y),
      cv::Point(face.rect.x + face.rect.width, face.rect.y + face.rect.height),
      cv::Scalar(0, 255, 0), 2);
      string score = to_string(face.prob);
      cv::putText(bgr, score, cv::Point(face.rect.x, face.rect.y),cv::FONT_HERSHEY_DUPLEX, 0.6, (0, 255, 255));
    }
    string save_name = results_path + filename;
    cv::imwrite(save_name.c_str(),bgr);
  }

  // cv::Mat bgr;
  // string file = "pig.jpg";
  // bgr = cv::imread(file);
  // vector<FaceObject> faces;
  // facedetect.DetectFace(bgr,faces);

  // for (int i=0;i<faces.size();i++) {
  //   FaceObject face = faces[i];
  //   cv::rectangle(bgr, cv::Point(face.rect.x, face.rect.y),
	// 	cv::Point(face.rect.x + face.rect.width, face.rect.y + face.rect.height),
	// 	cv::Scalar(0, 255, 0), 2);
  //   string score = to_string(face.prob);
  //   cv::putText(bgr, score, cv::Point(face.rect.x, face.rect.y),cv::FONT_HERSHEY_DUPLEX, 0.8, (0, 255, 255));
  // }
  // cv::imwrite("results.jpg",bgr);
}
