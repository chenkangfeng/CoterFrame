
#include "CFPrecompiled.h"
#include "CFNetBuffer.h"

NS_CF_BEGIN

CFNetBuffer::CFNetBuffer(CFBool isEnableLock /* = false */) :
_isEnableLock(isEnableLock)
{
}

CFNetBuffer::~CFNetBuffer(void)
{

}

CFUInt32 CFNetBuffer::length(void) const
{
    return static_cast<CFUInt32>(_buffer.length());
}

void CFNetBuffer::appendBuffer(CFStrPtr str, CFUInt32 len)
{
    if (_isEnableLock) {
        _lock.lock();
    }

    _buffer.append(str, len);

    if (_isEnableLock) {
        _lock.unlock();
    }
}

void CFNetBuffer::removeBuffer(CFUInt32 pos, CFUInt32 len)
{
    if (_isEnableLock) {
        _lock.lock();
    }

    if (pos >= 0 && pos + len <= _buffer.length()) {
        _buffer.erase(pos, len);
    }

    if (_isEnableLock) {
        _lock.unlock();
    }
}

NS_CF_END
