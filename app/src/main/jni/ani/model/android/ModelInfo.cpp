//
// Created by lozpeng on 2024/1/8.
//

#include "ModelInfo.hpp"
#include "jni/jni.hpp"
#include <optional>
#include "ani_jni.hpp"
#include <vector>
#include <string>
#include <memory>

namespace ani {
    namespace android {
        /**
         * 注册
         * @param env
         */
        void ModelInfo::registerNative(jni::JNIEnv& env)
        {
            jni::Class<ModelInfo>::Singleton(env);
        }

        jni::Local<jni::Object<ModelInfo>> ModelInfo::New(jni::JNIEnv& env, const ani::ModelInfo& cModelInfo)
        {
            static auto& javaClass = jni::Class<ModelInfo>::Singleton(env);
            static auto constructor = javaClass.GetConstructor<
                    jni::String,    //modelId
                    jni::String,    //modelName
                    jni::String,    //inputName
                    jni::String,    //outputName
                    jni::Integer,   //classes
                    jni::Integer,   //cpu
                    jni::Integer,   //targetSize
                    jni::Array<jni::Float>,    //meanvalues
                    jni::Array<jni::Float>  //normals
            >(env);
            auto values = cModelInfo.getMeanVals();
            auto jMeanVals = jni::Array<jni::Float>::New(env, values.size());
            for (std::size_t i = 0; i < values.size(); i++) {
                jMeanVals.Set(env, i, jni::Box(env, values.at(i)));
            }
            auto normVals = cModelInfo.getNormals();
            auto jNormVals = jni::Array<jni::Float>::New(env, normVals.size());
            for (std::size_t i = 0; i < normVals.size(); i++) {
                jNormVals.Set(env, i, jni::Box(env, normVals.at(i)));
            }
            //---
            return javaClass.New(
                    env,
                    constructor,
                    jni::Make<jni::String>(env, cModelInfo.getModelId()),//modelId
                    jni::Make<jni::String>(env, cModelInfo.getModelName()),//modelName
                    jni::Make<jni::String>(env, cModelInfo.getInputName()),//inputName
                    jni::Make<jni::String>(env, cModelInfo.getOutpuName()),//outputName
                    jni::Box(env,cModelInfo.getClasses()),  //classes
                    jni::Box(env,cModelInfo.getCpuGPU()),  //cpu
                    jni::Box(env,cModelInfo.getTargetSize()),  //targetSize
                    jMeanVals,                   //mean values
                    jNormVals);                 //normal values
        }

        size_t ModelInfo::toStdFloatVector(jni::JNIEnv& env,const jni::Array<jni::Float>& jVals,
                                                                std::vector<float>& values)
        {
            //jni::NullCheck(env,&jVals);
            jni::jsize size = jVals.Length(env);
            values.reserve(size);
            for(int i=0;i<size;i++)
            {
                float f= jni::Unbox(env,jVals.Get(env,i));
                values.push_back(f);
            }
            return values.size();
        }
        /**
         * 从java的对象转换为C++对象
         * @param env
         * @param jModeInfo
         * @return
         */
        ani::ModelInfo ModelInfo::getModelInfo(jni::JNIEnv& env , const jni::Object<ModelInfo>& jModelInfo){
            auto opts = ani::ModelInfo();
            static auto& javaClass = jni::Class<ModelInfo>::Singleton(env);

            static auto modelIdField = javaClass.GetField<jni::String>(env, "modelId");
            static auto modelNameField = javaClass.GetField<jni::String>(env, "modelName");
            static auto inputNameField = javaClass.GetField<jni::String>(env, "inputName");
            static auto outputField = javaClass.GetField<jni::String>(env, "outputName");

            static auto classesField = javaClass.GetField<jni::Integer>(env,"classes");
            static auto cpuField = javaClass.GetField<jni::Integer>(env,"cpuGpu");
            static auto targetSizeField = javaClass.GetField<jni::Integer>(env,"targetSize");

            static auto meanValsFields  =javaClass.GetField<jni::Array<jni::Float>>(env,"meanVals");
            static auto normValsFields  =javaClass.GetField<jni::Array<jni::Float>>(env,"normals");

            //auto jMeans = jModelInfo.Get(env,meanValsFields);
            //====mean values
            std::vector<float> means;
            toStdFloatVector(env,jModelInfo.Get(env,meanValsFields),means);
            //==== normal values
            std::vector<float> normals;
            toStdFloatVector(env,jModelInfo.Get(env,normValsFields),normals);

            auto retVal = ani::ModelInfo()
                    .withModelName(jni::Make<std::string>(env, jModelInfo.Get(env, modelNameField)))
                    .withInputName(jni::Make<std::string>(env, jModelInfo.Get(env, inputNameField)))
                    .withOutpuName(jni::Make<std::string>(env, jModelInfo.Get(env, outputField)))
                    .withModelId(jni::Make<std::string>(env, jModelInfo.Get(env, modelIdField)))
                    .withClasses(jni::Unbox(env,jModelInfo.Get(env,classesField)))
                    .withCPUGPU(jni::Unbox(env,jModelInfo.Get(env,cpuField)))
                    .withTargetSize(jni::Unbox(env,jModelInfo.Get(env,targetSizeField)))
                    .withMeanVals(means)
                    .withNormals(normals)
                    ;
            return retVal;
        }

        ModelInfo:: ~ModelInfo()=default;
    }
} // ani