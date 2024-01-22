#pragma once
//
// Created by lozpeng on 2024/1/8.
//
#include <jni/jni.hpp>
#include "../utils/noncopyable.hpp"
#include "ModelInfo.hpp"

namespace ani {
    namespace android{
        /**
         * 模型信息对应java的ModelInfo类
         */
        class ModelInfo : private ani::util::noncopyable{
        private:
            class MImpl;
            std::unique_ptr<MImpl> impl_;
            public:
                static constexpr auto Name(){return "org/cwcc/ani/ai/model/ModelInfo";};
                /**
                *
                */
                static void registerNative(jni::JNIEnv&);
                /**
                 * 获取一个默认的模型信息
                 * @return
                 */
                static ModelInfo getDefaultModelInfo();

                ModelInfo(JNIEnv&);

                ModelInfo();

                ModelInfo(const ModelInfo&) = delete; // noncopyable
                ~ModelInfo();

                void setModelId(jni::JNIEnv&,const jni::String& modelId);
                jni::Local<jni::String> getModelId(jni::JNIEnv&);

                void setModelName(jni::JNIEnv&,const jni::String&);
                jni::Local<jni::String> getModelName(jni::JNIEnv&);

                void setInputName(jni::JNIEnv&,const jni::String&);
                jni::Local<jni::String> getInputName(jni::JNIEnv&);

                void setOutputName(jni::JNIEnv&,const jni::String&);
                jni::Local<jni::String> getOutputName(jni::JNIEnv&);

                void setIsGPUCPU(jni::JNIEnv&,const jni::Boolean &);
                jni::Local<jni::Boolean> getIsGPUCPU(jni::JNIEnv&);


                void setClasses(jni::JNIEnv&,const jni::Integer& );
                jni::Local<jni::Integer> getClasses(jni::JNIEnv&);

                void setMeanVals(jni::JNIEnv&,const jni::Array<jni::Float>&);
                jni::Local<jni::Array<jni::Float>> getMeanVals(jni::JNIEnv&);

                void setNormalVals(jni::JNIEnv&,const jni::Array<jni::Float>&);
                jni::Local<jni::Array<jni::Float>> getNormalVals(jni::JNIEnv&);

                void setTargetSize(jni::JNIEnv&,const jni::Float&);
                jni::Local<jni::Float> getTargetSize(jni::JNIEnv&);
         };
    }//android
} // ani
