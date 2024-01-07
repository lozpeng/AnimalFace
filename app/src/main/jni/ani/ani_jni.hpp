#pragma once
//
// Created by lozpeng on 2024/1/7.
//

// clang-format off
#if defined WIN32
#ifdef ANI_BUILDING_LIB
        #ifdef __GNUC__
            #define ANI_EXPORT __attribute__((dllexport))
        #else
            #define ANI_EXPORT __declspec(dllexport)
        #endif
    #else
        #ifdef __GNUC__
            #define ANI_EXPORT __attribute__((dllimport))
        #else
            #define ANI_EXPORT __declspec(dllimport)
        #endif
    #endif
#else
#define ANI_EXPORT __attribute__((visibility ("default"))) // NOLINT
#endif
// clang-format on
#include <string>
#include <jni/jni.hpp>

typedef struct _jmethodID* jmethodID;
typedef struct _JavaVM JavaVM;
typedef struct _JNIEnv JNIEnv;

namespace ani{
    extern JavaVM* theJVM;

    extern std::string cachePath;
    extern std::string dataPath;

    bool attach_jni_thread(JavaVM* vm, JNIEnv** env, std::string threadName);
    void detach_jni_thread(JavaVM* vm, JNIEnv** env, bool detach);
}
