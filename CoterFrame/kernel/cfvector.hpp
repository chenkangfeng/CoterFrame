
#ifndef CF_VECTOR_HPP
#define CF_VECTOR_HPP

#include <vector>
#include "include/cfmacro.h"
#include "cfsharedptr.hpp"

NS_CF_BEGIN

template <typename T>
class CFVector
{
public:
    CFVector(void) {}
    ~CFVector(void) {}

    void pushBack(CF_SHARED_PTR<T>&& var) {
        vec_share_ptr_.push_back(var);
    }
    CFUInt32 size(void) {
        return (CFUInt32)vec_share_ptr_.size();
    }
    CF_SHARED_PTR<T>& operator[](CFUInt32 index) {
        return vec_share_ptr_[index];
    }
private:
    typedef std::vector<CF_SHARED_PTR<T> > VectorSharePtr;
    VectorSharePtr vec_share_ptr_;
};

NS_CF_END

#endif // CF_VECTOR_HPP
