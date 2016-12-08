
#ifndef CF_NET_LOCK
#define CF_NET_LOCK

#include "CFPrecompiled.h"
#include <atomic>

NS_CF_BEGIN

class CFNetLock
{
public:
    explicit CFNetLock(CFBool isEnable);
    ~CFNetLock(void);

    void lock(void);
    void unlock(void);
private:
    CFNetLock(const CFNetLock&);
    CFNetLock& operator=(const CFNetLock& other);

    CFBool _isEnable;
    mutable std::atomic_flag _flag;
};

NS_CF_END

#endif // CF_NET_LOCK
