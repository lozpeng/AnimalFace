//
// Created by lozpeng on 2024/1/15.
//

#ifndef ANIMALFACE_COLLECTION_HPP
#define ANIMALFACE_COLLECTION_HPP

#include <jni/jni.hpp>

#include <vector>

namespace ani {
    namespace andriod {
        namespace conversion{
            std::vector<std::string> toVector(JNIEnv& env, const jni::Array<jni::String>& array);
            jni::Local<jni::Array<jni::String>> toArray(JNIEnv& env, const std::vector<std::string>&);
        }
    }
}


#endif //ANIMALFACE_COLLECTION_HPP
