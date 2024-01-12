//
// Created by lozpeng on 2024/1/8.
//

#include "ModelInfo.hpp"
#include "jni/jni.hpp"
#include <optional>
#include "ani_jni.hpp"

namespace ani {
    namespace andriod {
        jni::Local <jni::Object<ModelInfo>> ModelInfo::New(jni::JNIEnv &env, const ani::ModelInfo &modelInfo) {
            /**
             *
             */
            static auto &javaClass = jni::Class<ModelInfo>::Singleton(env);
            /**
             *
             */
            static auto constructor = javaClass.GetConstructor<
                    jni::String,    //modelId
                    jni::String,    //modelName
                    jni::String,    //inputName
                    jni::String,    //outputName
                    jni::jint,      //cpuGpu
                    jni::jint,      //targetSize
                    jni::jint//,      //classes
                    ,jni::Array<jni::jfloat>
                    ,jni::Array<jni::jfloat>
                    >
                    (env);
            //如果给定值是可选 即可以为空
            //std::optional<std::string> sourceVersionPrefixValue = tileServerOptions.sourceVersionPrefix();
            //styleVersionPrefixValue ? jni::Make<jni::String>(env, *styleVersionPrefixValue)
            //                                            : jni::Local<jni::String>(),
            //jfloatarray -> std::vctor<float> means
            //jfloatArray jmeanVals = env.NewFloatArray(modelInfo.meanVals().size());
            //env.SetFloatArrayRegion(jmeanVals, 0, modelInfo.meanVals().size(),
            //                                            modelInfo.meanVals().data());
            //normals
            //jfloatArray jnormals = env.NewFloatArray(modelInfo.meanVals().size());
            //env.SetFloatArrayRegion(jnormals, 0, modelInfo.normals().size(),
            //                        modelInfo.normals().data());
            //env.NewFloatArray(modelInfo.meanVals().size());
            //--meanvals
            auto value = modelInfo.meanVals();
            auto jniMeanVals= jni::Array<jni::jfloat>::New(env,value.size());
            for (std::size_t i = 0; i < value.size(); i++) {
                jniMeanVals.Set(env, i, value.at(i));
            }
            //--normals
            value = modelInfo.normals();
            auto jniNormalVals=jni::Array<jni::jfloat>::New(env,value.size());
            for (std::size_t i = 0; i < value.size(); i++) {
                jniNormalVals.Set(env, i, value.at(i));
            }
            return javaClass.New(
                    env,
                    constructor,
                    jni::Make<jni::String>(env,modelInfo.modelId()),
                    jni::Make<jni::String>(env,modelInfo.modelName()),
                    jni::Make<jni::String>(env,modelInfo.inputName()),
                    jni::Make<jni::String>(env,modelInfo.outputName()),
                    jni::jint(modelInfo.gpu()),
                    jni::jint(modelInfo.targetSize()),
                    jni::jint(modelInfo.classes()),
                    jniMeanVals,
                    jniNormalVals
                   );
        }

        jni::Local <jni::Object<ModelInfo>> ModelInfo::DefaultModelInfo(
                jni::JNIEnv &env, const jni::Class <ModelInfo> &jmodelInfo) {
            auto modelInfo = ani::ModelInfo::DefaultModelInfo();
            return ModelInfo::New(env, modelInfo);
        }
        /**
         *  从java 的对象转换为c++的对象
         * @param jModelInfo
         * @return
         */
        ani::ModelInfo ModelInfo::getModelInfo(jni::JNIEnv& env, const jni::Object<ModelInfo>& jModelInfo)
        {
            auto mdlInfo = ani::ModelInfo(); //创建一个C++的ModelInfo对象

            static auto& javaClass =jni::Class<ModelInfo>::Singleton(env);

            static auto modelIdField  = javaClass.GetField<jni::String>(env,"ModelId");
            static auto modelNameField = javaClass.GetField<jni::String>(env,"ModelName");
            static auto inputNameField = javaClass.GetField<jni::String>(env,"InputName");
            static auto outputNameField = javaClass.GetField<jni::String>(env,"OutputName");
            static auto gpuCpuField = javaClass.GetField<jni::jint>(env,"GPUCPU");
            static auto targetSizeField = javaClass.GetField<jni::jint>(env,"TargetSize");
            static auto classesField = javaClass.GetField<jni::jint>(env,"Classes");
            static auto meanValField = javaClass.GetField<jni::Array<jni::jfloat>>(env,"MeanVals");
            static auto normalValField = javaClass.GetField<jni::Array<jni::jfloat>>(env,"Normals");

            auto retVal = ani::ModelInfo()
                    .withModelId(jni::Make<std::string>(env,jModelInfo.Get(env,modelIdField)))
                    .withModelName(jni::Make<std::string>(env,jModelInfo.Get(env,modelNameField)))
                    .withInputName(jni::Make<std::string>(env,jModelInfo.Get(env,inputNameField)))
                    .withOutputName(jni::Make<std::string>(env,jModelInfo.Get(env,outputNameField)))
                    .withCpuGPU(jModelInfo.Get(env,gpuCpuField))
                    .withTargetSize(jModelInfo.Get(env,targetSizeField))
                    .withClasses(jModelInfo.Get(env,classesField))
                    .withMeanVals(jni::Make<std::vector<float>>(env, jModelInfo.Get(env,meanValField)))
                    .withNormals(jni::Make<std::vector<float>>(env, jModelInfo.Get(env,normalValField)))
                    ;
            return retVal;
        }
        /**
         * 注册
         * @param env
         */
        void ModelInfo::registerNative(jni::JNIEnv& env)
        {
            static auto& javaClass = jni::Class<ModelInfo>::Singleton(env);
            jni::RegisterNatives(env,
                                 *javaClass,
                                 ANI_METHOD(&ModelInfo::DefaultModelInfo,"defaultModelInfo"));
 //                                jni::MakeNativeMethod<decltype(&ModelInfo::DefaultModelInfo),
 //                                        &ModelInfo::DefaultModelInfo>("defaultModelInfo"));
        }
    }
} // ani