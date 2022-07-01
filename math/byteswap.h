#pragma once

#include <cstdint>

#if defined(_MSC_VER)

#include <intrin.h>

#pragma intrinsic(_byteswap_uint64)

std::uint64_t SwapBytes(std::uint64_t b)
{
    return _byteswap_uint64(b);
}

#elif defined(__GNUC__)

std::uint64_t SwapBytes(std::uint64_t b)
{
    return __builtin_bswap64(b);
}

#else

std::uint64_t SwapBytes(std::uint64_t b)
{
    std::uint64_t save = b;
    unsigned char* arr = (unsigned char*)&save;

    unsigned char temp;

    
    temp = arr[7]; arr[7] = arr[0]; arr[0] = temp;
    temp = arr[6]; arr[6] = arr[1]; arr[1] = temp;
    temp = arr[5]; arr[5] = arr[2]; arr[2] = temp;
    temp = arr[4]; arr[4] = arr[3]; arr[3] = temp;

    return save;
}

#endif

