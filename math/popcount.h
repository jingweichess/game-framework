#pragma once

#include <cstdint>

#include "bitreset.h"

#if defined(_MSC_VER)

#include <intrin.h>

#pragma intrinsic(__popcnt64)

static std::uint32_t popCount(std::uint64_t b)
{
    return std::uint32_t(__popcnt64(b));
}

static bool popCountIsOne(std::uint64_t b)
{
    return popCount(b) == 1;
}

static std::uint32_t popCountSparse(std::uint64_t b)
{
    return popCount(b);
}

#elif defined(__GNUC__)

static std::uint32_t popCount(std::uint64_t b)
{
    return std::uint32_t(__builtin_popcountll(b));
}

static bool popCountIsOne(std::uint64_t b)
{
    return popCount(b) == 1;
}

static std::uint32_t popCountSparse(std::uint64_t b)
{
    return popCount(b);
}

#else

#include "bitreset.h"

static std::uint32_t popCountSparse(std::uint64_t b)
{
    std::uint32_t i = 0;

    while (b != 0ull) {
        i++;
        b = ResetLowestSetBit(b);
    }

    return i;
}

static bool popCountIsOne(std::uint64_t b)
{
    return (b != 0ull) && (ResetLowestSetBit(b) == 0ull);
}

static std::uint32_t popCount(std::uint64_t b)
{
    return popCountSparse(b);
}

#endif

constexpr std::uint32_t ConstExprPopCount(std::uint64_t b)
{
    std::uint32_t i = 0;

    while (b != 0ull) {
        i++;
        b = ConstExprResetLowestSetBit(b);
    }

    return i;
}

constexpr bool ConstExprPopCountIsOne(std::uint64_t b)
{
    return ConstExprPopCount(b) == 1;
}
