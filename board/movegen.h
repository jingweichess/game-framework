#pragma once

#include "board.h"

#include "../types/movelist.h"
#include "../types/nodecount.h"

template <class T, class Board>
class MoveGenerator
{
public:
	using BoardType = Board;
	using MoveType = typename BoardType::MoveType;

	NodeCount generateAllMoves(BoardType& board, MoveList<MoveType>& moveList, bool countOnly = false) const
	{
		return static_cast<const T *>(this)->generateAllMovesImplementation(board, moveList, countOnly);
	}
};
