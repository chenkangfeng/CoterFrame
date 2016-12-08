
#include "CFPrecompiled.h"
#include "CFNetMessage.h"

NS_CF_BEGIN

static const CFUInt16 CF_PACK_MASK = 0x1234;
static const CFUInt16 CF_PACK_MASK_LEN = sizeof(CFInt16);
static const CFUInt16 CF_PACK_SIZE_LEN = sizeof(CFInt16);
static const CFUInt16 CF_PACK_HEAD_LEN = CF_PACK_MASK_LEN + CF_PACK_SIZE_LEN;

CFNetMessage::CFNetMessage(void)
{
}

CFNetMessage::CFNetMessage(const std::string& message, const CFNetHead& netHead /* = CFNetHead::UnHead */)
{
    if (netHead == CFNetHead::UseHead) {
        //CFUInt16 len = message.length() + CF_PACK_HEAD_LEN;
        //_message.append(CF_PACK_MASK, CF_PACK_MASK_LEN);
        //_message.append(len, CF_PACK_SIZE_LEN);
    }
    _message.append(message.data(), message.length());
}

CFNetMessage::~CFNetMessage(void)
{

}

std::string& CFNetMessage::getMessage(void)
{
    return _message;
}

NS_CF_END
