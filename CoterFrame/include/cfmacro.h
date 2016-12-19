
#ifndef CF_MACRO_H
#define CF_MACRO_H

#include <stdint.h>
// typedef system not defined type
typedef bool bool_t;
typedef long long_t;
typedef unsigned long ulong_t;
typedef float float_t;
typedef double double_t;
typedef const char* strptr_t;

// typedef coterframe type
typedef bool_t      CFBool;
typedef int8_t      CFInt8;
typedef uint8_t     CFUInt8;
typedef int16_t     CFInt16;
typedef uint16_t    CFUInt16;
typedef int32_t     CFInt32;
typedef uint32_t    CFUInt32;
typedef int64_t     CFInt64;
typedef uint64_t    CFUInt64;
typedef long_t      CFLong;
typedef ulong_t     CFULong;
typedef float_t     CFFloat;
typedef double_t    CFDouble;
typedef strptr_t    CFStrPtr;

// define coterframe namespace macro
#define NS_CF_BEGIN namespace CoterFrame {
#define NS_CF_END   }
#define NS_CF_USING using namespace CoterFrame;

// define safe delete data
#define CF_SAFE_DELETE(Data) \
if (nullptr != Data) { \
    delete Data; \
    Data = nullptr; \
}

// define safe delete arrary
#define CF_SAFA_DELETE_ARRAY(Array) \
if (nullptr != Array) { \
    delete[] Array; \
    Array = nullptr; \
}

#include <assert.h>
#define CF_ASSERT(Condition) assert(Condition)

#define CF_NOTHROW (std::nothrow)

#endif // CF_MACRO_H
