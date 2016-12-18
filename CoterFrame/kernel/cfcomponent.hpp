
#ifndef CF_COMPONENT_HPP
#define CF_COMPONENT_HPP

#include "include/cfmacro.h"
#include "cfglobal.hpp"

#define CF_COMPONENT(Interface, Implement, ...) \
class Implement : public CoterFrame::CFComponent<Interface, Implement, ##__VA_ARGS__>, \
    public CFSharedPtr<Implement>

NS_CF_BEGIN

template <typename Interface, typename Implement, typename... Args>
class CFComponent : public Interface
{
public:
    CFComponent(Args... args) : Interface(args...) {}
    virtual ~CFComponent(void) {}

    static CF_SHARED_PTR<Interface> create(Args... args) {
        return CFGlobal::create<Interface, Implement>(args...);
    }
};

NS_CF_END

#endif // CF_COMPONENT_HPP
