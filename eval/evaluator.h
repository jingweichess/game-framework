#pragma once

#include "../board/board.h"

#include "../types/score.h"

template <class T, class Board>
class Evaluator
{
protected:

public:
    using BoardType = Board;

    Evaluator() {}
    ~Evaluator() {}

    Score evaluate(BoardType& board, Score alpha, Score beta)
    {
        return static_cast<T*>(this)->evaluateImplementation(board, alpha, beta);
    }

    Score lazyEvaluate(BoardType& board)
    {
        return static_cast<T*>(this)->lazyEvaluateImplementation(board);
    }
};
