
#ifndef CF_SINGLETON_HPP
#define CF_SINGLETON_HPP

#include "include/cfmacro.h"

NS_CF_BEGIN

enum class SingletonType { kLazy, kFast };

template <typename T, SingletonType type = SingletonType::kLazy>
class Singleton {};

template <typename T>
class Singleton<T, SingletonType::kLazy>
{
public:
    Singleton(void) {
        instance_ = static_cast<T*>(this);
    }
    virtual ~Singleton(void) {}

    static T* getInstance(void) {
        return nullptr == instance_ ? new CF_NOTHROW T() : instance_;
    }
    static void releaseInstance(void) {
        CF_SAFE_DELETE(instance_);
    }
private:
    static T* instance_;
};

template <typename T>
T* Singleton<T, SingletonType::kLazy>::instance_ = nullptr;

template <typename T>
class Singleton<T, SingletonType::kFast>
{
public:
    Singleton(void) {}
    virtual ~Singleton(void) {}

    static T* getInstance(void) {
        return instance_;
    }
    static void releaseInstance(void) {
        CF_SAFE_DELETE(instance_);
    }
private:
    static T* instance_;
};

template <typename T>
T* Singleton<T, SingletonType::kFast>::instance_ = new CF_NOTHROW T();

NS_CF_END

#endif // CF_SINGLETON_HPP
