#pragma once
//
// Created by lozpeng on 2024/1/7.
//
#include <jni/jni.hpp>
#include "noncopyable.hpp"
namespace ani {
    namespace util{
        class List : private ani::util::noncopyable {
        public:
            static constexpr auto Name() { return "java/util/List"; };

            template <class T>
            static jni::Local<jni::Array<jni::Object<T>>> toArray(jni::JNIEnv& env, const jni::Object<List>& list) {
                static auto& javaClass = jni::Class<List>::Singleton(env);
                static auto toArray = javaClass.GetMethod<jni::Array<jni::Object<>>()>(env, "toArray");

                return jni::Local<jni::Array<jni::Object<T>>>(env, list.Call(env, toArray).release());
            };
        };

        class Arrays : private ani::util::noncopyable {
        public:
            static constexpr auto Name() { return "java/util/Arrays"; };

            template <class T>
            static jni::Local<jni::Object<List>> asList(jni::JNIEnv& env, const jni::Array<jni::Object<T>>& array) {
                static auto& javaClass = jni::Class<Arrays>::Singleton(env);
                static auto asList = javaClass.GetStaticMethod<jni::Object<List>(jni::Array<jni::Object<>>)>(env, "asList");

                auto typeErasedArray = jni::Local<jni::Array<jni::Object<>>>(env, jni::NewLocal(env, array).release());
                return javaClass.Call(env, asList, typeErasedArray);
            }
        };

        class Set : private ani::util::noncopyable {
        public:
            static constexpr auto Name() { return "java/util/Set"; };

            template <class T>
            static jni::Local<jni::Array<jni::Object<T>>> toArray(jni::JNIEnv& env, const jni::Object<Set>& list) {
                static auto& javaClass = jni::Class<Set>::Singleton(env);
                static auto toArray = javaClass.GetMethod<jni::Array<jni::Object<>>()>(env, "toArray");

                return jni::Local<jni::Array<jni::Object<T>>>(env, list.Call(env, toArray).release());
            };
        };

        class Map : private ani::util::noncopyable {
        public:
            static constexpr auto Name() { return "java/util/Map"; };

            class Entry : private ani::util::noncopyable {
            public:
                static constexpr auto Name() { return "java/util/Map$Entry"; };

                template <class T>
                static jni::Local<jni::Object<T>> getKey(jni::JNIEnv& env, const jni::Object<Entry>& entry) {
                    static auto& javaClass = jni::Class<Map::Entry>::Singleton(env);
                    static auto method = javaClass.GetMethod<jni::Object<>()>(env, "getKey");
                    return jni::Cast(env, jni::Class<T>::Singleton(env), entry.Call(env, method));
                }

                template <class T>
                static jni::Local<jni::Object<T>> getValue(jni::JNIEnv& env, const jni::Object<Entry>& entry) {
                    static auto& javaClass = jni::Class<Map::Entry>::Singleton(env);
                    static auto method = javaClass.GetMethod<jni::Object<>()>(env, "getValue");
                    return jni::Cast(env, jni::Class<T>::Singleton(env), entry.Call(env, method));
                }
            };
        };

        void registerNative(jni::JNIEnv&);
    } //namespace util
} // ani
