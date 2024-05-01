//
// Created by lozpeng on 2024/1/30.
//
#pragma once

#include "jni/jni.hpp"
#include<jni.h>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <opencv2/calib3d/calib3d.hpp>


namespace ani{
    namespace android{
        namespace util
        {
            class CvImageUtil{
            public:
                static bool bitMap2cvMatrix(JNIEnv* ,jobject ,cv::Mat&);
                static bool cvMatrix2Bitmap(JNIEnv *, cv::Mat& , jobject& );
            };
        }
    }
}