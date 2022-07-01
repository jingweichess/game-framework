#pragma once

enum Color {
    WHITE, BLACK, COLOR_COUNT,
    COLOR_START = WHITE,
    CURRENT_COLOR = WHITE,
    OTHER_COLOR = BLACK,
    STRONG_COLOR = WHITE,
    WEAK_COLOR = BLACK
};

constexpr Color& operator ++ (Color& c, int)
{
    return c = Color(int(c) + 1);
}

constexpr Color operator ~ (Color& c)
{
    if (c == Color::WHITE) {
        return Color::BLACK;
    }
    else {
        return Color::WHITE;
    }
}
