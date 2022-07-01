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
    using EndgameFunctionType = bool (*) (const BoardType& board, Score& score);
    using EndgameFunctionMapType = std::map<Hash, EndgameFunctionType>;

protected:
    EndgameFunctionMapType endgameFunctionMap;

    static constexpr bool nullEndgameFunction(const BoardType& board, Score& score)
    {
        return false;
    }
public:
    constexpr Endgame() = default;
    constexpr ~Endgame() = default;

    constexpr bool add(const BoardType& board, const EndgameFunctionType& endgameFunction)
    {
        Hash materialHash = board.materialHashValue;
        Endgame::endgameFunctionMap[materialHash] = endgameFunction;

        return true;
    }
     
    constexpr bool probe(const BoardType& board, Score& score)
    {
        Hash materialHash = board.materialHashValue;

        if (Endgame::endgameFunctionMap.count(materialHash) == 0) {
            Endgame::endgameFunctionMap[materialHash] = Endgame::nullEndgameFunction;
        }

        EndgameFunctionType& endgameFunction = Endgame::endgameFunctionMap.at(materialHash);
        return endgameFunction(board, score);
    }
};
