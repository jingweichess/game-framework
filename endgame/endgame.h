#pragma once

#include <map>

#include "../types/color.h"
#include "../types/hash.h"
#include "../types/score.h"

template <class Board>
class Endgame
{
public:
    using BoardType = Board;
    using EndgameFunctionType = bool (*) (BoardType& board, Score& score);
    using EndgameFunctionMapType = std::map<Hash, EndgameFunctionType>;

protected:
    EndgameFunctionMapType endgameFunctionMap;

    static bool nullEndgameFunction(BoardType& board, Score& score)
    {
        return false;
    }
public:
    Endgame() {}
    ~Endgame() {}

    void add(BoardType& board, EndgameFunctionType& endgameFunction)
    {
        Hash materialHash = board.materialHashValue;
        Endgame::endgameFunctionMap[materialHash] = endgameFunction;
    }
     
    bool probe(BoardType& board, Score& score)
    {
        Hash materialHash = board.materialHashValue;

        if (Endgame::endgameFunctionMap.count(materialHash) == 0) {
            Endgame::endgameFunctionMap[materialHash] = Endgame::nullEndgameFunction;

            return false;
        }

        EndgameFunctionType endgameFunction = Endgame::endgameFunctionMap.at(materialHash);
        return endgameFunction(board, score);
    }
};
