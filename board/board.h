#pragma once

#include <string>

template <class T, class Move>
class GameBoard
{
public:
    using MoveType = Move;

    GameBoard() {}
    ~GameBoard() {}

    template<bool performPreCalculations = true>
    void doMove(MoveType& move)
    {
        static_cast<T*>(this)->doMoveImplementation<performPreCalculations>(move);
    }

    void resetSpecificPosition(std::string& fen)
    {
        static_cast<T*>(this)->resetSpecificPositionImplementation(fen);
    }

    void resetStartingPosition()
    {
        static_cast<T*>(this)->resetStartingPositionImplementation();
    }
};
