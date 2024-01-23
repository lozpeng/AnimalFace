//
// Created by lozpeng on 2024/1/12.
//

#ifndef ANIMALFACE_YOLOMODEL_HPP
#define ANIMALFACE_YOLOMODEL_HPP
#include <jni/jni.hpp>
#include <string>
#include <jni.h>
#include "model/android/ModelInfo.hpp"
#include "model/android/ModelResult.hpp"
#include "model/android/Bitmap.hpp"
#include "model/android/asset_manager.hpp"


namespace ani {

    class YoloModel {
    public:
        static constexpr auto Name() { return "org/cwcc/ani/ai/model/YoloModel"; };

        static void registerNative(jni::JNIEnv&);
        static jboolean hasInstance(jni::JNIEnv&);
        static jni::Local<jni::Object<android::AssetManager>> getAssetManager(jni::JNIEnv&);

        //加载模型
        jni::Local<jni::Boolean> loadModel(jni::JNIEnv& env,
                                                      jni::Object<ani::android::ModelInfo>& jModelInfo);

        /**
         * 使用模型进行检测
         */
        jni::Local<jni::Array<jni::Object<android::ModelResult>>> detect(jni::JNIEnv&,jni::Object<android::Bitmap>&);
        /**
         *
         */
        jni::Local<jni::Array<jni::Object<android::ModelResult>>> detectByModel(jni::JNIEnv&,
                                                                     jni::Object<ani::android::ModelInfo>&,
                                                                     jni::Object<android::Bitmap>&);
    private:
        jni::Global<jni::Object<android::AssetManager>> assetManager;
    };

} // ani

#endif //ANIMALFACE_YOLOMODEL_HPP
