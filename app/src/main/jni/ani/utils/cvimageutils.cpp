//
// Created by lozpeng on 2024/1/30.
//

#include "cvimageutils.hpp"
#include <android/bitmap.h>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <opencv2/calib3d/calib3d.hpp>
#define ANI_ASSERT(status, ret)     if (!(status)) { return ret; }
#define ANI_ASSERT_FALSE(status)    ANI_ASSERT(status, false)
namespace ani{
    namespace android{
        namespace util
        {
            bool CvImageUtil::bitMap2cvMatrix(JNIEnv* env,jobject bitmap_obj,cv::Mat& matrix)
            {
                void* bitmapPixels;
                AndroidBitmapInfo bitmapInfo;

                ANI_ASSERT_FALSE( AndroidBitmap_getInfo(env, bitmap_obj, &bitmapInfo) >= 0);        // Get picture parameters
                ANI_ASSERT_FALSE( bitmapInfo.format == ANDROID_BITMAP_FORMAT_RGBA_8888
                              || bitmapInfo.format == ANDROID_BITMAP_FORMAT_RGB_565 );          // Only ARGB? 8888 and RGB? 565 are supported
                ANI_ASSERT_FALSE( AndroidBitmap_lockPixels(env, bitmap_obj, &bitmapPixels) >= 0 );  // Get picture pixels (lock memory block)
                ANI_ASSERT_FALSE( bitmapPixels );
                //判断图像通道数
                if (bitmapInfo.format == ANDROID_BITMAP_FORMAT_RGBA_8888) {//mat的四通道
                    cv::Mat tmp(bitmapInfo.height, bitmapInfo.width, CV_8UC4, bitmapPixels);    // Establish temporary mat
                    tmp.copyTo(matrix);                                                         // Copy to target matrix
                } else {
                    cv::Mat tmp(bitmapInfo.height, bitmapInfo.width, CV_8UC2, bitmapPixels);
                    cv::cvtColor(tmp, matrix, cv::COLOR_BGR5652RGB);
                }

                //convert RGB to BGR
                cv::cvtColor(matrix,matrix,cv::COLOR_RGB2BGR);

                AndroidBitmap_unlockPixels(env, bitmap_obj);            // Unlock

                return true;
            }
            bool CvImageUtil::cvMatrix2Bitmap(JNIEnv * env, cv::Mat& matrix, jobject& obj_bitmap)
            {
                void * bitmapPixels;                                            // Save picture pixel data
                AndroidBitmapInfo bitmapInfo;                                   // Save picture parameters

                ANI_ASSERT_FALSE( AndroidBitmap_getInfo(env, obj_bitmap, &bitmapInfo) >= 0);        // Get picture parameters
                ANI_ASSERT_FALSE( bitmapInfo.format == ANDROID_BITMAP_FORMAT_RGBA_8888
                              || bitmapInfo.format == ANDROID_BITMAP_FORMAT_RGB_565 );          // Only ARGB? 8888 and RGB? 565 are supported
                ANI_ASSERT_FALSE( matrix.dims == 2
                              && bitmapInfo.height == (uint32_t)matrix.rows
                              && bitmapInfo.width == (uint32_t)matrix.cols );                   // It must be a 2-dimensional matrix with the same length and width
                ANI_ASSERT_FALSE( matrix.type() == CV_8UC1 || matrix.type() == CV_8UC3 || matrix.type() == CV_8UC4 );
                ANI_ASSERT_FALSE( AndroidBitmap_lockPixels(env, obj_bitmap, &bitmapPixels) >= 0 );  // Get picture pixels (lock memory block)
                ANI_ASSERT_FALSE( bitmapPixels );

                if (bitmapInfo.format == ANDROID_BITMAP_FORMAT_RGBA_8888) {
                    cv::Mat tmp(bitmapInfo.height, bitmapInfo.width, CV_8UC4, bitmapPixels);
                    switch (matrix.type()) {
                        case CV_8UC1:   cv::cvtColor(matrix, tmp, cv::COLOR_GRAY2RGBA);     break;
                        case CV_8UC3:   cv::cvtColor(matrix, tmp, cv::COLOR_RGB2RGBA);      break;
                        case CV_8UC4:   matrix.copyTo(tmp);                                 break;
                        default:        AndroidBitmap_unlockPixels(env, obj_bitmap);        return false;
                    }
                } else {
                    cv::Mat tmp(bitmapInfo.height, bitmapInfo.width, CV_8UC2, bitmapPixels);
                    switch (matrix.type()) {
                        case CV_8UC1:   cv::cvtColor(matrix, tmp, cv::COLOR_GRAY2BGR565);   break;
                        case CV_8UC3:   cv::cvtColor(matrix, tmp, cv::COLOR_RGB2BGR565);    break;
                        case CV_8UC4:   cv::cvtColor(matrix, tmp, cv::COLOR_RGBA2BGR565);   break;
                        default:        AndroidBitmap_unlockPixels(env, obj_bitmap);        return false;
                    }
                }
                AndroidBitmap_unlockPixels(env, obj_bitmap);                // Unlock
                return true;
            }
        }
    }
}