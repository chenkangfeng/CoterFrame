
#include "CFPrecompiled.h"
#include "CFNetLock.h"

NS_CF_BEGIN

CFNetLock::CFNetLock(CFBool isEnable) :
_isEnable(isEnable)
{
    lock();
}

CFNetLock::~CFNetLock(void)
{
    unlock();
}

void CFNetLock::lock(void)
{
    if (_isEnable) {
        while (_flag.test_and_set()) {}
    }
}

void CFNetLock::unlock(void)
{
    if (_isEnable) {
        _flag.clear();
    }
}

CFNetLock::CFNetLock(const CFNetLock&)
{
}

CFNetLock& CFNetLock::operator=(const CFNetLock&)
{
    return *this;
}

NS_CF_END
