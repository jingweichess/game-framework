#pragma once

#include <cstdint>

#include "depth.h"

using Score = std::int32_t;

constexpr Score DRAW_SCORE = 0;
constexpr Score NO_SCORE = 0;
constexpr Score UNIT_SCORE = 256;
constexpr Score WIN_SCORE = 32000;
constexpr Score ZERO_SCORE = 0;

constexpr Score BASICALLY_WINNING_SCORE = UNIT_SCORE * 15;

constexpr bool IsMateScore(Score score)
{
    return (score < (-WIN_SCORE + Depth::MAX)) ||
        (score > (WIN_SCORE - Depth::MAX));
}

constexpr Depth DistanceToMate(Score score)
{
    if (score > (WIN_SCORE - Depth::MAX)) {
        return Depth::ONE * (WIN_SCORE - score);
    }
    else if (score < (-WIN_SCORE + Depth::MAX)) {
        return Depth::ONE * (score + WIN_SCORE);
    }
    else {
        return Depth::ZERO;
    }
}

#if defined(USE_M128I)
#include <immintrin.h>

static __m128i zerovector = _mm_setr_epi32(0, 0, 0, 0);
#endif

union Evaluation {
    struct {
        Score mg, eg, pad0, pad1;
    };

#if defined(USE_M128I)
    __m128i vector;
#endif

    constexpr Evaluation() : mg(0), eg(0), pad0(0), pad1(0) {}
    constexpr Evaluation(Score mg, Score eg) : mg(mg), eg(eg), pad0(0), pad1(0) {}
    constexpr ~Evaluation() {}

    constexpr Score operator()(std::int32_t phase) const
    {
        Score result = ((this->mg * phase) + (this->eg * (32 - phase))) / 32;

        return result;
    }

#ifndef USE_M128I
    constexpr
#endif
    Evaluation& operator += (const Evaluation e2)
    {
#if defined(USE_M128I)
        this->vector = _mm_add_epi32(this->vector, e2.vector);
#else

        this->mg = this->mg + e2.mg;
        this->eg = this->eg + e2.eg;
#endif

        return *this;
    }

#ifndef USE_M128I
    constexpr
#endif
    friend Evaluation operator + (const Evaluation e1, const Evaluation e2)
    {
        Evaluation result;

#if defined(USE_M128I)
        result.vector = _mm_add_epi32(e1.vector, e2.vector);
#else
        result.mg = e1.mg + e2.mg;
        result.eg = e1.eg + e2.eg;
#endif

        return result;
    }

#ifndef USE_M128I
    constexpr
#endif
    Evaluation& operator -= (const Evaluation e2)
    {
#if defined(USE_M128I)
        this->vector = _mm_sub_epi32(this->vector, e2.vector);
#else
        this->mg = this->mg - e2.mg;
        this->eg = this->eg - e2.eg;
#endif

        return *this;
    }

#ifndef USE_M128I
    constexpr
#endif
    friend Evaluation operator - (const Evaluation e1, const Evaluation e2)
    {
        Evaluation result;

#if defined(USE_M128I)
        result.vector = _mm_sub_epi32(e1.vector, e2.vector);
#else
        result.mg = e1.mg - e2.mg;
        result.eg = e1.eg - e2.eg;
#endif

        return result;
    }

#ifndef USE_M128I
    constexpr
#endif
    Evaluation operator - ()
    {
#if defined(USE_M128I)
        Evaluation result;
        result.vector = _mm_sub_epi32(zerovector, this->vector);

        return result;
#else
        return Evaluation{ -this->mg, -this->eg };
#endif
    }

#ifndef USE_M128I
    constexpr
#endif
    Evaluation operator * (const std::int32_t i)
    {
        Evaluation result;

#if defined(USE_M128I)
        __m128i ivector = _mm_setr_epi32(i, i, i, i);

        result.vector = _mm_mullo_epi32(this->vector, ivector);
#else
        result.mg = this->mg * i;
        result.eg = this->eg * i;
#endif

        return result;
    }

#ifndef USE_M128I
    constexpr
#endif
    Evaluation operator / (const std::int32_t i)
    {
        Evaluation result;

//#if defined(USE_M128I) and defined(_MSC_VER)
//        __m128i ivector = _mm_setr_epi32(i, i, i, i);

//        result.vector = _mm_div_epi32(this->vector, ivector);
//#else
        result.mg = this->mg / i;
        result.eg = this->eg / i;
//#endif

        return result;
    }

#ifndef USE_M128I
    constexpr
#endif
    bool operator == (Evaluation e2)
    {
#if defined(USE_M128I)
        __m128i result = _mm_cmpeq_epi32(this->vector, e2.vector);
        std::uint64_t spread[2];

        _mm_store_si128((__m128i*)spread, result);

        return spread != 0x0;
#else
        return (this->mg == e2.mg) && (this->eg == e2.eg);
#endif
    }
};

#ifndef USE_M128I
constexpr
#else
static
#endif
Evaluation operator * (std::int32_t i, const Evaluation e)
{
    Evaluation result;

#if defined(USE_M128I)
    __m128i ivector = _mm_setr_epi32(i, i, i, i);

    result.vector = _mm_mullo_epi32(e.vector, ivector);
#else
    result.mg = e.mg * i;
    result.eg = e.eg * i;
#endif

    return result;
}
