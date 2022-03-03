#ifndef __SINGLETON_H__
#define __SINGLETON_H__

#include "hiccup/hiccup.h"

HICCUP_BEGIN

template<typename T>
struct Singleton {
    static T& getInstance() {
        static T instance;
        return instance;
    }
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

protected:
    Singleton() noexcept = default;
};

#define SINGLETON(ClassName) struct ClassName : ::HICCUP_NS::Singleton<ClassName>
HICCUP_END

#endif