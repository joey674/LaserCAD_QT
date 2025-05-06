#ifndef RTC5EXPLTEST_H
#define RTC5EXPLTEST_H
#if defined(__cplusplus)
extern "C" {
#endif //defined(__cplusplus)

#ifdef _WIN32
#include <windows.h>
#if !defined(ULONG_PTR) //  usually defined in <BaseTsd.h>
#if !defined(_WIN64)
#define ULONG_PTR UINT
#else
#define ULONG_PTR UINT64
#endif // !defined(_WIN64)
#endif // !defined(ULONG_PTR)
#else
#include <stdint.h>
typedef int32_t LONG; //  LONG  is assumed to be 4 Bytes
typedef uint32_t UINT; //  UINT  is assumed to be 4 Bytes
typedef uintptr_t ULONG_PTR;
#define __stdcall
#endif

long RTC5openT(void);
void RTC5closeT(void);

#if defined(__cplusplus)
}
#endif
#endif // RTC5EXPLTEST_H
