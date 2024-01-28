//
// Created by lozpeng on 2024/1/8.
//

#include "ModelInfo.hpp"
#include "jni/jni.hpp"
#include <optional>
#include "ani_jni.hpp"

namespace ani {
    namespace android {
       class ModelInfo::MImpl{
           public:
               std::string modelId;             //模型编号
               std::string modelName;           //模型名称
               std::string inputName;           //输入名称
               std::string outputName;          //输出名称
               int classes;                     //类数量
               int cpuGpu;                      //使用CPU或GPU
               int targetSize;                  //目标大小
               std::vector<float>  meanVals;   //数组，
               std::vector<float>  normals;    //数组
        };
        ModelInfo::ModelInfo(jni::JNIEnv& env)
                : impl_(std::make_unique<ModelInfo::MImpl>())
        {
            //std::string s = jni::Make<std::string>(env,str);
            impl_->inputName="images";
            impl_->outputName = "output";
            impl_->targetSize = 320;
            //--mean values
            impl_->meanVals.push_back(103.53f);
            impl_->meanVals.push_back(116.28f);
            impl_->meanVals.push_back(123.675f);
            //--
            impl_->normals.push_back(1 / 255.f);
            impl_->normals.push_back(1 / 255.f);
            impl_->normals.push_back(1 / 255.f);
        }

        ModelInfo::ModelInfo() : impl_(std::make_unique<ModelInfo::MImpl>()){
            impl_->inputName="images";
            impl_->outputName = "output";
            impl_->targetSize = 320;
            //--mean values
            impl_->meanVals.push_back(103.53f);
            impl_->meanVals.push_back(116.28f);
            impl_->meanVals.push_back(123.675f);
            //--
            impl_->normals.push_back(1 / 255.f);
            impl_->normals.push_back(1 / 255.f);
            impl_->normals.push_back(1 / 255.f);
        }
        /**
         *
         * @param modelId
         */
        void ModelInfo::setModelId(jni::JNIEnv& env,const jni::String& modelId)
        {
            impl_->modelId = jni::Make<std::string>(env,modelId);
        }
        /**
         *
         * @param env
         * @return
         */
        jni::Local<jni::String> ModelInfo::getModelId(jni::JNIEnv& env)
        {
            return jni::Make<jni::String>(env, impl_->modelId);
        }

        void ModelInfo::setModelName(jni::JNIEnv& env,const jni::String& modelName)
        {
            impl_->modelName=jni::Make<std::string>(env,modelName);
        }
        jni::Local<jni::String> ModelInfo::getModelName(jni::JNIEnv& env)
        {
            return jni::Make<jni::String>(env, impl_->modelName);
        }

        void ModelInfo::setInputName(jni::JNIEnv& env,const jni::String& inputName)
        {
            impl_->inputName = jni::Make<std::string>(env,inputName);
        }
        jni::Local<jni::String> ModelInfo::getInputName(jni::JNIEnv& env)
        {
            return jni::Make<jni::String>(env, impl_->inputName);
        }
        void ModelInfo::setOutputName(jni::JNIEnv& env,const jni::String& outputName)
        {
            impl_->outputName = jni::Make<std::string>(env,outputName);
        }
        jni::Local<jni::String> ModelInfo::getOutputName(jni::JNIEnv& env)
        {
            return jni::Make<jni::String>(env, impl_->outputName);
        }

        void ModelInfo::setIsGPUCPU(jni::JNIEnv& env,const jni::Boolean& gpuCpu)
        {
            impl_->cpuGpu = jni::Unbox(env,gpuCpu)?1:0;
        }
        jni::Local<jni::Boolean> ModelInfo::getIsGPUCPU(jni::JNIEnv& env){
           return jni::Box(env,this->impl_->cpuGpu==1?jni::jboolean(true):jni::jboolean(false));
        }
        void ModelInfo::setClasses(jni::JNIEnv& env,const jni::Integer& classes){
            impl_->classes = jni::Unbox(env,classes);
        }
        jni::Local<jni::Integer> ModelInfo::getClasses(jni::JNIEnv& env) {
            return jni::Box(env, this->impl_->classes);
        }

        void ModelInfo::setMeanVals(jni::JNIEnv& env,const jni::Array<jni::Float>& meanVals){
            jsize size = meanVals.Length(env);
            for(jsize i=0;i<size;i++)
            {
                float x = jni::Unbox(env,meanVals.Get(env,i));
                impl_->meanVals.push_back(x);
            }
        }
        jni::Local<jni::Array<jni::Float>> ModelInfo::getMeanVals(jni::JNIEnv& env){
            std::vector<float> values = impl_->meanVals;
            //if(values.size()<=0)return ;

            auto result = jni::Array<jni::Float>::New(env, values.size());

            for (std::size_t i = 0; i < values.size(); i++) {
                result.Set(env, i, jni::Box(env, values.at(i)));
            }
            return result;
        }

        void ModelInfo::setNormalVals(jni::JNIEnv& env,const jni::Array<jni::Float>& normalVals){
            jsize size = normalVals.Length(env);
            for(jsize i=0;i<size;i++)
            {
                float x = jni::Unbox(env,normalVals.Get(env,i));
                impl_->normals.push_back(x);
            }
        }
        /**
         *
         * @param env
         * @return
         */
        jni::Local<jni::Array<jni::Float>> ModelInfo::getNormalVals(jni::JNIEnv& env)
        {
            std::vector<float> values = impl_->normals;
            if(values.size()<=0)return jni::Local<jni::Array<jni::Float>>(env,nullptr);

            auto result = jni::Array<jni::Float>::New(env, values.size());

            for (std::size_t i = 0; i < values.size(); i++) {
                result.Set(env, i, jni::Box(env, values.at(i)));
            }
            return result;
        }
        void ModelInfo::setTargetSize(jni::JNIEnv& env,const jni::Integer& targetSize)
        {
            impl_->targetSize = jni::Unbox(env,targetSize);
        }
        jni::Local<jni::Integer> ModelInfo::getTargetSize(jni::JNIEnv& env)
        {
           return jni::Box(env,impl_->targetSize);
        }
        /**
         * 注册
         * @param env
         */
        void ModelInfo::registerNative(jni::JNIEnv& env)
        {
            static auto& javaClass = jni::Class<ModelInfo>::Singleton(env);

            #define METHOD(MethodPtr, name) jni::MakeNativePeerMethod<decltype(MethodPtr), (MethodPtr)>(name)
            /**
             * 注册链接C++和java端函数
             */
            jni::RegisterNativePeer<ModelInfo>(
                                  env,
                                  javaClass,
                                  "nativePtr",
                                    METHOD(&ModelInfo::setModelName,"setModelName"),  //需要将方法定义为const jni:: & 类型
                                    METHOD(&ModelInfo::getModelName,"getModelName"),
                                    METHOD(&ModelInfo::setModelId,"setModelId"),
                                    METHOD(&ModelInfo::getModelId,"getModelId"),
                                    METHOD(&ModelInfo::setInputName,"setInputName"),
                                    METHOD(&ModelInfo::getInputName,"getInputName"),
                                    METHOD(&ModelInfo::setOutputName,"setOutputName"),
                                    METHOD(&ModelInfo::getOutputName,"getOutputName"),
                                    METHOD(&ModelInfo::setIsGPUCPU,"setGPUCUP"),
                                    METHOD(&ModelInfo::getIsGPUCPU,"getGPUCUP"),
                                    METHOD(&ModelInfo::setClasses,"setClasses"),
                                    METHOD(&ModelInfo::getClasses,"getClasses"),
                                    METHOD(&ModelInfo::setMeanVals,"setMeanVals"),
                                    METHOD(&ModelInfo::getMeanVals,"getMeanVals"),
                                    METHOD(&ModelInfo::setTargetSize,"setTargetSize"),
                                    METHOD(&ModelInfo::getTargetSize,"getTargetSize"),
                                    METHOD(&ModelInfo::setNormalVals,"setNormalVals"),
                                    METHOD(&ModelInfo::getNormalVals,"getNormalVals")
                                 );
        }
    }
} // ani