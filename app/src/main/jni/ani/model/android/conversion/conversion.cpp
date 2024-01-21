//
// Created by lozpeng on 2024/1/15.
//
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
            jni::Local<jni::String> toJniString(jni::JNIEnv& env,const std::string str)
            {
                return jni::Make<jni::String>(env, str);
            }
            /**
             *
             * @param env
             * @param value
             * @return
             */
            jni::Local<jni::Boolean> toJniBoolean(jni::JNIEnv& env,const bool& value)
            {
                return jni::Box(env, value ? jni::jni_true : jni::jni_false);
            }
            /**
             *
             * @param env
             * @param value
             * @return
             */
            jni::Local<jni::Float> toJniFloat(jni::JNIEnv& env,const float& value)
            {
                return jni::Box(env, value);
            }
            /**
             *
             * @param env
             * @param value
             * @return
             */
            jni::Local<jni::Array<jni::String>> toJniStringArray(jni::JNIEnv& env,
                                                                        const std::vector<std::string>& value)
            {
                auto result = jni::Array<jni::String>::New(env, value.size());

                for (std::size_t i = 0; i < value.size(); i++) {
                    result.Set(env, i, jni::Make<jni::String>(env, value.at(i)));
                }
                return result;
            }

            jni::Local<jni::Array<jni::Float>> toJniFloatArray(jni::JNIEnv& env,const std::vector<float>& value){
                auto result = jni::Array<jni::Float>::New(env, value.size());

                for (std::size_t i = 0; i < value.size(); i++) {
                    result.Set(env, i, jni::Box(env, value.at(i)));
                }

                return result;
            }
            jni::Local<jni::Array<jni::Double>> toJniDoubleArray(jni::JNIEnv& env,const std::vector<double>& value){
                auto result = jni::Array<jni::Double>::New(env, value.size());

                for (std::size_t i = 0; i < value.size(); i++) {
                    result.Set(env, i, jni::Box(env, value.at(i)));
                }
                return result;
            }
        }
    }
}