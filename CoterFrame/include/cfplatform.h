
#ifndef CF_PLATFORM_H
#define CF_PLATFORM_H

typedef enum {
    kPlatformWin        = (1 << 0),
    kPlatformLinux      = (1 << 1),
    kPlatformMac        = (1 << 2),
    kPlatformIOS        = (1 << 3),
    kPlatformAndroid    = (1 << 4)
} CFPlatform;

#if defined(_WINDOWS) || defined(WIN) || defined(_WIN32) || defined(_WIN64)
const CFPlatform kPlatform = kPlatformWin;
#elif defined(ANDROID)
const CFPlatform kPlatform = kPlatformAndroid;
#elif defined(__APPLE__) || defined(__OSX__)
#include <TargetConditionals.h>
#if TARGET_OS_MAC
const CFPlatform kPlatform = kPlatformMac;
#elif TARGET_OS_IPHONE
const CFPlatform kPlatform = kPlatformIOS;
#endif
#elif defined(LINUX)
const CFPlatform kPlatform = kPlatformLinux;
#else
#error "Cannot recognize the platform!"
#endif

#define CF_PLATFORM(Platform) (kPlatform & (Platform))

#endif // CF_PLATFORM_H
