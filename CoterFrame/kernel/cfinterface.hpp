
#ifndef CF_INTERFACE_HPP
#define CF_INTERFACE_HPP

#include "include/cfmacro.h"
#include "cfcomponent.hpp"

// define interface macro
#define CF_INTERFACE(Interface, ...) \
class Interface : public CoterFrame::CFInterface<Interface, ##__VA_ARGS__>, \
    public CFSharedPtr<Interface>

NS_CF_BEGIN

// interface class
template <typename Interface, typename... Args>
class CFInterface
{
public:
    CFInterface(void) {}
    virtual ~CFInterface(void) {}

    // interface create function
    // unable to create an abstract class
    // return empty interface share ptr
    static CF_SHARED_PTR<Interface> create(Args... args) {
        return CF_SHARED_PTR<Interface>();
    }

    // component create function
    // return interface share ptr
    // if component has been setup it will return a component instance
    static CF_SHARED_PTR<Interface> createComponent(Args... args) {
        return creator_(args...);
    }

    // component setup function
    // replace interface create function to component create function
    template <typename Implement>
    static void setupComponent(void) {
        if (CFGlobal::isInherit<Interface, Implement>()) {
            creator_ = Implement::create;
        }
    }
private:
    typedef CF_SHARED_PTR<Interface>(*Creator)(Args...);
    static Creator creator_;
};

// interface creat function init
template <typename Interface, typename... Args>
typename CFInterface<Interface, Args...>::Creator
CFInterface<Interface, Args...>::creator_ = CFInterface::create;

NS_CF_END

#endif // CF_INTERFACE_HPP
