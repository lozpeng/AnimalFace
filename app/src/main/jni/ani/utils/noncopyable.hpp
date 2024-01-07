#pragma once
//
// Created by lozpeng on 2024/1/7.
//
namespace ani{
    namespace util
    {
        namespace non_copyable_ {
            class noncopyable {
            public:
                noncopyable(noncopyable const&) = delete;
                noncopyable& operator=(noncopyable const&) = delete;

            protected:
                constexpr noncopyable() = default;
                ~noncopyable() = default;
            };
        } // namespace non_copyable_

        using noncopyable = non_copyable_::noncopyable;
    }//namespace util
}//namespace ani
