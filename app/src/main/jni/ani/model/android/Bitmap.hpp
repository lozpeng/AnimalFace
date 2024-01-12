//
// Created by lozpeng on 2024/1/12.
//

#ifndef ANIMALFACE_BITMAP_HPP
#define ANIMALFACE_BITMAP_HPP

#include <jni/jni.hpp>
#include "model/image.hpp"

namespace ani {
    namespace android {

        class Bitmap {
        public:
            class Config {
            public:
                static constexpr auto Name() { return "android/graphics/Bitmap$Config"; };

                enum Value {
                    ALPHA_8,
                    ARGB_4444,
                    ARGB_8888,
                    RGB_565,
                };

                static jni::Local<jni::Object<Config>> Create(jni::JNIEnv&, Value);
            };
            static constexpr auto Name() { return "android/graphics/Bitmap"; };
            static void registerNative(jni::JNIEnv&);

            static jni::Local<jni::Object<Bitmap>> CreateBitmap(jni::JNIEnv&,
                                                                jni::jint width,
                                                                jni::jint height,
                                                                const jni::Object<Config>&);

            static jni::Local<jni::Object<Bitmap>> CreateBitmap(jni::JNIEnv& env,
                                                                jni::jint width,
                                                                jni::jint height,
                                                                Config::Value config) {
                return CreateBitmap(env, width, height, Config::Create(env, config));
            }

            static PremultipliedImage GetImage(jni::JNIEnv&, const jni::Object<Bitmap>&);
            static jni::Local<jni::Object<Bitmap>> CreateBitmap(jni::JNIEnv&, const PremultipliedImage&);
            static jni::Local<jni::Object<Bitmap>> Copy(jni::JNIEnv&, const jni::Object<Bitmap>&);
        };

    } // ani
} // android

#endif //ANIMALFACE_BITMAP_HPP
