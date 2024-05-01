//
// Created by lozpeng on 2024/1/7.
//
#include "ani_jni.hpp"
#include <android/log.h>
#include <string>

namespace ani
{
    JavaVM* theJVM;

    bool attach_jni_thread(JavaVM* vm, JNIEnv** env, std::string threadName) {
        assert(vm != nullptr);
        assert(env != nullptr);

        JavaVMAttachArgs args = {JNI_VERSION_1_6, threadName.c_str(), NULL};

        jint ret;
        *env = nullptr;
        bool detach = false;
        ret = vm->GetEnv(reinterpret_cast<void**>(env), JNI_VERSION_1_6);
        if (ret != JNI_OK) {
            if (ret != JNI_EDETACHED) {
                __android_log_print(ANDROID_LOG_WARN, "ani_jni", "attach_jni_thread");
                throw std::runtime_error("GetEnv() failed");
            } else {
                ret = vm->AttachCurrentThread(env, &args);
                if (ret != JNI_OK) {
                    __android_log_print(ANDROID_LOG_ERROR, "ani_jni", "attach_jni_thread %s", std::to_string(ret).c_str());
                    throw std::runtime_error("AttachCurrentThread() failed");
                }
                detach = true;
            }
        }

        return detach;
    }

// TODO: remove
    void detach_jni_thread(JavaVM* vm, JNIEnv** env, bool detach) {
        if (detach) {
            assert(vm != nullptr);
            assert(env != nullptr);

            jint ret;
            if ((ret = vm->DetachCurrentThread()) != JNI_OK) {
                __android_log_print(ANDROID_LOG_ERROR, "ani_jni", "DetachCurrentThread() failed with %s", std::to_string(ret).c_str());
                throw std::runtime_error("DetachCurrentThread() failed");
            }
        }
        *env = nullptr;
    }
}