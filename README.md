# Retinaface CPP

包含使用MNN、NCNN部署的代码  
包含编译好的linux x86_64(ubuntu20.04)平台下的ncnn、MNN、opencv库，可以直接编译测试,需要修改makefile中的路径  
包含一个模型可以检测动漫卡通人物的人脸


编译和测试  
在ubuntu 20.04上进行编译和测试  
```
make Retinaface_NCNN
./Retinaface_NCNN test_carton.list

make Retinaface_MNN
./Retinaface_MNN test_carton.list
```

## 增加NDK构建脚本和andrid armv7a库 
可以构建android下的c++可执行程序，ncnn、MNN、opencv库采用ndk-19r编译，api-leval为21

## add python api use pybind11
```shell
g++ -std=c++11 -O3 -shared -fPIC  $(python3 -m pybind11 --includes) -I/usr/include/python3.8m py_retina.cpp -I./ -L./ -ldetect_ncnn -o retinacarton$(python3-config --extension-suffix)
```


## reference 
https://github.com/biubug6/Pytorch_Retinaface       
https://github.com/Tencent/ncnn   
https://github.com/alibaba/MNN  
https://github.com/daquexian/onnx-simplifier
