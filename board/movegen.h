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

	NodeCount generateAllMoves(Board& board, MoveList<MoveType>& moveList, bool countOnly = false)
	{
		return static_cast<T*>(this)->generateAllMovesImplementation(board, moveList, countOnly);
	}
};
