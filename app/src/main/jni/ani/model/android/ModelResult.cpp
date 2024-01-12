//
// Created by lozpeng on 2024/1/12.
//

#include "ModelResult.hpp"

namespace ani {
    namespace android {
        /**
         *
         */
        void ModelResult::registerNative(jni::JNIEnv& env)
        {
            jni::RegisterNativePeer<android::ModelResult>(env,jni::Class<android::ModelResult>::Find(env),
                                                          "peer",
                                                            jni::MakePeer<android::ModelResult>,
                                                                    "initialize",
                                                    "finalize"
                            );
        }

    } // ani
} // android