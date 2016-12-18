
#ifndef CF_PLATFORM_H
#define CF_PLATFORM_H

#define CF_PLATFORM_WIN     (1 << 0)
#define CF_PLATFORM_LINUX   (1 << 1)
#define CF_PLATFORM_MAC     (1 << 2)
#define CF_PLATFORM_IOS     (1 << 3)
#define CF_PLATFORM_ANDROID (1 << 4)

#if defined(_WINDOWS) || defined(WIN) || defined(_WIN32) || defined(_WIN64)
#define CF_PLATFORM_VAR CF_PLATFORM_WIN
#elif defined(ANDROID)
#define CF_PLATFORM_VAR CF_PLATFORM_ANDROID
#elif defined(__APPLE__) || defined(__OSX__)
#include <TargetConditionals.h>
#if TARGET_OS_MAC
#define CF_PLATFORM_VAR CF_PLATFORM_MAC
#elif TARGET_OS_IPHONE
#define CF_PLATFORM_VAR CF_PLATFORM_IOS
#endif
#elif defined(LINUX)
#define CF_PLATFORM_VAR CF_PLATFORM_LINUX
#else
#error "Cannot recognize the platform!"
#endif

#define CF_PLATFORM(Platform) (CF_PLATFORM_VAR & (Platform))

#endif // CF_PLATFORM_H
