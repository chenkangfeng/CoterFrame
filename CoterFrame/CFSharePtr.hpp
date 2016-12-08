
#ifndef CF_SHARE_PTR_HPP
#define CF_SHARE_PTR_HPP

#include "CFPrecompiled.h"
#include <memory>

NS_CF_BEGIN

template <typename T, bool isEnableSharedFromThis = false>
class CFSharePtr {};

template <typename T>
class CFSharePtr<T, false>
{
public:
    typedef std::weak_ptr<T> WeakPtr;
    typedef std::shared_ptr<T> SharePtr;
};

template <typename T>
class CFSharePtr<T, true> : public std::enable_shared_from_this<T>
{
public:
    typedef std::weak_ptr<T> WeakPtr;
    typedef std::shared_ptr<T> SharePtr;
};

NS_CF_END

#endif // CF_SHARE_PTR_HPP
