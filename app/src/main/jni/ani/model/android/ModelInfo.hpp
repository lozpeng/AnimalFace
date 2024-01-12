#pragma once
//
// Created by lozpeng on 2024/1/8.
//
#include <jni/jni.hpp>
#include "../utils/noncopyable.hpp"
#include "ModelInfo.hpp"
#include "../ModelInfo.hpp"

namespace ani {
    namespace andriod{
        /**
         * 模型信息对应java的ModelInfo类
         */
        class ModelInfo : private ani::util::noncopyable{
            public:
                static constexpr auto Name(){return "org/cwcc/ani/ai/model/ModelInfo";};
                /**
                 *
                 * @return
                 */
                static jni::Local<jni::Object<ModelInfo>> New(jni::JNIEnv&, const ani::ModelInfo&);
                /**
                 *
                 * @return
                 */
                static jni::Local<jni::Object<ModelInfo>> DefaultModelInfo(jni::JNIEnv&,const jni::Class<ModelInfo>&);
                /**
                 *
                 * @return
                 */
                static ani::ModelInfo getModelInfo(jni::JNIEnv&, const jni::Object<ModelInfo>&);
                /**
                 *
                 */
                static void registerNative(jni::JNIEnv&);

         };
    }//android
} // ani
