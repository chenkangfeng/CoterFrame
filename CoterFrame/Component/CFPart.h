
#ifndef CF_PART_H
#define CF_PART_H

#include "CFPrecompiled.h"

NS_CF_BEGIN

template <typename T>
class CFPart
{
public:
    CFPart(void);
    virtual ~CFPart(void);

    T* createPart()
};

NS_CF_END

#endif // CF_PART_H
