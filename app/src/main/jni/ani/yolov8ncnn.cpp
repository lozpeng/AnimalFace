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


#include "AniAI.hpp"
#include "jni/jni.hpp"

#include "utils/cvimageutils.hpp"
#include "model/android/attach_env.hpp"

#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>

using namespace ani;
using namespace ani::android;

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
// public native boolean loadModel(asset_manager mgr, int modelid, int cpugpu);
JNIEXPORT jboolean JNICALL Java_org_cwcc_ani_ai_model_Yolov8Model_loadModel(JNIEnv* env, jobject thiz, jobject assetManager, jint modelid, jint cpugpu)
{
    android::UniqueEnv ann = android::AttachEnv();
    if (modelid < 0 || modelid > 6 || cpugpu < 0 || cpugpu > 1)
    {
        return JNI_FALSE;
    }
    if(!g_camera)
        g_camera = new AniNdkCamera;
    if (android::AniAI::hasInstance(*env)) {
        auto assMgr = android::AniAI::getAssetManager(*env);
        AAssetManager* mgr1 = AAssetManager_fromJava(env, jni::Unwrap(assMgr.get()));
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
            if(g_yolo)
                delete g_yolo;
            g_yolo = 0;
        }
        else
        {
            if (!g_yolo)
                g_yolo = new Yolo;

            g_modelType =const_cast<char*>(modeltype);
            g_targetSize = target_size;
            g_modelId = (int)modelid;
            g_use_gpu= use_gpu;

            g_yolo->load(mgr, g_modelType,
                            g_targetSize,
                            mean_vals[g_modelId],
                            norm_vals[g_modelId],
                              g_use_gpu);
            __android_log_print(ANDROID_LOG_DEBUG, "Yolov8Model", "YoloV8Model inited!");
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

// public native boolean loadModelPro(asset_manager mgr,NcnnModel modelInfo);
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
    android::UniqueEnv ann = android::AttachEnv();
    __android_log_print(ANDROID_LOG_DEBUG, "ncnn", "openCamera %d", facing);
    if(g_camera)
        g_camera->open((int)facing);
    else
        __android_log_print(ANDROID_LOG_DEBUG, "ncnn", "openCamera %d failed",facing);

    return JNI_TRUE;
}

// public native boolean closeCamera();
JNIEXPORT jboolean JNICALL Java_org_cwcc_ani_ai_model_Yolov8Model_closeCamera(JNIEnv* env, jobject thiz)
{
    android::UniqueEnv ann = android::AttachEnv();
    __android_log_print(ANDROID_LOG_DEBUG, "ncnn", "closeCamera");
    if(g_camera)
        g_camera->close();

    return JNI_TRUE;
}

// public native boolean setOutputWindow(Surface surface);
JNIEXPORT jboolean JNICALL Java_org_cwcc_ani_ai_model_Yolov8Model_setOutputWindow(JNIEnv* env, jobject thiz, jobject surface)
{
    android::UniqueEnv ann = android::AttachEnv();
    if(!g_camera)
        g_camera = new AniNdkCamera;

    ANativeWindow* win = ANativeWindow_fromSurface(env, surface);
    __android_log_print(ANDROID_LOG_DEBUG, "ncnn", "setOutputWindow %p", win);
    if(g_camera){
        g_camera->set_window(win);
        return JNI_TRUE;
    }
    else
        return JNI_FALSE;
}
//检测图片，识别
JNIEXPORT jobjectArray JNICALL
Java_org_cwcc_ani_ai_model_Yolov8Model_Detect(JNIEnv *env, jobject thiz, jobject bitmap)
{
    android::UniqueEnv ann = android::AttachEnv();
    double start_time = ncnn::get_current_time();

    AndroidBitmapInfo info;
    AndroidBitmap_getInfo(env, bitmap, &info);
    if (info.format != ANDROID_BITMAP_FORMAT_RGBA_8888)
        return NULL;

    cv::Mat rgb; //cv格式的图片
    bool ret = util::CvImageUtil::bitMap2cvMatrix(env, bitmap, rgb);          // Bitmap to cv::Mat
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