#pragma  once
//
// Created by lozpeng on 2024/1/12.
//
#include "jni/jni.hpp"
#include "../../utils/noncopyable.hpp"

#include <iostream>

namespace ani {
    namespace android {
        class ModelResult : private ani::util::noncopyable{
        private:
            class Impl;
            std::unique_ptr<Impl> impl_;
        public:
            static constexpr auto Name(){return "org/cwcc/ani/ai/model/ModelResult";};
            /**
            *
            */
            static void registerNative(jni::JNIEnv&);

            ModelResult(JNIEnv&);
            ModelResult(const ModelResult&) = delete; // noncopyable
            ~ModelResult();

            jni::Local<jni::Float> getX(jni::JNIEnv&);
            jni::Local<jni::Float> getY(jni::JNIEnv&);
            jni::Local<jni::Float> getW(jni::JNIEnv&);
            jni::Local<jni::Float> getH(jni::JNIEnv&);
            jni::Local<jni::Float> getProb(jni::JNIEnv&);
            jni::Local<jni::String> getLabel(jni::JNIEnv&);
            jni::Local<jni::String> getId(jni::JNIEnv&);


            ModelResult& withX(float x);
            ModelResult& withY(float y);
            ModelResult& withW(float w);
            ModelResult& withH(float h);
            ModelResult& withLabel(std::string label );
            ModelResult& withIsLabel(bool isLabel);
            ModelResult& withProb(float prob);
        protected:

        };

    } // ani
} // android
