
#ifndef CF_SINGLETON_HPP
#define CF_SINGLETON_HPP

#include "include/cfmacro.h"

NS_CF_BEGIN

// singleton type enum
enum class CFSingletonType { kLazy, kFast };

// singleton template
template <typename T, CFSingletonType type = CFSingletonType::kLazy>
class CFSingleton {};

// lazy singleton
template <typename T>
class CFSingleton<T, CFSingletonType::kLazy>
{
public:
    CFSingleton(void) {
        instance_ = static_cast<T*>(this);
    }
    virtual ~CFSingleton(void) {}

    // get singleton instance
    // if it has been release it will init angin
    static T* getInstance(void) {
        return nullptr == instance_ ? new CF_NOTHROW T() : instance_;
    }
    static void releaseInstance(void) {
        CF_SAFE_DELETE(instance_);
    }
private:
    static T* instance_;
};

// lazy singleton init with nullptr
template <typename T>
T* CFSingleton<T, CFSingletonType::kLazy>::instance_ = nullptr;

// fast singleton
template <typename T>
class CFSingleton<T, CFSingletonType::kFast>
{
public:
    CFSingleton(void) {}
    virtual ~CFSingleton(void) {}

    // get singleton instance
    // if it has been release it will return nullptr
    static T* getInstance(void) {
        return instance_;
    }
    static void releaseInstance(void) {
        CF_SAFE_DELETE(instance_);
    }
private:
    static T* instance_;
};

// fast singleton init immediately
template <typename T>
T* CFSingleton<T, CFSingletonType::kFast>::instance_ = new CF_NOTHROW T();

NS_CF_END

#endif // CF_SINGLETON_HPP
