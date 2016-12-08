
#ifndef CF_PLATFORM_H
#define CF_PLATFORM_H

#define CF_WIN     (1 << 1)
#define CF_LINUX   (1 << 2)
#define CF_MAC     (1 << 3)
#define CF_IOS     (1 << 4)
#define CF_ANDROID (1 << 5)

#if defined(_WINDOWS) || defined(WIN) || defined(_WIN32) || defined(_WIN64)
#define _CF_PLATFORM CF_WIN
#elif defined(ANDROID)
#define _CF_PLATFORM CF_ANDROID
#elif defined(__APPLE__) || defined(__OSX__)
#include <TargetConditionals.h>
#if TARGET_OS_MAC
#define _CF_PLATFORM CF_MAC
#elif TARGET_OS_IPHONE
#define _CF_PLATFORM CF_IOS
#endif
#elif defined(LINUX)
#define _CF_PLATFORM CF_LINUX
#else
#error "Cannot recognize the platform!"
#endif

#define CF_PLATFORM(Platform) (_CF_PLATFORM & (Platform))

#endif // CF_PLATFORM_H
