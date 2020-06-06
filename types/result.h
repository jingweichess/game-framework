#pragma once

enum TwoPlayerGameResult {
    LOSS, DRAW, WIN, NO_GAMERESULT
};

static TwoPlayerGameResult operator - (TwoPlayerGameResult gr)
{
    switch (gr) {
    case TwoPlayerGameResult::LOSS:
        return TwoPlayerGameResult::WIN;
    case TwoPlayerGameResult::WIN:
        return TwoPlayerGameResult::LOSS;
    }

    return gr;
}

struct TwoPlayerGameSetResult {
    TwoPlayerGameResult white, black;
    NodeCount bookDepth;
};

typedef std::uint32_t GameResultCount;

constexpr GameResultCount ZeroGameResultCount = 0;
