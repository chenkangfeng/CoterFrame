
#include "CFPrecompiled.h"
#include "CFNetLock.h"

NS_CF_BEGIN

CFNetLock::CFNetLock(void)
{
    unlock();
}

CFNetLock::~CFNetLock(void)
{
    unlock();
}

void CFNetLock::lock(void)
{
    while (_flag.test_and_set());
}

void CFNetLock::unlock(void)
{
    _flag.clear();
}

CFNetLock::CFNetLock(const CFNetLock&)
{
}

CFNetLock& CFNetLock::operator=(const CFNetLock&)
{
    return *this;
}

NS_CF_END
