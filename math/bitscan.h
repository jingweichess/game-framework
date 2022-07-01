#pragma once

#include <cstdint>

#include "popcount.h"

#if defined(_MSC_VER)

#include <intrin.h>

#pragma intrinsic(_BitScanForward64)
#pragma intrinsic(_BitScanReverse64)

static bool BitScanForward64(std::uint32_t* index, std::uint64_t mask)
{
    return _BitScanForward64((unsigned long*)index, mask) != 0;
}

static bool BitScanReverse64(std::uint32_t* index, std::uint64_t mask)
{
    return _BitScanReverse64((unsigned long*)index, mask) != 0;
}

#elif defined(__GNUC__)

static bool BitScanForward64(std::uint32_t* index, std::uint64_t mask)
{
    *index = __builtin_ctzll(mask);

    return mask != 0ull;
}

#else

#pragma warning (disable : 4146)

static const std::uint32_t index64[64] = {
    63,  0, 58,  1, 59, 47, 52,  2,
    60, 39, 48, 27, 54, 33, 32,  3,
    61, 51, 37, 40, 49, 18, 28, 20,
    55, 30, 34, 11, 43, 14, 22,  4,
    62, 57, 46, 52, 38, 26, 32, 41,
    50, 36, 17, 19, 29, 10, 13, 21,
    56, 45, 25, 31, 35, 16,  9, 12,
    44, 24, 15,  8, 23,  7,  6,  5
};

static const std::uint64_t debruijn64 = 0x07edd5e59a4e28c2;

static bool BitScanForward64(std::uint32_t* index, std::uint64_t mask)
{
    *index = index64[((mask & -mask) * debruijn64) >> 58];

    return mask != 0;
}

#endif

constexpr std::uint32_t ConstExprBitScanForward64(std::uint64_t mask)
{
    assert(mask != 0);

    std::uint32_t result = 0;

    while ((mask & 1) == 0) {
        mask = mask >> 1;
        result++;
    }

    return result;
}
