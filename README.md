# Retinaface NCNN

包含编译好的linux x86_64平台下的ncnn、opencv静态库，可以直接编译测试  
包含两个模型retiface_pig、retinaface_carton，一个检测猪脸，一个检测动漫卡通人物的人脸
可以通过retinaface.cpp中代码进行配置，修改下面的代码即可
```
std::string parampath = model_path + "/retiface_pig.param";
std::string binpath = model_path + "/retiface_pig.bin";

ncnn::Mat score_blob, bbox_blob;
ex.extract("output0", bbox_blob); 
//ex.extract("486", score_blob);  //选择retiface_carton模型时，使用该语句
ex.extract("543", score_blob);    //选择retinaface_pig模型时，使用该语句

```

编译和测试
```
make 
./Retinaface test_carton.list
```

## reference 
https://github.com/biubug6/Pytorch_Retinaface       
https://github.com/Tencent/ncnn   
https://github.com/daquexian/onnx-simplifier