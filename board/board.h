#pragma once

#include <string>

template <class T, class Move>
class GameBoard
{
public:
    using MoveType = typename Move;

    GameBoard() {}
    ~GameBoard() {}

    void doMove(MoveType& move)
    {
        static_cast<T*>(this)->doMoveImplementation(move);
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
