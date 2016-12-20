
#ifndef CF_I_NET_OBJECT_H
#define CF_I_NET_OBJECT_H

#include "include/cfmacro.h"
#include "kernel/cfinterface.hpp"
#include "cfnetwork.h"
#include "cfinetaddr.h"
#include "cfinetbuffer.h"

NS_CF_BEGIN

// object interface
CF_INTERFACE(CFINetObject, CFNetwork, CFINetAddr::SharedPtr, CFINetBuffer::SharedPtr)
{
public:
    CFINetObject(CFNetwork*, CFINetAddr::SharedPtr, CFINetBuffer::SharedPtr) {}
    virtual ~CFINetObject(void) {}

    // get object addr
    virtual const CFINetAddr::SharedPtr& addr(void) const = 0;
};

NS_CF_END

#endif // CF_I_NET_OBJECT_H
