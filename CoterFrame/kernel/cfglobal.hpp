
#ifndef CF_GLOBAL_HPP
#define CF_GLOBAL_HPP

#include "include/cfmacro.h"
#include "cfsharedptr.hpp"

NS_CF_BEGIN

// global function class
class CFGlobal
{
public:
    CFGlobal(void) {}
    ~CFGlobal(void) {}

    // subclass is inherit baseclass
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

    // create shared ptr for baseclass
    template <typename Baseclass, typename... Args>
    static CF_SHARED_PTR<Baseclass> create(Args... args) {
        return CF_SHARED_PTR<Baseclass>(new CF_NOTHROW Baseclass(args...));
    }
    // create share ptr for subclass when it inherit baseclass
    template <typename Baseclass, typename Subclass, typename... Args>
    static CF_SHARED_PTR<Subclass> create(Args... args) {
        CF_SHARED_PTR<Subclass> instance;
        if (isInherit<Baseclass, Subclass>()) {
            instance = std::move(create<Subclass>(args...));
        }
        return instance;
    }
};

NS_CF_END

#endif // CF_GLOBAL_HPP
