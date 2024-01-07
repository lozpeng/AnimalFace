#pragma once
//
// Created by lozpeng on 2024/1/7.
//
#include "ani_jni.hpp"

#include <string>

#include <jni.h>
#include "jni/jni.hpp"

namespace ani{
    //!注册一些
    ANI_EXPORT void registerNatives(JavaVM* vm);
}

