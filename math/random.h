#pragma once

#include <cmath>
#include <cstdint>

static std::uint64_t pseudoState = 0x3d382260596c0545;

static void PseudoRandomSeed(std::uint64_t seed)
{
    pseudoState = seed;
}

static std::uint64_t PseudoRandomValue()
{
    return pseudoState = 6364136223846793005 * pseudoState + 1442695040888963407;
}

static std::int64_t PseudoRandomValue(std::int64_t min, std::int64_t max)
{
    std::int64_t range = std::abs(max - min);

    if (range == 0) {
        PseudoRandomValue();
        return min;
    }

    return min + PseudoRandomValue() % range;
}

#if defined(_MSC_VER)

#include <intrin.h>

#pragma intrinsic(_rdrand64_step)
#pragma intrinsic(_rdseed64_step)
#pragma intrinsic(__rdtsc)

static std::uint64_t CpuClock()
{
    return __rdtsc();
}

static void RandomSeed(std::uint64_t seed)
{
    _rdrand64_step(&seed);
}

static std::uint64_t RandomValue()
{
    std::uint64_t result;

    _rdrand64_step(&result);

    return result;
}

static std::int64_t RandomValue(std::int64_t min, std::int64_t max)
{
    std::int64_t range = std::abs(max - min);

    if (range == 0) {
        RandomValue();
        return min;
    }

    return min + RandomValue() % range;
}

#else

static std::uint64_t CpuClock()
{
    return 0x3d382260596c0545;
}

static void RandomSeed(std::uint64_t seed)
{
    PseudoRandomSeed(seed);
}

static std::uint64_t RandomValue()
{
    return PseudoRandomValue();
}

static std::int64_t RandomValue(std::int64_t min, std::int64_t max)
{
    return PseudoRandomValue(min, max);
}

#endif
