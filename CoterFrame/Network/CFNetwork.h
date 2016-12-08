
#ifndef CF_NETWORK_H
#define CF_NETWORK_H

#include "CFPrecompiled.h"
#include "event.h"

NS_CF_BEGIN

class CFNetwork
{
public:
    CFNetwork(void);
    virtual ~CFNetwork(void);

    CFBool isUseThread(void);

    virtual void mainLoop(void);
protected:
    virtual void _closeNetwork(void);

    CFBool _isRunning;
    CFBool _isUseThread;
    struct event_base* _base;
};

NS_CF_END

#endif // CF_NETWORK_H
