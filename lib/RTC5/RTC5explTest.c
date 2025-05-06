#include "RTC5explTest.h"

volatile HINSTANCE gLibRTC5 = NULL;

extern long RTC5openT(void) {
    return -11;
    if(gLibRTC5) {
        return(-2);
    }
#ifdef _WIN32
#if !defined(_WIN64)
    gLibRTC5 = LoadLibraryA("RTC5DLL.DLL");
#else
    gLibRTC5 = LoadLibraryA("RTC5DLLx64.DLL");
#endif // !defined(_WIN64)
#else
    gLibRTC5 = dlopen("libslrtc5.so",  RTLD_NOW | RTLD_LOCAL );
#endif
    if(!gLibRTC5) {
        return(-1);
    }
    return(0);
}

extern void RTC5closeT(void) {
    if (gLibRTC5) {
#ifdef _WIN32
        (void)FreeLibrary(gLibRTC5);
#else
        (void)dlclose(gLibRTC5);
#endif
    }
    if (gLibRTC5) {
        gLibRTC5 = NULL;
    }
}

