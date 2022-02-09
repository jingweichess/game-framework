#pragma once

#include <cstdint>

#include "depth.h"

typedef std::int32_t Score;

constexpr Score BASICALLY_WINNING_SCORE = 3000;
constexpr Score DRAW_SCORE = 0;
constexpr Score NO_SCORE = 0;
constexpr Score UNIT_SCORE = 256;
constexpr Score WIN_SCORE = 32000;
constexpr Score ZERO_SCORE = 0;

static bool IsMateScore(Score score)
{
    return (score < (-WIN_SCORE + Depth::MAX)) ||
        (score > (WIN_SCORE - Depth::MAX));
}

static Depth DistanceToMate(Score score)
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
#include <emmintrin.h>
#include <immintrin.h>
#include <smmintrin.h>

static __m128i zerovector = _mm_setr_epi32(0, 0, 0, 0);
#endif

union Evaluation {
    struct {
        Score mg, eg, pad0, pad1;
    };

#if defined(USE_M128I)
    __m128i vector;
#endif

    Score operator()(std::int32_t phase) const
    {
        Score result = ((this->mg * phase) + (this->eg * (32 - phase))) / 32;

        return result;
    }

    Evaluation& operator += (const Evaluation &e2)
    {
#if defined(USE_M128I)
        this->vector = _mm_add_epi32(this->vector, e2.vector);
#else

        this->mg = this->mg + e2.mg;
        this->eg = this->eg + e2.eg;
#endif

        return *this;
    }

    friend Evaluation operator + (Evaluation e1, const Evaluation& e2)
    {
        return e1 += e2;
    }

    Evaluation& operator -= (const Evaluation &e2)
    {
#if defined(USE_M128I)
        this->vector = _mm_sub_epi32(this->vector, e2.vector);
#else
        this->mg = this->mg - e2.mg;
        this->eg = this->eg - e2.eg;
#endif

        return *this;
    }

    friend Evaluation operator - (Evaluation e1, const Evaluation& e2)
    {
        return e1 -= e2;
    }

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

    Evaluation operator * (const std::int32_t &i)
    {
        Evaluation result;

#if defined(USE_M128I)
        __m128i ivector = _mm_setr_epi32(i, i, i, i);

        result.vector = _mm_mullo_epi32(this->vector, ivector);
#else
        result = Evaluation{ this->mg * i, this->eg * i };
#endif

        return result;
    }

    Evaluation operator / (const std::int32_t &i)
    {
        Evaluation result;

#if defined(USE_M128I) and defined(_MSC_VER)
        __m128i ivector = _mm_setr_epi32(i, i, i, i);

        result.vector = _mm_div_epi32(this->vector, ivector);
#else
        result = Evaluation{ this->mg / i, this->eg / i };
#endif

        return result;
    }

    bool operator == (Evaluation e2)
    {
#if defined(USE_M128I) and defined(HAS_AVX512)
        __mmask8 mask = _mm_cmpeq_epi32_mask(e1.vector, e2.vector);

        //The mask that is returned has a bit set for each 32 bit element in the vector that is equal.  The
        //  4 higher bits are always 0.  If all 4 lower bits are set, this indicates the two vectors are equal.
        return mask & 0x07 != 0;
#else
        return (this->mg == e2.mg) && (this->eg == e2.eg);
#endif
    }
};

static Evaluation operator * (std::int32_t i, Evaluation e)
{
    return e * i;
}
