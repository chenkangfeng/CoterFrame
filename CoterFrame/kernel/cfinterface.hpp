
#ifndef CF_INTERFACE_HPP
#define CF_INTERFACE_HPP

#include "include/cfmacro.h"
#include "cfcomponent.hpp"

#define CF_INTERFACE(Interface, ...) \
class Interface : public CoterFrame::CFInterface<Interface, ##__VA_ARGS__>

NS_CF_BEGIN

template <typename Interface, typename... Args>
class CFInterface
{
public:
    CFInterface(void) {}
    virtual ~CFInterface(void) {}

    static CF_SHARED_PTR<Interface> create(Args... args) {
        // return CFGlobal::create<Interface>(args...);
        // Unable to create an abstract class
        return CF_SHARED_PTR<Interface>();
    }

    static CF_SHARED_PTR<Interface> createComponent(Args... args) {
        return creator_(args...);
    }

    template <typename Implement>
    static void registerComponent(void) {
        if (CFGlobal::isInherit<Interface, Implement>()) {
            creator_ = Implement::create;
        }
    }
private:
    typedef CF_SHARED_PTR<Interface>(*Creator)(Args...);
    static Creator creator_;
};

template <typename Interface, typename... Args>
typename CFInterface<Interface, Args...>::Creator
CFInterface<Interface, Args...>::creator_ = CFInterface::create;

NS_CF_END

#endif // CF_INTERFACE_HPP
