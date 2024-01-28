//
// Created by lozpeng on 2024/1/12.
//

#ifndef ANIMALFACE_ANIAIMODEL_HPP
#define ANIMALFACE_ANIAIMODEL_HPP
#include <jni/jni.hpp>
#include <string>
#include <jni.h>
#include "model/android/asset_manager.hpp"
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>

namespace ani {
    namespace android {
        class AniAIModel {
        public:
            static constexpr auto Name() { return "org/cwcc/ani/ai/model/AniAIModel"; };

            static void registerNative(jni::JNIEnv &);

            static jboolean hasInstance(jni::JNIEnv &);

            static jni::Local<jni::Object<android::AssetManager>> getAssetManager(jni::JNIEnv &);


            static AAssetManager* getAAssetManager(jni::JNIEnv &env);
//        //加载模型
//        jni::Local<jni::Boolean> loadModel(jni::JNIEnv& env,
//                                                      jni::Object<ani::android::ModelInfo>& jModelInfo);
//
//        /**
//         * 使用模型进行检测
//         */
//        jni::Local<jni::Array<jni::Object<android::ModelResult>>> detect(jni::JNIEnv&,jni::Object<android::Bitmap>&);
//        /**
//         *
//         */
//        jni::Local<jni::Array<jni::Object<android::ModelResult>>> detectByModel(jni::JNIEnv&,
//                                                                     jni::Object<ani::android::ModelInfo>&,
//                                                                     jni::Object<android::Bitmap>&);
            //static jni::Global<jni::Object<android::AssetManager>>  assetManager;
        };
    }
} // ani

#endif //ANIMALFACE_ANIAIMODEL_HPP
