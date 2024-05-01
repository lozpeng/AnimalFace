#pragma once
//
// Created by lozpeng on 2024/1/8.
//
#include <jni/jni.hpp>
#include "../utils/noncopyable.hpp"

#include "model/ModelInfo.hpp"

namespace ani {
    namespace android{
        /**
         * 模型信息对应java的ModelInfo类
         */
        class ModelInfo : private ani::util::noncopyable{
            public:
                static constexpr auto Name(){return "org/cwcc/ani/ai/model/ModelInfo";};
                /**
                *`
                */
                static void registerNative(jni::JNIEnv&);

                static jni::Local<jni::Object<ModelInfo>> New(jni::JNIEnv&, const ani::ModelInfo&);

                static ani::ModelInfo getModelInfo(jni::JNIEnv&, const jni::Object<ModelInfo>&);

                static size_t toStdFloatVector(jni::JNIEnv&,const jni::Array<jni::Float>&,std::vector<float>&);

                ModelInfo(const ModelInfo&) = delete; // noncopyable
                ~ModelInfo();
         };
    }//android
} // ani
