//
// Created by lozpeng on 2024/1/30.
//

#pragma once

#include "ndkcamera.h"
#include <android/asset_manager_jni.h>
#include <android/native_window_jni.h>
#include <android/native_window.h>

#include <android/bitmap.h>
#include <android/log.h>

#include <platform.h>
#include <benchmark.h>


#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <opencv2/calib3d/calib3d.hpp>

#if __ARM_NEON
#include <arm_neon.h>
#endif // __ARM_NEON

namespace ani {
    class AniNdkCamera : public NdkCameraWindow {
    public:
        virtual void on_image_render(cv::Mat& rgb) const;
    };

} // ani
