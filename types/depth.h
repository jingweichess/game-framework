#pragma once

enum Depth {
    ZERO = 0,
    ONE = 1,

    MAX = 128
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
