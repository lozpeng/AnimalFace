#include "attach_env.hpp"
#include "../../ani_jni.hpp"

namespace ani {
    namespace android {
            /**
             * @return
             */
            UniqueEnv AttachEnv() {
                assert(theJVM);

                JNIEnv* env = nullptr;
                jint err = theJVM->GetEnv(reinterpret_cast<void**>(&env), JNI_VERSION_1_6);
                switch (err) {
                    case JNI_OK:
                        return UniqueEnv(env, JNIEnvDeleter(*theJVM, false));
                    case JNI_EDETACHED:
                        return UniqueEnv(jni::AttachCurrentThread(*theJVM).release(), JNIEnvDeleter(*theJVM, true));
                    default:
                        throw std::system_error(err, jni::ErrorCategory());
                }
            }
        } // namespace android
} // namespace ani
