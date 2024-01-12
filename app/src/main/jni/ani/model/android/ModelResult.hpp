#pragma  once
//
// Created by lozpeng on 2024/1/12.
//
#include "jni/jni.hpp"
#include "../../utils/noncopyable.hpp"
#include "../../model/ModelResult.hpp"

#include <iostream>

namespace ani {
    namespace android {
        class ModelResult : private ani::util::noncopyable{
        public:
            static constexpr auto Name(){return "org/cwcc/ani/ai/model/ModelResult";};

            ModelResult(JNIEnv&){ std::cout << "Native peer initialized" << std::endl; }
            ModelResult(const ModelResult&) = delete; // noncopyable
            ~ModelResult() { std::cout << "Native peer finalized" << std::endl; }

            //ani::ModelResult
            /**
             *
             */
            static void registerNative(jni::JNIEnv&);

        };

    } // ani
} // android
