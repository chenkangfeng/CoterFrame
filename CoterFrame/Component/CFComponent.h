
#ifndef CF_COMPONENT_H
#define CF_COMPONENT_H

#include "CFPrecompiled.h"
#include "CFPart.h"

NS_CF_BEGIN

template <typename T>
class CFComponent : public CFPart
{
public:
    CFComponent(void);
    virtual ~CFComponent(void);
};

NS_CF_END

#endif // CF_COMPONENT_H
