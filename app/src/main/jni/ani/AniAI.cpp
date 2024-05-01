//
// Created by lozpeng on 2024/1/12.
//

#include "AniAI.hpp"
#include "model/android/asset_manager.hpp"
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>

#include <android/log.h>
#include "model/android/conversion/conversion.hpp"

#include "model/android/ModelInfo.hpp"
#include "yolo.h"

#include "jni_native.hpp"
#include "utils/anindkcamera.hpp"
#include "model/android/attach_env.hpp"

extern "C" JNIEXPORT jint JNI_OnLoad(JavaVM *vm, void *) {
    assert(vm != nullptr);
    ani::registerNatives(vm);
    __android_log_print(ANDROID_LOG_DEBUG, "AniAI", "JNI_OnLoaded");
    return JNI_VERSION_1_6;
    //return jni::Unwrap(jni::jni_version_1_6);
}

extern "C" JNIEXPORT void JNI_OnUnload(JavaVM* vm, void* reserved) {
    {
        ncnn::MutexLockGuard g(lock);
        if(g_yolo)
            delete g_yolo;

        g_yolo = 0;
    }
    if(g_camera)
        delete g_camera;

    g_camera = 0;
    __android_log_print(ANDROID_LOG_DEBUG, "AniAI", "JNI_OnUnloaded");
}
namespace ani {
    namespace android {
        void AniAI::registerNative(jni::JNIEnv &env) {
            jni::Class<AniAI>::Singleton(env);
        }

        jni::Local<jni::Object<android::AssetManager>> AniAI::getAssetManager(jni::JNIEnv &env) {
            static auto& javaClass = jni::Class<AniAI>::Singleton(env);
            auto method = javaClass.GetStaticMethod<jni::Object<android::AssetManager>()>(env,
                                                                                          "getAssetManager");
            return javaClass.Call(env, method);
        }

        jboolean AniAI::hasInstance(jni::JNIEnv &env) {
            static auto &javaClass = jni::Class<AniAI>::Singleton(env);
            auto method = javaClass.GetStaticMethod<jboolean()>(env, "hasInstance");
            return javaClass.Call(env, method);
        }
        /**
         * 获取Android资源管理对象
         * @param env
         * @return
         */
        AAssetManager* AniAI::getAAssetManager(jni::JNIEnv &env)
        {
            //jni::Global<jni::Object<android::AssetManager>>
            auto  assetManager  = jni::NewGlobal(env, getAssetManager(env));
            jni::NullCheck(env, &assetManager);
            AAssetManager* mgr = AAssetManager_fromJava(&env, jni::Unwrap(assetManager.get()));
            assetManager.release();
            return mgr;
        }
    }
    /**
    static Yolo* g_yolo = 0;
    static ncnn::Mutex lock;

    //加载模型
    jni::Local<jni::Boolean> AniAI::loadModel(jni::JNIEnv& env,
                                                  jni::Object<ani::android::ModelInfo>& jModelInfo)
    {
        //添加方法实现 ，加载模型
        assetManager = jni::NewGlobal(env, getAssetManager(env));

        jni::NullCheck(env, &jModelInfo);
        //AAssetManager_fromJava(&env, jni::Unwrap(assetManager.get()));
        AAssetManager* mgr = AAssetManager_fromJava(&env, jni::Unwrap(assetManager.get()));
        if(mgr==nullptr)
            return jni::Box(env,jni::jni_false);

        __android_log_print(ANDROID_LOG_DEBUG, "AniAI", "loadModel %p", mgr);
        using namespace ani;
        //java object transform to c++ptr actually it's also the same C++ object ptr
        static auto& javaClass = jni::Class<android::ModelInfo>::Singleton(env);
        static auto field = javaClass.GetField<jlong>(env, "nativePtr");
        android::ModelInfo* modelInfo =  reinterpret_cast<android::ModelInfo*>(jModelInfo.Get(env, field));

        const std::string modelName =jni::Make<std::string>(env,modelInfo->getModelName(env));
        __android_log_print(ANDROID_LOG_DEBUG, "AniAI", "loadModel %s", modelName.c_str());

        const int targetSize = jni::Unbox(env,modelInfo->getTargetSize(env));
        const int use_gpu = jni::Unbox(env,modelInfo->getIsGPUCPU(env));
        jni::Local<jni::Array<jni::Float>> jmeanVals = modelInfo->getMeanVals(env);
        jni::NullCheck(env, &jmeanVals);
        std::size_t len = jmeanVals.Length(env);
        float meanVals[len] ;
        int size = ani::andriod::conversion::fromJniFloatArray(env,jmeanVals, meanVals);
        if(size!=len)
            return jni::Local<jni::Boolean>(env, nullptr);
        jni::Local<jni::Array<jni::Float>> jNormals = modelInfo->getNormalVals(env);
        jni::NullCheck(env, &jNormals);
        len = jNormals.Length(env);
        float normals[len];
        size = andriod::conversion::fromJniFloatArray(env,jNormals, normals);
        if(size!=len)
            return jni::Local<jni::Boolean>(env, nullptr);
        {
            ncnn::MutexLockGuard g(lock);

            if (use_gpu && ncnn::get_gpu_count() == 0)// no gpu
            {
                delete g_yolo;
                g_yolo = 0;
            }
            else
            {
                if (!g_yolo)
                    g_yolo = new Yolo;
                g_yolo->load(mgr, modelName.c_str(),
                             targetSize,
                             meanVals,
                             normals,
                             use_gpu);
                __android_log_print(ANDROID_LOG_DEBUG, "AniAI", "loadModel %s", "模型加载成功！");
            }
        }
        return jni::Box(env,jni::jni_true);
    }

    jni::Local<jni::Array<jni::Object<android::ModelResult>>> AniAI::detect(jni::JNIEnv& env,
                                                                                    jni::Object<android::Bitmap>& jBitMap)
    {
        PremultipliedImage pImage = android::Bitmap::GetImage(env,jBitMap);

        return jni::Local<jni::Array<jni::Object<android::ModelResult>>>(env, nullptr);
    }
    jni::Local<jni::Array<jni::Object<android::ModelResult>>> AniAI::detectByModel(jni::JNIEnv& env,
                                                                            jni::Object<ani::android::ModelInfo>& jModelInfo,
                                                                            jni::Object<android::Bitmap>& jBitMap)
    {
        assetManager = jni::NewGlobal(env, getAssetManager(env));
        jni::Local<jni::Boolean> jResult = loadModel(env,jModelInfo);
        bool result = jni::Unbox(env,jResult);
        if(!result)
            return jni::Local<jni::Array<jni::Object<android::ModelResult>>>(env, nullptr);
        return detect(env,jBitMap);
    }
     **/
} // ani