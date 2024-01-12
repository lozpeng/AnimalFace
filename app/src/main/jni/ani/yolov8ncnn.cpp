// Tencent is pleased to support the open source community by making ncnn available.
//
// Copyright (C) 2021 THL A29 Limited, a Tencent company. All rights reserved.
//
// Licensed under the BSD 3-Clause License (the "License"); you may not use this file except
// in compliance with the License. You may obtain a copy of the License at
//
// https://opensource.org/licenses/BSD-3-Clause
//
// Unless required by applicable law or agreed to in writing, software distributed
// under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
// CONDITIONS OF ANY KIND, either express or implied. See the License for the
// specific language governing permissions and limitations under the License.

#include <android/asset_manager_jni.h>
#include <android/native_window_jni.h>
#include <android/native_window.h>

#include <android/bitmap.h>
#include <android/log.h>

#include <jni.h>

#include <string>
#include <vector>

#include <platform.h>
#include <benchmark.h>

#include "yolo.h"

#include "ndkcamera.h"

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <opencv2/calib3d/calib3d.hpp>
#if __ARM_NEON
#include <arm_neon.h>
#endif // __ARM_NEON

#include "jni_native.hpp"

#define ASSERT(status, ret)     if (!(status)) { return ret; }
#define ASSERT_FALSE(status)    ASSERT(status, false)

static int draw_unsupported(cv::Mat& rgb)
{
    const char text[] = "unsupported";

    int baseLine = 0;
    cv::Size label_size = cv::getTextSize(text, cv::FONT_HERSHEY_SIMPLEX, 1.0, 1, &baseLine);

    int y = (rgb.rows - label_size.height) / 2;
    int x = (rgb.cols - label_size.width) / 2;

    cv::rectangle(rgb, cv::Rect(cv::Point(x, y), cv::Size(label_size.width, label_size.height + baseLine)),
                    cv::Scalar(255, 255, 255), -1);

    cv::putText(rgb, text, cv::Point(x, y + label_size.height),
                cv::FONT_HERSHEY_SIMPLEX, 1.0, cv::Scalar(0, 0, 0));

    return 0;
}

static int draw_fps(cv::Mat& rgb)
{
    // resolve moving average
    float avg_fps = 0.f;
    {
        static double t0 = 0.f;
        static float fps_history[10] = {0.f};

        double t1 = ncnn::get_current_time();
        if (t0 == 0.f)
        {
            t0 = t1;
            return 0;
        }

        float fps = 1000.f / (t1 - t0);
        t0 = t1;

        for (int i = 9; i >= 1; i--)
        {
            fps_history[i] = fps_history[i - 1];
        }
        fps_history[0] = fps;

        if (fps_history[9] == 0.f)
        {
            return 0;
        }

        for (int i = 0; i < 10; i++)
        {
            avg_fps += fps_history[i];
        }
        avg_fps /= 10.f;
    }

    char text[32];
    sprintf(text, "FPS=%.2f", avg_fps);

    int baseLine = 0;
    cv::Size label_size = cv::getTextSize(text, cv::FONT_HERSHEY_SIMPLEX, 0.5, 1, &baseLine);

    int y = 0;
    int x = rgb.cols - label_size.width;

    cv::rectangle(rgb, cv::Rect(cv::Point(x, y), cv::Size(label_size.width, label_size.height + baseLine)),
                    cv::Scalar(255, 255, 255), -1);

    cv::putText(rgb, text, cv::Point(x, y + label_size.height),
                cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(0, 0, 0));

    return 0;
}

static Yolo* g_yolo = 0;
static ncnn::Mutex lock;

class MyNdkCamera : public NdkCameraWindow
{
public:
    virtual void on_image_render(cv::Mat& rgb) const;
};

void MyNdkCamera::on_image_render(cv::Mat& rgb) const
{
    // nanodet
    {
        ncnn::MutexLockGuard g(lock);

        if (g_yolo)
        {
            std::vector<Object> objects;
            g_yolo->detect(rgb, objects);

            g_yolo->draw(rgb, objects);
        }
        else
        {
            draw_unsupported(rgb);
        }
    }

    draw_fps(rgb);
}

static MyNdkCamera* g_camera = 0;

extern "C" {
//检测结果对象
static jclass objCls = NULL;
static jmethodID constructortorId;
static jfieldID xId;
static jfieldID yId;
static jfieldID wId;
static jfieldID hId;
static jfieldID labelId;
static jfieldID probId;

JNIEXPORT jint JNI_OnLoad(JavaVM* vm, void* reserved)
{
    __android_log_print(ANDROID_LOG_DEBUG, "ncnn", "JNI_OnLoad");

    g_camera = new MyNdkCamera;
    ani::registerNatives(vm);
    //return JNI_VERSION_1_6;
    return jni::Unwrap(jni::jni_version_1_6);
    //return JNI_VERSION_1_4;
}

JNIEXPORT void JNI_OnUnload(JavaVM* vm, void* reserved)
{
    __android_log_print(ANDROID_LOG_DEBUG, "ncnn", "JNI_OnUnload");

    {
        ncnn::MutexLockGuard g(lock);

        delete g_yolo;
        g_yolo = 0;
    }

    delete g_camera;
    g_camera = 0;
}

JNIEXPORT void JNICALL
Java_org_cwcc_ani_ai_model_Yolov8Model_toValue(JNIEnv *env, jobject thiz, jfloatArray vals) {
    jfloat* featureData1 = (jfloat*)env->GetFloatArrayElements(vals, 0);
    jsize featureSize1 = env->GetArrayLength(vals);
    std::vector<float> featureVector1(featureSize1);
}
JNIEXPORT jfloatArray JNICALL
Java_org_cwcc_ani_ai_model_Yolov8Model_getFloatValue(JNIEnv *env, jobject thiz) {
    std::vector<float> faceFeatureData{0,1};
    jfloatArray faceFeatureArray = env->NewFloatArray(faceFeatureData.size());

    env->SetFloatArrayRegion(faceFeatureArray, 0, faceFeatureData.size(), faceFeatureData.data());
    return faceFeatureArray;
}

/**
 * java的bitmap转为cv::Mat格式
 * @param env
 * @param bitmap_obj
 * @param matrix
 * @return
 */
bool bitMap2cvMatrix(JNIEnv* env,jobject bitmap_obj,cv::Mat & matrix)
{
    void* bitmapPixels;
    AndroidBitmapInfo bitmapInfo;

    ASSERT_FALSE( AndroidBitmap_getInfo(env, bitmap_obj, &bitmapInfo) >= 0);        // Get picture parameters
    ASSERT_FALSE( bitmapInfo.format == ANDROID_BITMAP_FORMAT_RGBA_8888
                  || bitmapInfo.format == ANDROID_BITMAP_FORMAT_RGB_565 );          // Only ARGB? 8888 and RGB? 565 are supported
    ASSERT_FALSE( AndroidBitmap_lockPixels(env, bitmap_obj, &bitmapPixels) >= 0 );  // Get picture pixels (lock memory block)
    ASSERT_FALSE( bitmapPixels );
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
bool cvMatrix2Bitmap(JNIEnv * env, cv::Mat & matrix, jobject obj_bitmap) {
    void * bitmapPixels;                                            // Save picture pixel data
    AndroidBitmapInfo bitmapInfo;                                   // Save picture parameters

    ASSERT_FALSE( AndroidBitmap_getInfo(env, obj_bitmap, &bitmapInfo) >= 0);        // Get picture parameters
    ASSERT_FALSE( bitmapInfo.format == ANDROID_BITMAP_FORMAT_RGBA_8888
                  || bitmapInfo.format == ANDROID_BITMAP_FORMAT_RGB_565 );          // Only ARGB? 8888 and RGB? 565 are supported
    ASSERT_FALSE( matrix.dims == 2
                  && bitmapInfo.height == (uint32_t)matrix.rows
                  && bitmapInfo.width == (uint32_t)matrix.cols );                   // It must be a 2-dimensional matrix with the same length and width
    ASSERT_FALSE( matrix.type() == CV_8UC1 || matrix.type() == CV_8UC3 || matrix.type() == CV_8UC4 );
    ASSERT_FALSE( AndroidBitmap_lockPixels(env, obj_bitmap, &bitmapPixels) >= 0 );  // Get picture pixels (lock memory block)
    ASSERT_FALSE( bitmapPixels );

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


// public native boolean loadModel(AssetManager mgr, int modelid, int cpugpu);
JNIEXPORT jboolean JNICALL Java_org_cwcc_ani_ai_model_Yolov8Model_loadModel(JNIEnv* env, jobject thiz, jobject assetManager, jint modelid, jint cpugpu)
{
    if (modelid < 0 || modelid > 6 || cpugpu < 0 || cpugpu > 1)
    {
        return JNI_FALSE;
    }

    AAssetManager* mgr = AAssetManager_fromJava(env, assetManager);

    __android_log_print(ANDROID_LOG_DEBUG, "ncnn", "loadModel %p", mgr);

    const char* modeltypes[] =
    {
        "yolov8n",
        "yolov8s",
        "birds_200-sim-opt-fp16"
    };

    const int target_sizes[] =
    {
        320,
        320,
        320,
    };

    const float mean_vals[][3] =
    {
        {103.53f, 116.28f, 123.675f},
        {103.53f, 116.28f, 123.675f},
        {103.53f, 116.28f, 123.675f},
    };

    const float norm_vals[][3] =
    {
        { 1 / 255.f, 1 / 255.f, 1 / 255.f },
        { 1 / 255.f, 1 / 255.f, 1 / 255.f },
        { 1 / 255.f, 1 / 255.f, 1 / 255.f },
    };

    const char* modeltype = modeltypes[(int)modelid];
    int target_size = target_sizes[(int)modelid];
    bool use_gpu = (int)cpugpu == 1;

    // reload
    {
        ncnn::MutexLockGuard g(lock);

        if (use_gpu && ncnn::get_gpu_count() == 0)
        {
            // no gpu
            delete g_yolo;
            g_yolo = 0;
        }
        else
        {
            if (!g_yolo)
                g_yolo = new Yolo;
            g_yolo->load(mgr, modeltype, target_size, mean_vals[(int)modelid], norm_vals[(int)modelid], use_gpu);
        }
    }
    // init jni glue 初始化返回结果
    jclass localObjCls = env->FindClass("org/cwcc/ani/ai/model/Yolov8Model$Obj");
    objCls = reinterpret_cast<jclass>(env->NewGlobalRef(localObjCls));

    constructortorId = env->GetMethodID(objCls, "<init>", "(Lorg/cwcc/ani/ai/model/Yolov8Model;)V");

    xId = env->GetFieldID(objCls, "x", "F");
    yId = env->GetFieldID(objCls, "y", "F");
    wId = env->GetFieldID(objCls, "w", "F");
    hId = env->GetFieldID(objCls, "h", "F");
    labelId = env->GetFieldID(objCls, "label", "Ljava/lang/String;");
    probId = env->GetFieldID(objCls, "prob", "F");

    return JNI_TRUE;
}

// public native boolean loadModelPro(AssetManager mgr,NcnnModel modelInfo);
JNIEXPORT jboolean JNICALL
Java_org_cwcc_ani_ai_model_Yolov8Model_loadModelPro(JNIEnv *env, jobject thiz, jobject mgr, jobject model_info) {
    // TODO: implement loadModelPro()

    return 0;
}
// public native boolean openCamera(int facing);
JNIEXPORT jboolean JNICALL Java_org_cwcc_ani_ai_model_Yolov8Model_openCamera(JNIEnv* env, jobject thiz, jint facing)
{
    if (facing < 0 || facing > 1)
        return JNI_FALSE;

    __android_log_print(ANDROID_LOG_DEBUG, "ncnn", "openCamera %d", facing);

    g_camera->open((int)facing);

    return JNI_TRUE;
}

// public native boolean closeCamera();
JNIEXPORT jboolean JNICALL Java_org_cwcc_ani_ai_model_Yolov8Model_closeCamera(JNIEnv* env, jobject thiz)
{
    __android_log_print(ANDROID_LOG_DEBUG, "ncnn", "closeCamera");

    g_camera->close();

    return JNI_TRUE;
}

// public native boolean setOutputWindow(Surface surface);
JNIEXPORT jboolean JNICALL Java_org_cwcc_ani_ai_model_Yolov8Model_setOutputWindow(JNIEnv* env, jobject thiz, jobject surface)
{
    ANativeWindow* win = ANativeWindow_fromSurface(env, surface);

    __android_log_print(ANDROID_LOG_DEBUG, "ncnn", "setOutputWindow %p", win);

    g_camera->set_window(win);

    return JNI_TRUE;
}
//检测图片，识别
JNIEXPORT jobjectArray JNICALL
Java_org_cwcc_ani_ai_model_Yolov8Model_Detect(JNIEnv *env, jobject thiz, jobject bitmap)
{
    double start_time = ncnn::get_current_time();

    AndroidBitmapInfo info;
    AndroidBitmap_getInfo(env, bitmap, &info);
    if (info.format != ANDROID_BITMAP_FORMAT_RGBA_8888)
        return NULL;

    cv::Mat rgb; //cv格式的图片
    bool ret = bitMap2cvMatrix(env, bitmap, rgb);          // Bitmap to cv::Mat
    if (ret == false) {
        return NULL;
    }
    std::vector<Object> objects;
    {
        ncnn::MutexLockGuard g(lock);

        if (g_yolo) {
            g_yolo->detect(rgb, objects);
        }
    }

    /*
    // Android Bitmap转ncnn::Mat
    ncnn::Mat in = ncnn::Mat::from_android_bitmap(env, bitmap, ncnn::Mat::PIXEL_RGB);

    // Convert in ncnn::Mat to cv::Mat
    cv::Mat img(in.h, in.w, CV_8UC3, in.data);

    // Apply lens correction my change
    cv::Mat cameraMatrix = (cv::Mat_<double>(3, 3)
            << 1.00155905e+03, 0.00000000e+00, 9.59165358e+02, 0.00000000e+00, 1.00302639e+03, 5.46561966e+02, 0.00000000e+00, 0.00000000e+00, 1.00000000e+00);
    cv::Mat distCoeffs = (cv::Mat_<double>(1, 5)
            << 3.64619756e-02, 1.35448346e+00, 1.48796634e-03, -3.30450509e-04, -8.34865831e+00);
    cv::Mat img_undistorted;
    cv::undistort(img, img_undistorted, cameraMatrix, distCoeffs);

    // Convert img_undistorted cv::Mat back to in ncnn::Mat
    in = ncnn::Mat::from_pixels(img_undistorted.data, ncnn::Mat::PIXEL_RGB, img_undistorted.cols,
                                img_undistorted.rows);

    std::vector<Object> objects;
    {
        ncnn::MutexLockGuard g(lock);

        if (g_yolo) {
            g_yolo->detect_mat(in, objects);
        }
    }

    // objects to Obj[]
    static const char *class_names[] = {
            "cart", "person", "warning sign", "skim milk", "largeskim milk"
    };
    */
    jobjectArray jObjArray = env->NewObjectArray(objects.size(), objCls, NULL);
    //__android_log_print(ANDROID_LOG_DEBUG, "NcnnYolov8", "objects num: %d", objects.size());
    __android_log_print(ANDROID_LOG_DEBUG, "NcnnYolov8", "objects num: %zu", objects.size());
    for (size_t i = 0; i < objects.size(); i++) {
        jobject jObj = env->NewObject(objCls, constructortorId, thiz);

        env->SetFloatField(jObj, xId, objects[i].rect.x);
        env->SetFloatField(jObj, yId, objects[i].rect.y);
        env->SetFloatField(jObj, wId, objects[i].rect.width);
        env->SetFloatField(jObj, hId, objects[i].rect.height);
        //env->SetObjectField(jObj, labelId, env->NewStringUTF(class_names[objects[i].label]));
        char text[256];
        sprintf(text, "%d ", objects[i].label);
        env->SetObjectField(jObj, labelId, env->NewStringUTF(text));
        env->SetFloatField(jObj, probId, objects[i].prob);

        env->SetObjectArrayElement(jObjArray, i, jObj);
        //__android_log_print(ANDROID_LOG_DEBUG, "NcnnYolov8", "%.2f  %.2f  %.2f  %.2f %s %.2f", \
            objects[i].rect.x, objects[i].rect.y, objects[i].rect.width, objects[i].rect.height, \
            class_names[objects[i].label], objects[i].prob);
    }

    double elasped = ncnn::get_current_time() - start_time;
    __android_log_print(ANDROID_LOG_DEBUG, "NcnnYolov8", "%.2fms  detect", elasped);
    return jObjArray;
}
}