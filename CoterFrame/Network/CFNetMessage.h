
#ifndef CF_NET_MESSAGE_H
#define CF_NET_MESSAGE_H

#include "CFPrecompiled.h"

NS_CF_BEGIN

enum class CFNetHead { UnHead, UseHead };

class CFNetMessage
{
public:
    CFNetMessage(void);
    CFNetMessage(const std::string& message, const CFNetHead& netHead = CFNetHead::UnHead);
    ~CFNetMessage(void);

    std::string& getMessage(void);
private:
    std::string _message;
};

NS_CF_END

#endif // CF_NET_MESSAGE_H
