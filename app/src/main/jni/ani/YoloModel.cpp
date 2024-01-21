//
// Created by lozpeng on 2024/1/12.
//

#include "YoloModel.hpp"

namespace ani {
    void YoloModel::registerNative(jni::JNIEnv& env)
    {
        static auto& javaClass = jni::Class<YoloModel>::Singleton(env);
#define METHOD(MethodPtr, name) jni::MakeNativePeerMethod<decltype(MethodPtr), (MethodPtr)>(name)
        //注册方法
        jni::RegisterNativePeer<YoloModel>(
                env,
                javaClass,
                "nativePtr",
                  METHOD(&YoloModel::loadModel,"nativeLoadModel")
                , METHOD(&YoloModel::detect,"nativeDectect")
                , METHOD(&YoloModel::detectByModel,"nativeDectectByModel")
                );
    }

    //加载模型
    jni::Local<jni::Boolean> YoloModel::loadModel(jni::JNIEnv& env,jni::Object<ani::android::ModelInfo>& jModelInfo)
    {
        return jni::Local<jni::Boolean>(env, nullptr);
    }

    /**
     * 使用模型进行检测
     */
    jni::Local<jni::Array<jni::Object<android::ModelResult>>> YoloModel::detect(jni::JNIEnv& env,
                                                                                    jni::Object<android::Bitmap>& jBitMap)
    {
        return jni::Local<jni::Array<jni::Object<android::ModelResult>>>(env, nullptr);
    }
    /**
     *
     */
    jni::Local<jni::Array<jni::Object<android::ModelResult>>> YoloModel::detectByModel(jni::JNIEnv& env,
                                                                            jni::Object<ani::android::ModelInfo>& jModelInfo,
                                                                            jni::Object<android::Bitmap>& jBitMap)
    {

        return jni::Local<jni::Array<jni::Object<android::ModelResult>>>(env, nullptr);
    }
} // ani