#pragma once

#include <cstdint>
#include <fstream>
#include <string>
#include <vector>

#include "../clock/clock.h"

#include "../personality/parametermap.h"
#include "../personality/personality.h"

template <class T, class Searcher, class GameResult>
class Player
{
protected:
	std::vector<typename Searcher::BoardType> boardList;
	std::uint32_t currentBoard;

	Clock clock;
	ParameterMap parameterMap;
	Personality personality;

	Searcher searcher;

	typename Searcher::BoardType& getCurrentBoard()
	{
		return this->boardList[this->currentBoard];
	}
public:
	using BoardType = typename Searcher::BoardType;
	using GameResultType = GameResult;
	using MoveGeneratorType = typename Searcher::MoveGeneratorType;
	using MoveType = typename Searcher::MoveType;

	Player()
	{
		this->currentBoard = 0;

		BoardType board;
		this->boardList.push_back(board);
	}

	~Player() {}

	void applyPersonality(bool strip = false)
	{
		std::int32_t multiplier = strip ? -1 : 1;

		for (Personality::iterator it = this->personality.begin(); it != this->personality.end(); ++it) {
			const std::string& name = it->first;
			Score score = multiplier * it->second;

			//First, make sure the parameter exists in case we're passed bad parameters
			this->parameterMap[name];

			Score* parameterScore = this->parameterMap.find(name)->second;
			*parameterScore += score;
		}

		static_cast<T*>(this)->applyPersonalityImplementation(strip);
	}

	GameResultType checkBoardGameResult(BoardType& board)
	{
		return static_cast<T*>(this)->checkBoardGameResultImplementation(board);
	}

	void doMove(MoveType& move)
	{
		BoardType nextBoard = this->boardList[this->currentBoard];
		nextBoard.doMove(move);

		this->currentBoard++;

		if (this->currentBoard >= this->boardList.size()) {
			this->boardList.push_back(nextBoard);
		}
		else {
			this->boardList[this->currentBoard] = nextBoard;
		}

		this->searcher.addMoveToHistory(nextBoard, move);
	}

	void getMove(MoveType& move)
	{
		this->applyPersonality();

		static_cast<T*>(this)->getMoveImplementation(move);

		this->stripPersonality();
	}

	Clock& getClock()
	{
		return this->clock;
	}

	void loadPersonalityFile(std::string& personalityFileName)
	{
		std::fstream personalityFile;

		personalityFile.open(personalityFileName, std::fstream::ios_base::in);

		if (!personalityFile.is_open()) {
			return;
		}

		while (true) {
			std::string parameterName;
			Score parameterScore;

			personalityFile >> parameterName >> parameterScore;

			if (personalityFile.eof()) {
				break;
			}

			this->setParameter(parameterName, parameterScore);
		}

		personalityFile.close();
	}

	void resetSpecificPosition(std::string& fen)
	{
		this->currentBoard = 0;

		BoardType board;
		board.resetSpecificPosition(fen);

		this->boardList[0] = board;

		this->searcher.resetMoveHistory();
	}

	void resetStartingPosition()
	{
		this->currentBoard = 0;

		BoardType board;
		board.resetStartingPosition();

		this->boardList[0] = board;

		this->searcher.resetMoveHistory();
	}

	void setBoard(BoardType& board)
	{
		this->boardList[0] = board;
		this->currentBoard = 0;
	}

	void setClock(Clock& clock)
	{
		this->clock = clock;
	}

	void setParameter(std::string& name, Score score)
	{
		this->personality.setParameter(name, score);
	}

	void setPersonality(Personality& personality)
	{
		this->personality = personality;
	}

	void stripPersonality()
	{
		this->applyPersonality(true);
	}

	void undoMove()
	{
		if (this->currentBoard > 0) {
			this->currentBoard--;
		}
	}
};
