
#include "CFPrecompiled.h"
#include "CFNetwork.h"

NS_CF_BEGIN

CFNetwork::CFNetwork(void) :
_isRunning(false),
_isMultiThread(false),
_base(nullptr)
{
}

CFNetwork::~CFNetwork(void)
{
    _closeNetwork();
}

CFBool CFNetwork::isMultiThread(void)
{
    return _isMultiThread;
}

void CFNetwork::mainLoop(void)
{
    if (_isRunning && nullptr != _base) {
        event_base_loop(_base, EVLOOP_ONCE | EVLOOP_NONBLOCK);
    }
}

void CFNetwork::_closeNetwork(void)
{
    _isRunning = false;
    if (nullptr != _base) {
        event_base_free(_base);
        _base = nullptr;
    }
}

NS_CF_END
