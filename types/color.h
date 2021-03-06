#pragma once

enum Color {
    WHITE, BLACK, COLOR_COUNT,
    COLOR_START = WHITE,
};

static Color& operator ++ (Color& c, int)
{
    return c = Color(int(c) + 1);
}

static Color operator ~ (Color& c)
{
    if (c == Color::WHITE) {
        return Color::BLACK;
    }
    else {
        return Color::WHITE;
    }
}
