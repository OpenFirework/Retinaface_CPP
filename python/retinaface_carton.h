#include <iostream>
#include <vector>
#include <string>

typedef struct face_rect_{
    int x;
    int y;
    int w;
    int h;
    float score;
    // int getx() { return x; }
    // int gety() { return y; }
    // int getw() { return w; }
    // int geth() { return h; }
    // float getscore { return score; }
}face_rect;

class RetinaFaceCarton {
  public:
  
    RetinaFaceCarton ();
    
    int Initial(std::string model_path);
    
    ~RetinaFaceCarton();
    
    std::vector<face_rect> DetectFace(unsigned char *bgr_buffer, int width, int height);
    
    
  private:
    void *handle = nullptr;
};

