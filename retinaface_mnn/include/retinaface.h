#include <MNN/ImageProcess.hpp>
#include <MNN/Interpreter.hpp>
#include <memory>
#include <iostream>
#include <vector>
#include <math.h>
#include "opencv2/opencv.hpp"
#include "opencv2/highgui.hpp"

using namespace std;

struct FaceObject {
    cv::Rect_<float> rect;
    float prob;
};

struct Anchor{
	float cx;
	float cy;
	float s_kx;
	float s_ky;
};


class RetinaFace {
  public:
    RetinaFace ();
    int Initial(std::string model_path);
    ~RetinaFace();
    int DetectFace(cv::Mat img,vector<FaceObject> &faces);

  private:
    MNN::Interpreter *net_ = nullptr;
    MNN::Session *session_ = nullptr;
    MNN::CV::ImageProcess::Config preProcessConfig_;
    
    MNN::Tensor* input_;
    MNN::Tensor* loc_;
    MNN::Tensor* cls_;
    vector<Anchor> Anchors_;
    int width_;
    int height_;
    float mean_vals_[3];
    float conf_;
    int top_k_;  
};