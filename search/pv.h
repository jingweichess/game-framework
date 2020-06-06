#pragma once

#include <iostream>
#include <string>

#include "../clock/clock.h"

#include "../types/depth.h"
#include "../types/movelist.h"
#include "../types/nodecount.h"
#include "../types/score.h"

template <class T, class Move>
class PrincipalVariation
{
protected:
	MoveList<Move> moveList;
public:
	using iterator = typename MoveList<Move>::iterator;
	using size_type = typename MoveList<Move>::size_type;

	PrincipalVariation()
	{

	}

	~PrincipalVariation()
	{

	}

	void clear()
	{
		this->moveList.clear();
	}

	void copyBackward(PrincipalVariation<T, Move>& principalVariation, Move& move)
	{
		this->moveList = principalVariation.moveList;
		this->moveList.insert(this->moveList.begin(), move);
	}

	void print()
	{
		for (PrincipalVariation<T, Move>::iterator it = this->moveList.begin(); it != this->moveList.end(); ++it) {
			if (it != this->moveList.begin()) {
				std::cout << " ";
			}

			this->printMoveToConsole(*it);
		}
	}

	void printMoveToConsole(Move& move)
	{
		static_cast<T*>(this)->printMoveToConsoleImplementation(move);
	}

	size_type size()
	{
		return this->moveList.size();
	}

	void stringToMove(std::string& moveString, Move& move)
	{
		static_cast<T*>(this)->stringToMoveImplementation(moveString, move);
	}

	Move& operator[](const size_type _Pos)
	{
		return this->moveList[_Pos];
	}

	const Move& operator[](const size_type _Pos) const
	{
		return this->moveList[_Pos];
	}
};
