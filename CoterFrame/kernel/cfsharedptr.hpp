
#ifndef CF_SHARED_PTR_HPP
#define CF_SHARED_PTR_HPP

#include "include/cfmacro.h"
#include <memory>

// define weak ptr
#define CF_WEAK_PTR std::weak_ptr
#define CF_WEAK_PTR_DECLARE(Type) \
public: \
typedef CF_WEAK_PTR<Type> WeakPtr;

// define shared ptr
#define CF_SHARED_PTR std::shared_ptr
#define CF_SHARED_PTR_DECLARE(Type) \
public: \
typedef CF_SHARED_PTR<Type> SharedPtr;

NS_CF_BEGIN

// weak ptr class
template <typename T>
class CFWeakPtr
{
public:
    CF_WEAK_PTR_DECLARE(T)
};

// shared ptr template
template <typename T, CFBool enable_shared_from_this = false>
class CFSharedPtr {};

// shared ptr class
template <typename T>
class CFSharedPtr<T, false>
{
    CF_SHARED_PTR_DECLARE(T)
};

// shared ptr class with enable shared from this
template <typename T>
class CFSharedPtr<T, true> : public std::enable_shared_from_this<T>
{
    CF_SHARED_PTR_DECLARE(T)
};

NS_CF_END

#endif // CF_SHARED_PTR_HPP
