//
// Created by lozpeng on 2024/1/19.
//
#include <jni/jni.hpp>

#include "AniModelResult.hpp"
#include <string>

namespace ani{
    namespace android{
            /**
            *
            */
            void AniModelResult::registerNative(jni::JNIEnv& env)
            {
                static auto& javaClass =
                        jni::Class<AniModelResult>::Singleton(env);

                jni::RegisterNatives(env,
                                     *javaClass,
                                     jni::MakeNativeMethod<decltype(&AniModelResult::DefaultResult),
                                             &AniModelResult::DefaultResult>("DefaultResult"));
            }

            jni::Local<jni::Object<AniModelResult>> AniModelResult::New(jni::JNIEnv& env, const ani::ModelResult& modelResult)
            {
                //AniModelResult(String label,float x,float y,float w,float h,boolean isLabeled,float prob)
                static auto& javaClass = jni::Class<AniModelResult>::Singleton(env);
                static auto constructor = javaClass.GetConstructor<
                                                                    jni::String,    //label
                                                                    jni::jfloat,   //x
                                                                    jni::jfloat,   //y
                                                                    jni::jfloat,   //w
                                                                    jni::jfloat,    //h
                                                                    jni::jboolean,  //islabeled
                                                                    jni::jfloat     //prob
                                                                    >(env);
                //---
                //const jni::String lbl = jni::Make<jni::String>(env, modelResult.label());
                return javaClass.New(
                        env,
                        constructor,
                        jni::Make<jni::String>(env, modelResult.label()),//label
                        modelResult.x(),         //x
                        modelResult.y(),                                  //y
                        jni::jfloat(modelResult.w()),                     //w
                        jni::jfloat(modelResult.h()),                     //h
                        jni::jboolean(modelResult.isLabel()),             //isLabeled
                        jni::jfloat(modelResult.prob()));                 //prob
            }

        jni::Local<jni::Object<AniModelResult>> AniModelResult::DefaultResult(
                                jni::JNIEnv& env, const jni::Class<AniModelResult>& jOptions)
        {
            auto options = ani::ModelResult();
            options.withLabel("C++ Side测试");
            return AniModelResult::New(env, options);
        }
        //
        ani::ModelResult getModelResult(jni::JNIEnv& env, const jni::Object<AniModelResult>& jOptions)
        {
            auto result = ani::ModelResult();
            static auto& javaClass = jni::Class<AniModelResult>::Singleton(env);

            static auto xField = javaClass.GetField<jni::jfloat>(env, "x");
            static auto hField = javaClass.GetField<jni::jfloat>(env, "h");


            auto retVal = ani::ModelResult()
                            .withLabel("test")
                            .withX(jOptions.Get(env,xField))
                            .withH(jOptions.Get(env,hField));

            return retVal;
        }
    }//anroid
}//ani
