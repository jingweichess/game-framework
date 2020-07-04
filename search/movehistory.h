#pragma once

#include <vector>

#include "../types/hash.h"

template <class T, class Board, class MoveHistoryStruct>
class MoveHistory
{
protected:
    std::vector<MoveHistoryStruct> moveHistoryList;
public:
    using BoardType = Board;
    using MoveHistoryStructType = MoveHistoryStruct;
    using MoveType = typename BoardType::MoveType;

    using reverse_iterator = typename std::vector<MoveHistoryStruct>::reverse_iterator;
    using size_type = typename std::vector<MoveHistoryStruct>::size_type;

    MoveHistory()
    {

    }

    ~MoveHistory()
    {

    }

    void addMoveToHistory(BoardType& board, MoveType& move)
    {
        MoveHistoryStructType moveHistoryStruct;

        static_cast<T*>(this)->getNextMoveHistoryEntry(moveHistoryStruct, board, move);

        this->moveHistoryList.push_back(moveHistoryStruct);
    }

    std::uint32_t checkForDuplicateHash(Hash hashValue)
    {
        std::uint32_t result = 0;

        for (reverse_iterator it = this->moveHistoryList.rbegin(); it != this->moveHistoryList.rend(); ++it) {
            MoveHistoryStructType& chessMoveHistoryStruct = (*it);

            if (static_cast<T*>(this)->beforeDuplicateHashCheckImplementation(hashValue, chessMoveHistoryStruct)) {
                break;
            }

            if (chessMoveHistoryStruct.hashValue == hashValue) {
                result++;
            }

            if (static_cast<T*>(this)->afterDuplicateHashCheckImplementation(hashValue, chessMoveHistoryStruct)) {
                break;
            }
        }

        return result;
    }

    void resetHistory()
    {
        this->moveHistoryList.clear();
    }

    void removeSingleMove()
    {
        this->moveHistoryList.pop_back();
    }

    void reserve(const size_type _Newcapacity)
    {
        this->moveHistoryList.reserve(_Newcapacity);
    }
};
