//
// Created by lozpeng on 2024/1/12.
//

#include "ModelResult.hpp"
#include "attach_env.hpp"

namespace ani {
    namespace android {
        class ModelResult::Impl{
        public:
            float x;  //监测的结果起始位置
            float y; //监测的结果起始位置
            float w; //目标物在图像的宽度
            float h; //目标物在图像的高度
            bool isLabel;// 标识是否为标识
            float prob;     //目标识别结果置信度
            std::string label; //目标物注释
        };
        ModelResult::ModelResult(JNIEnv& env)
                :impl_(std::make_unique<ModelResult::Impl>())
                {
                    //javaPeer(jni::NewGlobal(env,impl_));
                }

        ModelResult::~ModelResult()
        {
//            if(javaPeer.get()!=nullptr)
//            {
//                android::UniqueEnv env = android::AttachEnv();
//                static auto& javaClass = jni::Class<ModelResult>::Singleton(*env);
//                static auto nativePtrField = javaClass.GetField<jlong>(*env, "nativePtr");
//                javaPeer.Set(*env, nativePtrField, (jlong)0);
//                javaPeer.reset();
//            }
        }
        /**
         *
         */
        void ModelResult::registerNative(jni::JNIEnv& env)
        {
            static auto& javaClass = jni::Class<ModelResult>::Singleton(env);
            #define AMETHOD(MethodPtr, name) jni::MakeNativePeerMethod<decltype(MethodPtr), (MethodPtr)>(name)

            jni::RegisterNativePeer<ModelResult>(
                        env,
                        javaClass,
                        "nativePtr",
                        AMETHOD(&ModelResult::getId, "nativeGetId"),
                        AMETHOD(&ModelResult::getX, "nativeGetX"),
                        AMETHOD(&ModelResult::getY, "nativeGetY"),
                        AMETHOD(&ModelResult::getW, "nativeGetW"),
                        AMETHOD(&ModelResult::getH, "nativeGetH"),
                        AMETHOD(&ModelResult::getProb, "nativeGetProb"),
                        AMETHOD(&ModelResult::getLabel, "nativeGetLabel")
                    );
        }

        jni::Local<jni::String> ModelResult::getId(jni::JNIEnv& env)
        {
            return jni::Make<jni::String>(env,impl_->label);
        }


        ModelResult&  ModelResult::withX(float x)
        {
            impl_->x = x;
            return *this;
        }

        jni::Local<jni::Float> ModelResult::getX(jni::JNIEnv& env)
        {
            return jni::Box(env, impl_->x);
        }

        ModelResult&  ModelResult::withY(float y)
        {
            impl_->y = y;
            return *this;

        }

        jni::Local<jni::Float> ModelResult::getY(jni::JNIEnv& env)
        {
            return jni::Box(env, impl_->y);
        }

        ModelResult&  ModelResult::withW(float w)
        {
            impl_->w = w;
            return *this;
        }
        jni::Local<jni::Float> ModelResult::getW(jni::JNIEnv& env)
        {
            return jni::Box(env,impl_->w);
        }


        ModelResult&  ModelResult::withH(float h)
        {
            impl_->h = h;
            return *this;
        }
        jni::Local<jni::Float> ModelResult::getH(jni::JNIEnv& env)
        {
            return jni::Box(env,impl_->h);
        }

        ModelResult&  ModelResult::withLabel(std::string label )
        {
            impl_->label = std::move(label);
            return *this;
        }
        jni::Local<jni::String>  ModelResult::getLabel(jni::JNIEnv& env)
        {
           return jni::Make<jni::String>(env,impl_->label);
        }

        ModelResult&  ModelResult::withIsLabel(bool isLabel) {
            impl_->isLabel = isLabel;
            return *this;
        }

        ModelResult&  ModelResult::withProb(float prob) {
            impl_->prob = prob;
            return *this;
        }

        jni::Local<jni::Float> ModelResult::getProb(jni::JNIEnv& env)
        {
            return jni::Box(env,impl_->prob);
            //return jni::Local<jni::Integer>(env, nullptr);
        }

    } // ani
} // android