# Copyright (C) 2009 The Android Open Source Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
LOCAL_PATH := $(call my-dir)


include $(CLEAR_VARS)
LOCAL_MODULE := opencv_world
LOCAL_SRC_FILES := $(LOCAL_PATH)/../../armv7a/opencv-3.4.7/lib/libopencv_world.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := libpng
LOCAL_SRC_FILES := $(LOCAL_PATH)/../../armv7a/opencv-3.4.7/lib/liblibpng.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := libjpeg-turbo
LOCAL_SRC_FILES := $(LOCAL_PATH)/../../armv7a/opencv-3.4.7/lib/liblibjpeg-turbo.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := zlib
LOCAL_SRC_FILES := $(LOCAL_PATH)/../../armv7a/opencv-3.4.7/lib/libzlib.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := libjasper
LOCAL_SRC_FILES := $(LOCAL_PATH)/../../armv7a/opencv-3.4.7/lib/liblibjasper.a 
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := ncnn
LOCAL_SRC_FILES := $(LOCAL_PATH)/../../armv7a/ncnn-0413/lib/libncnn.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := omp
LOCAL_SRC_FILES := $(LOCAL_PATH)/../../armv7a/ncnn-0413/lib/libomp.a
include $(PREBUILT_STATIC_LIBRARY)

#include $(CLEAR_VARS)
#LOCAL_MODULE := MNN
#LOCAL_SRC_FILES := $(LOCAL_PATH)/../../armv7a/MNN-1.0.0/lib/libMNN.so
#include $(PREBUILT_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := facedetect
LOCAL_ARM_MODE := arm
TARGET_ARCH_ABI := armeabi-v7a
LOCAL_ARM_NEON := true 
LOCAL_CPPFLAGS += -std=c++11 -O3 -fPIC \
                  -DANDROID -marm -mfpu=neon -march=armv7-a 

LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../armv7a/ncnn-0413/include \
		    $(LOCAL_PATH)/../../armv7a/opencv-3.4.7/include \
                   $(LOCAL_PATH)/../../include \
                   $(LOCAL_PATH)/../../retinaface_ncnn/include 
                   

LOCAL_SRC_FILES := $(LOCAL_PATH)/../../retinaface_ncnn/src/retinaface.cpp 

include $(BUILD_STATIC_LIBRARY)


include $(CLEAR_VARS)
LOCAL_ARM_MODE := arm
TARGET_ARCH_ABI := armeabi-v7a
LOCAL_ARM_NEON := true
LOCAL_ALLOW_UNDEFINED_SYMBOLS := true
LOCAL_PRELINK_MODULE :=false  

LOCAL_CPPFLAGS += -std=c++11 -O3 -fPIC \
                  -DANDROID -marm -mfpu=neon -march=armv7-a \
                  -Wl,--no-warn-mismatch -llog -ldl \
		   -fvisibility=hidden -fvisibility-inlines-hidden \
                  -fomit-frame-pointer -fstrict-aliasing -ffunction-sections -fdata-sections -ffast-math
LOCAL_LDFLAGS += -fuse-ld=bfd -fPIC \
                  -DANDROID -marm -mfpu=neon -mfloat-abi=hard -march=armv7-a \
                  -Wl,--no-warn-mismatch -llog -ldl -lstdc++ 

LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../armv7a/ncnn-0413/include \
		    $(LOCAL_PATH)/../../armv7a/MNN-1.0.0/include \
		    $(LOCAL_PATH)/../../retinaface_ncnn/include \
		    $(LOCAL_PATH)/../../armv7a/opencv-3.4.7/include \
            $(LOCAL_PATH)/../../include 
                  

LOCAL_MODULE := test_retinaface

LOCAL_SRC_FILES := ../../main.cpp
LOCAL_WHOLE_STATIC_LIBRARIES += ncnn opencv_world


LOCAL_STATIC_LIBRARIES +=  ncnn omp \
			    opencv_world libjasper libpng \
			    libjpeg-turbo zlib facedetect

include $(BUILD_EXECUTABLE)


