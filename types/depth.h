#pragma once

enum Depth {
    ZERO = 0,
    ONE = 1,
    TWO = ONE * 2,
    THREE = ONE * 3,
    FOUR = ONE * 4,
    FIVE = ONE * 5,
    SIX = ONE * 6,
    SEVEN = ONE * 7,
    EIGHT = ONE * 8,
    NINE = ONE * 9,
    TEN = ONE * 10,

    MAX = ONE * 128
};

static Depth operator + (Depth d1, Depth d2)
{
    return Depth(int(d1) + int(d2));
}

static Depth operator - (Depth d1, Depth d2)
{
    return Depth(int(d1) - int(d2));
}

static Depth operator * (Depth d, int i)
{
    return Depth(int(d) * i);
}

static Depth operator * (Depth d, float f)
{
    return Depth(float(d) * f);
}

static Depth& operator ++ (Depth& d, int)
{
    return d = Depth(d + Depth::ONE);
}

static Depth& operator += (Depth& d1, Depth d2)
{
    return d1 = Depth(int(d1) + int(d2));
}

static Depth& operator -= (Depth& d1, Depth d2)
{
    return d1 = Depth(int(d1) - int(d2));
}
