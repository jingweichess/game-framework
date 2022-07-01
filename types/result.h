#pragma once

#include <cassert>

#include "nodecount.h"

enum TwoPlayerGameResult {
    LOSS, DRAW, WIN, NO_GAMERESULT
};

constexpr TwoPlayerGameResult operator - (TwoPlayerGameResult gr)
{
    switch (gr) {
    case TwoPlayerGameResult::LOSS:
        return TwoPlayerGameResult::WIN;
    case TwoPlayerGameResult::WIN:
        return TwoPlayerGameResult::LOSS;
    case TwoPlayerGameResult::DRAW:
        return gr;
    case TwoPlayerGameResult::NO_GAMERESULT:
        return gr;
    default:
        assert(0);
    }
}

struct TwoPlayerGameSetResult {
    TwoPlayerGameResult white, black;
    NodeCount bookDepth;
};

using GameResultCount = std::uint32_t;

constexpr GameResultCount ZeroGameResultCount = GameResultCount(0);
