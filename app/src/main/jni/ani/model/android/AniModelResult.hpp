//
// Created by lozpeng on 2024/1/19.
//

#ifndef ANIMALFACE_ANIMODELRESULT_HPP
#define ANIMALFACE_ANIMODELRESULT_HPP
#include <jni/jni.hpp>
#include "../utils/noncopyable.hpp"
#include "../ModelResult.hpp"
namespace ani{
    namespace android{
/**
 * 与java端联动
 */
class AniModelResult : private ani::util::noncopyable{
        public:
            static constexpr auto Name(){return "org/cwcc/ani/ai/model/AniModelResult";};
            /**
            *
            */
            static void registerNative(jni::JNIEnv& env);
            /**
             * C++ side try to new a java side object
             * @param env
             * @return
             */
            static jni::Local<jni::Object<AniModelResult>> New(jni::JNIEnv& env, const ani::ModelResult&);

            static jni::Local<jni::Object<AniModelResult>> DefaultResult(
                            jni::JNIEnv& env, const jni::Class<AniModelResult>& jOptions);

            //从java对象转C++对象。硬拷贝方式
            static ani::ModelResult getModelResult(jni::JNIEnv&, const jni::Object<AniModelResult>&);

};
    }//anroid
}//ani

#endif //ANIMALFACE_ANIMODELRESULT_HPP
