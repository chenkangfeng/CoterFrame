
#ifndef CF_GLOBAL_HPP
#define CF_GLOBAL_HPP

#include "include/cfmacro.h"
#include "cfsharedptr.hpp"

NS_CF_BEGIN

class CFGlobal
{
public:
    CFGlobal(void) {}
    ~CFGlobal(void) {}

    template <typename Baseclass, typename Subclass>
    static CFBool isInherit(void) {
        return isInherit<Baseclass>((Subclass*)nullptr);
    }
    template <typename Baseclass>
    static CFBool isInherit(Baseclass*) {
        return true;
    }
    template <typename Baseclass>
    static CFBool isInherit(void*) {
        return false;
    }

    template <typename Baseclass, typename... Args>
    static CF_SHARED_PTR<Baseclass> create(Args... args) {
        return CF_SHARED_PTR<Baseclass>(new CF_NOTHROW Baseclass(args...));
    }
    template <typename Baseclass, typename Subclass, typename... Args>
    static CF_SHARED_PTR<Subclass> create(Args... args) {
        CF_SHARED_PTR<Subclass> instance;
        if (isInherit<Baseclass, Subclass>()) {
            instance = std::move(CF_SHARED_PTR<Subclass>(new CF_NOTHROW Subclass(args...)));
        }
        return instance;
    }
};

NS_CF_END

#endif // CF_GLOBAL_HPP
