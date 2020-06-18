#pragma once

#include <cstdint>

#include "depth.h"

typedef std::int32_t Score;

static constexpr Score BASICALLY_WINNING_SCORE = 5000;
static constexpr Score DRAW_SCORE = 0;
static constexpr Score NO_SCORE = 0;
static constexpr Score UNIT_SCORE = 128;
static constexpr Score WIN_SCORE = 32000;
static constexpr Score ZERO_SCORE = 0;

static bool IsMateScore(Score value)
{
    return (value < (-WIN_SCORE + Depth::MAX)) ||
        (value > (WIN_SCORE - Depth::MAX));
}

#if defined(USE_M128I)
#include <emmintrin.h>
#include <immintrin.h>
#include <smmintrin.h>

static __m128i zerovector = _mm_setr_epi32(0, 0, 0, 0);
#endif

union Evaluation {
    struct {
        Score mg, eg;
    };

#if defined(USE_M128I)
    __m128i vector;
#endif
};

static Evaluation operator + (Evaluation e1, Evaluation e2)
{
#if defined(USE_M128I)
    Evaluation result;
    result.vector = _mm_add_epi32(e1.vector, e2.vector);

    return result;
#else
    return Evaluation{ e1.mg + e2.mg, e1.eg + e2.eg };
#endif
}

static Evaluation operator += (Evaluation& e1, Evaluation e2)
{
    return e1 = e1 + e2;
}

static Evaluation operator - (Evaluation e1, Evaluation e2)
{
#if defined(USE_M128I)
    Evaluation result;
    result.vector = _mm_sub_epi32(e1.vector, e2.vector);

    return result;
#else
    return Evaluation{ e1.mg - e2.mg, e1.eg - e2.eg };
#endif
}

static Evaluation& operator -= (Evaluation& e1, Evaluation e2)
{
    return e1 = e1 - e2;
}

static Evaluation operator - (Evaluation e)
{
#if defined(USE_M128I)
    e.vector = _mm_sub_epi32(zerovector, e.vector);

    return e;
#else
    return Evaluation{ -e.mg, -e.eg };
#endif
}

static Evaluation operator * (Evaluation e, std::int32_t i)
{
#if defined(USE_M128I)
    __m128i ivector = _mm_setr_epi32(i, i, i, i);

    Evaluation result;
    result.vector = _mm_mullo_epi32(e.vector, ivector);

    return result;
#else
    return Evaluation{ e.mg * i, e.eg * i };
#endif
}

static Evaluation operator * (std::int32_t i, Evaluation e)
{
    return e * i;
}

static Evaluation operator / (Evaluation e, std::int32_t i)
{
//#if defined(USE_M128I)
//    __m128i ivector = _mm_setr_epi32(i, i, i, i);

//    Evaluation result;
//    result.vector = _mm_div_epi32(e.vector, ivector);

//    return result;
//#else
    return Evaluation{ e.mg / i, e.eg / i };
//#endif
}

static bool operator == (Evaluation e1, Evaluation e2)
{
#if defined(USE_M128I) and defined(HAS_AVX512)
    __mmask8 mask = _mm_cmpeq_epi32_mask(e1.vector, e2.vector);

    //The mask that is returned has a bit set for each 32 bit element in the vector that is equal.  The
    //  4 higher bits are always 0.  If all 4 lower bits are set, this indicates the two vectors are equal.
    return mask & 0x07 != 0;
#else
    return (e1.mg == e2.mg) && (e1.eg == e2.eg);
#endif
}

static bool operator != (Evaluation e1, Evaluation e2)
{
#if defined(USE_M128I) and defined(HAS_AVX512)
    __mmask8 mask = _mm_cmpeq_epi32_mask(e1.vector, e2.vector);

    //The mask that is returned has a bit set for each 32 bit element in the vector that is equal.  The
    //  4 higher bits are always 0.  If all 4 lower bits are set, this indicates the two vectors are equal.
    return mask & 0x07 == 0;
#else
    return (e1.mg != e2.mg) || (e1.eg != e2.eg);
#endif
}
