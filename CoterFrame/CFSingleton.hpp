
#ifndef CF_SINGLETON_HPP
#define CF_SINGLETON_HPP

#include "CFMacro.h"

NS_CF_BEGIN

enum class SingletonType {Lazy, Fast};

template <typename T, SingletonType type = SingletonType::Lazy>
class Singleton {};

template <typename T>
class Singleton<T, SingletonType::Lazy>
{
public:
    Singleton(void) {
        _instance = static_cast<T*>(this);
    }
    virtual ~Singleton(void) {}

    static T* getInstance(void) {
        return nullptr == _instance ? new T() : _instance;
    }
    static void releaseInstance(void) {
        CF_SAFE_DELETE(_instance);
    }
private:
    static T* _instance;
};

template <typename T>
T* Singleton<T, SingletonType::Lazy>::_instance = nullptr;

template <typename T>
class Singleton<T, SingletonType::Fast>
{
public:
    Singleton(void) {}
    virtual ~Singleton(void) {}

    static T* getInstance(void) {
        return _instance;
    }
    static void releaseInstance(void) {
        CF_SAFE_DELETE(_instance);
    }
private:
    static T* _instance;
};

template <typename T>
T* Singleton<T, SingletonType::Fast>::_instance = new T();

NS_CF_END

#endif // CF_SINGLETON_HPP
