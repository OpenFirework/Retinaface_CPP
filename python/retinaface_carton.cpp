#include "retinaface_carton.h"
#include "retinaface.h"

RetinaFaceCarton::RetinaFaceCarton() {
  if(handle == nullptr) {
    handle = new RetinaFace();
  }
}

RetinaFaceCarton::~RetinaFaceCarton() {
  if(handle == nullptr) {
    //delete handle;
    delete ((RetinaFace*)handle);
  }
}


int RetinaFaceCarton::Initial(std::string model_path) {
  return ((RetinaFace*)handle)->Initial(model_path);
}


 std::vector<face_rect> RetinaFaceCarton::DetectFace(unsigned char *bgr_buffer, int width, int height) {
 
   cv::Mat bgr(height, width, CV_8UC3, bgr_buffer);
   vector<FaceObject> infaces;
   int ret = ((RetinaFace*)handle)->DetectFace(bgr,infaces);
   
   std::vector<face_rect> faces;
   for (int i=0;i<infaces.size();i++) {
      face_rect face;
      face.x = infaces[i].rect.x;
      face.y = infaces[i].rect.y;
      face.w = infaces[i].rect.width;
      face.h = infaces[i].rect.height;
      face.score = infaces[i].prob;
      faces.push_back(face);
    }
   
   infaces.clear();
   return faces;
}
