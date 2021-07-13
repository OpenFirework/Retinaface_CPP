#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "retinaface_carton.h"
#include <vector>

namespace py = pybind11;

class PyRetinaFaceCarton{
    public:
    PyRetinaFaceCarton() {
        if(handle == nullptr) {
            handle = new RetinaFaceCarton;
        }
    }

     
    int Initial(std::string model_path) {
        return handle->Initial(model_path);
    }
    
    ~PyRetinaFaceCarton() {
        if(handle != nullptr) {
            delete handle;
        }
    }
    
    std::vector<face_rect> DetectFace(py::buffer b, int width, int height) {
        std::vector<face_rect> faces = handle->DetectFace((unsigned char *)(b.request().ptr), width, height);
        return faces;
    }
    

    RetinaFaceCarton *handle = nullptr;
};

PYBIND11_MODULE(retinacarton, m) {
    m.doc() = "pybind11 example plugin"; // optional module docstring

    py::class_<face_rect>(m, "face_rect")
    .def(py::init<>())
    .def_readwrite("x",&face_rect::x)
    .def_readwrite("y",&face_rect::y)
    .def_readwrite("w",&face_rect::w)
    .def_readwrite("h",&face_rect::h)
    .def_readwrite("score",&face_rect::score)
    .def("__repr__",
        [](const face_rect &a) {
            return std::to_string(a.x)+","+std::to_string(a.y) +","+std::to_string(a.w)+","+std::to_string(a.h)+","+std::to_string(a.score)+"\n";;
        });

    py::class_<PyRetinaFaceCarton>(m, "PyRetinaFaceCarton")
    .def(py::init<>())
    .def("Initial", &PyRetinaFaceCarton::Initial)
    .def("DetectFace", &PyRetinaFaceCarton::DetectFace);
}
