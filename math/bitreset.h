#pragma once

#include <cstdint>

#if defined(_MSC_VER)

#include <immintrin.h>
#include <ammintrin.h>

#pragma intrinsic(_blsr_u64)

static std::uint64_t ResetLowestSetBit(std::uint64_t b)
{
    return _blsr_u64(b);
}

#else

constexpr std::uint64_t ResetLowestSetBit(std::uint64_t b)
{
    return b & (b - 1);
}

#endif

constexpr std::uint64_t ConstExprResetLowestSetBit(std::uint64_t b)
{
    return b & (b - 1);
}
