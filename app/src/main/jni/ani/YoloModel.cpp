//
// Created by lozpeng on 2024/1/12.
//

#include "YoloModel.hpp"
#include "model/android/asset_manager.hpp"
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>

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
                  METHOD(&YoloModel::detect,"nativeDectect")
                , METHOD(&YoloModel::detectByModel,"nativeDectectByModel")
                );
    }
    jni::Local<jni::Object<android::AssetManager>> YoloModel::getAssetManager(jni::JNIEnv& env) {
        static auto& javaClass = jni::Class<YoloModel>::Singleton(env);
        auto method = javaClass.GetStaticMethod<jni::Object<android::AssetManager>()>(env, "getAssetManager");
        return  javaClass.Call(env, method);
    }

    jboolean YoloModel::hasInstance(jni::JNIEnv& env) {
        static auto& javaClass = jni::Class<YoloModel>::Singleton(env);
        auto method = javaClass.GetStaticMethod<jboolean()>(env, "hasInstance");
        return javaClass.Call(env, method);
    }


    //加载模型
    jni::Local<jni::Boolean> YoloModel::loadModel(jni::JNIEnv& env,
                                                  jni::Object<ani::android::ModelInfo>& jModelInfo)
    {
        //添加方法实现 ，加载模型
        assetManager = jni::NewGlobal(env, getAssetManager(env));
        //AAssetManager_fromJava(&env, jni::Unwrap(assetManager.get()));


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
        assetManager = jni::NewGlobal(env, getAssetManager(env));


        return jni::Local<jni::Array<jni::Object<android::ModelResult>>>(env, nullptr);
    }
} // ani