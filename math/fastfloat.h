#pragma once

#include <cstdint>

#include "bitscan.h"

struct FixedPoint16
{
    union {
        struct {
            std::int16_t decimal;
            std::int16_t integer;
        } parts;

        std::uint32_t all;
    };

    FixedPoint16()
    {
        FixedPoint16(0, 0);
    }

    FixedPoint16(std::int16_t integer, std::int16_t decimal) {
        this->parts.integer = integer;
        this->parts.decimal = decimal;
    }

    std::int32_t log()
    {

    }
};

static FixedPoint16 operator + (FixedPoint16 e1, FixedPoint16 e2)
{
    FixedPoint16 result;
    result.all = e1.all + e2.all;

    return result;
}

static FixedPoint16 operator - (FixedPoint16 e1, FixedPoint16 e2)
{
    FixedPoint16 result;
    result.all = e1.all - e2.all;

    return result;
}

static FixedPoint16 operator * (FixedPoint16 e1, FixedPoint16 e2)
{
    std::int64_t all = (std::int64_t)e1.all * (std::int64_t)e2.all;

    FixedPoint16 result;
    result.all = all >> 16;

    return result;
}

static FixedPoint16 operator * (FixedPoint16 e1, std::int32_t i)
{
    FixedPoint16 result;
    result.all = e1.all * i;

    return result;
}

static FixedPoint16 operator / (FixedPoint16 e1, FixedPoint16 e2)
{
    std::int64_t all = ((std::int64_t)e1.all << 32) / (std::int64_t)e2.all;

    FixedPoint16 result;
    result.all = all >> 16;

    return result;
}

static FixedPoint16 operator / (FixedPoint16 e1, std::int32_t i)
{
    FixedPoint16 result;
    result.all = e1.all / i;

    return result;
}
