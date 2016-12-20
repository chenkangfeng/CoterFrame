
#ifndef CF_I_NET_BUFFER_H
#define CF_I_NET_BUFFER_H

#include "include/cfmacro.h"
#include "kernel/cfinterface.hpp"

NS_CF_BEGIN

// buffer interface
CF_INTERFACE(CFINetBuffer)
{
public:
    CFINetBuffer(void);
    virtual ~CFINetBuffer(void);
};

NS_CF_END

#endif // CF_I_NET_BUFFER_H
