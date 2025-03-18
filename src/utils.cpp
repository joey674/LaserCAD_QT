#include "utils.h"
#include "logger.h"
// #include <objbase.h>

std::string GenerateUUID()
{
    std::string strUUID = "123";
    // GUID guid;
    // if (!CoCreateGuid(&guid)) {
    //     char buffer[64] = { 0 };
    //     _snprintf_s(buffer, sizeof(buffer),
    //                 "%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X",
    //                 guid.Data1, guid.Data2, guid.Data3,
    //                 guid.Data4[0], guid.Data4[1], guid.Data4[2],
    //                 guid.Data4[3], guid.Data4[4], guid.Data4[5],
    //                 guid.Data4[6], guid.Data4[7]);
    //     strUUID = buffer;
    // }
    return strUUID;
}

void test()
{
    DEBUG_MSG("aa");
}
