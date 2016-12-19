
#ifndef CF_STL_HPP
#define CF_STL_HPP

#include <list>
#include <vector>
#include <unordered_map>
#include <map>
#include "include/cfmacro.h"
#include "cfsharedptr.hpp"

NS_CF_BEGIN

// shared ptr list
template <typename T>
class CFList : public std::list<CF_SHARED_PTR<T> > {};

// shared ptr verctor
template <typename T>
class CFVector : public std::vector<CF_SHARED_PTR<T> > {};

// shared ptr map template
template <typename Key, typename Value, CFBool ordered = false>
class CFMap {};

// shared ptr unordered map
template <typename Key, typename Value>
class CFMap<Key, Value, false> : public std::unordered_map<Key, CF_SHARED_PTR<Value> > {};

// shared ptr map
template <typename Key, typename Value>
class CFMap<Key, Value, true> : public std::map<Key, CF_SHARED_PTR<Value> > {};

NS_CF_END

#endif // CF_STL_HPP
