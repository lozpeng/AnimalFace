//
// Created by lozpeng on 2024/1/15.
//

#ifndef ANIMALFACE_CONVERSION_HPP
#define ANIMALFACE_CONVERSION_HPP
#include <jni/jni.hpp>

#include <string>

namespace ani {
    namespace andriod {
        namespace conversion{
            /**
             *
             * @param env
             * @param str
             * @return
             */
            static jni::Local<jni::String> toJniString(jni::JNIEnv& env,const std::string str);
            /**
             *
             * @param env
             * @param value
             * @return
             */
            static jni::Local<jni::Boolean> toJniBoolean(jni::JNIEnv& env,const bool& value);
            /**
             *
             * @param env
             * @param value
             * @return
             */
            static jni::Local<jni::Float> toJniFloat(jni::JNIEnv& env,const float& value);
            /**
             *
             * @param env
             * @param value
             * @return
             */
            static jni::Local<jni::Array<jni::String>> toJniStringArray(jni::JNIEnv& env,
                                                                        const std::vector<std::string>& value);
            /**
             *
             * @param env
             * @param value
             * @return
             */
            static jni::Local<jni::Array<jni::Float>> toJniFloatArray(jni::JNIEnv& env,const std::vector<float>& value);

            /**
             *
             * @param env
             * @param value
             * @return
             */
            static jni::Local<jni::Array<jni::Float>> toJniDoubleArray(jni::JNIEnv& env,const std::vector<double>& value);
        }
    }
}

#endif //ANIMALFACE_CONVERSION_HPP
