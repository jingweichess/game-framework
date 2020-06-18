#pragma once

#include <vector>

template <class T, class Board, class MoveHistoryStruct>
class MoveHistory
{
protected:
    std::vector<MoveHistoryStruct> moveHistoryList;
public:
    using BoardType = Board;
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
        MoveHistoryStruct moveHistoryStruct;

        static_cast<T*>(this)->getNextMoveHistoryEntry(moveHistoryStruct, board, move);

        this->moveHistoryList.push_back(moveHistoryStruct);
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
