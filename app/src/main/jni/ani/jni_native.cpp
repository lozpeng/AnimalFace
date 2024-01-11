//
// Created by lozpeng on 2024/1/7.
//
#include <jni.h>
#include "jni_native.hpp"

#include "java_types.hpp"
#include "ani_jni.hpp"
#include "utils/utils.hpp"

#include "model/ModelInfo_JNI.hpp"

namespace ani {
    //注册基础类
    void registerNatives(JavaVM* vm) {
        theJVM = vm;

        jni::JNIEnv& env = jni::GetEnv(*vm, jni::jni_version_1_6);

        ani::java::registerNatives(env); //注册基础类型
        ani::util::registerNative(env);  //注册高级类型，如list map等


        //注册一些需要与java进行交互的的对象
        andriod::ModelInfo::registerNative(env); // 注册模型信息
    }
}