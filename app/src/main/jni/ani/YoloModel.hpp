//
// Created by lozpeng on 2024/1/12.
//

#ifndef ANIMALFACE_YOLOMODEL_HPP
#define ANIMALFACE_YOLOMODEL_HPP
#include <jni/jni.hpp>
#include <string>
#include <jni.h>
#include "model/android/ModelInfo.hpp"


namespace ani {

    class YoloModel {
    public:
        static constexpr auto Name() { return "org/cwcc/ani/ai/model/YoloModel"; };

        static void registerNative(jni::JNIEnv&);

        //加载模型
        jni::jboolean loadModel(jni::JNIEnv&,jni::Object<android::ModelInfo>&);


    };

} // ani

#endif //ANIMALFACE_YOLOMODEL_HPP
