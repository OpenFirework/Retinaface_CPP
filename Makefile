CXX := g++
CC := gcc

NCNN_INCLUDE_DIRS := linux_x86_64/ncnn/include ./retinaface_ncnn/include 
NCNN_LIB_DIRS := linux_x86_64/ncnn/lib 
NCNN_LINK_LIBS = ncnn 

MNN_INCLUDE_DIRS := linux_x86_64/mnn/include ./retinaface_mnn/include 
MNN_LIB_DIRS := linux_x86_64/mnn/lib 
MNN_LINK_LIBS = MNN 

export PKG_CONFIG_PATH:=/home/sky/projects/Retinaface_NCNN/linux_x86_64/opencv-3.4.7/lib/pkgconfig

NCNN_COMMON_FLAGS += $(foreach includedir,$(NCNN_INCLUDE_DIRS),-I$(includedir))
MNN_COMMON_FLAGS += $(foreach includedir,$(MNN_INCLUDE_DIRS),-I$(includedir))
COMMON_FLAGS += -fopenmp -std=c++11 
COMMON_FLAGS += `pkg-config --cflags opencv`

NCNN_LD_FLAGS += $(foreach libdir,$(NCNN_LIB_DIRS),-L$(libdir)) $(foreach library,$(NCNN_LINK_LIBS),-l$(library))
MNN_LD_FLAGS += $(foreach libdir,$(MNN_LIB_DIRS),-L$(libdir)) $(foreach library,$(MNN_LINK_LIBS),-l$(library))
MNN_LD_FLAGS += -Wl,-rpath,$(MNN_LIB_DIRS)
COMMON_LDFLAGS += `pkg-config --libs opencv` 

LD_FLAGS += ${LDFLAGS}
COMMON_FLAGS += ${CFLAGS}
NCNN_TARGETS := RetinaFace_NCNN
NCNN_SRCS = ./retinaface_ncnn/src/retinaface.cpp main.cpp

MNN_TARGETS := RetinaFace_MNN
MNN_SRCS = ./retinaface_mnn/src/retinaface.cpp main.cpp

$(NCNN_TARGETS):$(NCNN_SRCS)
	$(CXX) $(NCNN_COMMON_FLAGS) $(COMMON_FLAGS) $(NCNN_SRCS) -o $(NCNN_TARGETS) $(NCNN_LD_FLAGS) $(COMMON_LDFLAGS)
$(MNN_TARGETS):$(NCNN_SRCS)
	$(CXX) $(MNN_COMMON_FLAGS) $(COMMON_FLAGS) $(MNN_SRCS) -o $(MNN_TARGETS) $(MNN_LD_FLAGS) $(COMMON_LDFLAGS)
