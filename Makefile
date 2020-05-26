CXX := g++
CC := gcc

INCLUDE_DIRS := linux_x86_64/ncnn/include ./include 
LIB_DIRS := linux_x86_64/ncnn/lib 
LINK_LIBS = ncnn 

export PKG_CONFIG_PATH:=/home/sky/projects/Retinaface_NCNN/linux_x86_64/opencv-3.4.7/lib/pkgconfig

COMMON_FLAGS += $(foreach includedir,$(INCLUDE_DIRS),-I$(includedir))
COMMON_FLAGS += -fopenmp -std=c++11 
CFLAGS += `pkg-config --cflags opencv`

LD_FLAGS += $(foreach libdir,$(LIB_DIRS),-L$(libdir)) $(foreach library,$(LINK_LIBS),-l$(library))
LDFLAGS += `pkg-config --libs opencv` 

LD_FLAGS += ${LDFLAGS}
COMMON_FLAGS += ${CFLAGS}
TARGETS := RetinaFace
SRCS = ./src/retinaface.cpp main.cpp

$(TARGETS):$(SRCS)
	$(CXX) $(COMMON_FLAGS) $(SRCS) -o $(TARGETS) $(LD_FLAGS)
