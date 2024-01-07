//
// Created by lozpeng on 2024/1/7.
//

#include "utils.hpp"

namespace ani {
    namespace util {
        void registerNative(jni::JNIEnv& env) {
            jni::Class<Arrays>::Singleton(env);
            jni::Class<List>::Singleton(env);
            jni::Class<Set>::Singleton(env);
            jni::Class<Map>::Singleton(env);
            jni::Class<Map::Entry>::Singleton(env);
        }
    } // namespace util
} // ani