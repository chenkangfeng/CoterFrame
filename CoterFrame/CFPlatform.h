
#ifndef CF_PLATFORM_H
#define CF_PLATFORM_H

#define CF_PLATFORM_WIN     0x01
#define CF_PLATFORM_LINUX   0x02
#define CF_PLATFORM_MAC     0x04
#define CF_PLATFORM_IOS     0x08
#define CF_PLATFORM_ANDROID 0x10

#if defined(_WINDOWS) || defined(WIN) || defined(_WIN32) || defined(_WIN64)
    #define CF_TARGET_PLATFORM CF_PLATFORM_WIN
#elif defined(ANDROID)
    #define CF_TARGET_PLATFORM CF_PLATFORM_ANDROID
#elif defined(__APPLE__) || defined(__OSX__)
    #include <TargetConditionals.h>
    #if TARGET_OS_MAC
        #define CF_TARGET_PLATFORM CF_PLATFORM_MAC
    #elif TARGET_OS_IPHONE
        #define CF_TARGET_PLATFORM CF_PLATFORM_IOS
    #endif
#elif defined(LINUX)
    #define CF_TARGET_PLATFORM CF_PLATFORM_LINUX
#else
    #error "Cannot recognize the platform!"
#endif

#define CF_PLATFORM(Platform) (CF_TARGET_PLATFORM & (Platform))

#endif // CF_PLATFORM_H
