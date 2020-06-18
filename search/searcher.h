#pragma once

#include <algorithm>
#include <cstdint>

#include "pv.h"

#include "../clock/clock.h"

#include "../eval/evaluator.h"

#include "../types/depth.h"
#include "../types/nodecount.h"
#include "../types/score.h"

static constexpr bool enableAllSearchFeatures = true;

static constexpr bool enableAspirationWindow = enableAllSearchFeatures && true;

template <class T, class Evaluator, class MoveGenerator, class MoveHistory, class PrincipalVariation>
class Searcher
{
protected:
    Clock clock;
    Evaluator evaluator;
    MoveGenerator moveGenerator;
    MoveHistory moveHistory;

    NodeCount nodeCount;
    bool abortedSearch;

public:
    using BoardType = typename Evaluator::BoardType;
    using MoveGeneratorType = MoveGenerator;
    using MoveType = typename BoardType::MoveType;
    using PrincipalVariationType = PrincipalVariation;

    Searcher()
    {
        this->abortedSearch = false;
        this->nodeCount = ZeroNodes;
    }
    ~Searcher() {}

    void addMoveToHistory(BoardType& board, MoveType& move)
    {
        this->moveHistory.addMoveToHistory(board, move);
    }

    void initializeSearch(BoardType& board)
    {
        this->abortedSearch = false;
        this->nodeCount = ZeroNodes;

        this->clock.startClock();

        static_cast<T*>(this)->initializeSearchImplementation(board);
    }

    Score iterativeDeepeningLoop(BoardType& board, PrincipalVariationType& principalVariation)
    {
        this->initializeSearch(board);

        Score aspirationWindowDelta = Score(40);

        Score previousScore = NO_SCORE;
        Score alpha = -WIN_SCORE, beta = WIN_SCORE;
        Score bestScore = -WIN_SCORE;

        Depth searchDepth = Depth::ONE * 2;

        bool isSearching = true;
        bool foundMateSolution = false;

        while (isSearching) {
            if (enableAspirationWindow
                && !foundMateSolution
                && (searchDepth >= Depth::ONE * 3)) {
                alpha = std::max(previousScore - aspirationWindowDelta, -WIN_SCORE);
                beta = std::min(previousScore + aspirationWindowDelta, WIN_SCORE);
            }
            else if (foundMateSolution) {
                alpha = -WIN_SCORE;
                beta = previousScore + 1;
            }

            Score score = this->rootSearch(board, principalVariation, searchDepth, alpha, beta);
            foundMateSolution = IsMateScore(score);

            while (enableAspirationWindow
                && !foundMateSolution
                && !this->wasSearchAborted()) {
                if (score <= alpha) {
                    alpha = std::max(score - aspirationWindowDelta, -WIN_SCORE);
                }
                else if (score >= beta) {
                    beta = std::min(score + aspirationWindowDelta, WIN_SCORE);
                }
                else {
                    break;
                }

                score = this->rootSearch(board, principalVariation, searchDepth, alpha, beta);
                foundMateSolution = IsMateScore(score);

                aspirationWindowDelta += Score(40);
            }

            if (this->wasSearchAborted()) {
                break;
            }

            isSearching = this->clock.shouldContinueSearch(searchDepth, this->getNodeCount());

            previousScore = score;
            searchDepth++;
        }

        return bestScore;
    }

    NodeCount getNodeCount()
    {
        return this->nodeCount;
    }

    void removeLastMoveFromHistory()
    {
        this->moveHistory.removeSingleMove();
    }

    void resetMoveHistory()
    {
        this->moveHistory.resetHistory();
    }

    Score rootSearch(BoardType& board, PrincipalVariationType& principalVariation, Depth maxDepth, Score alpha, Score beta)
    {
        return static_cast<T*>(this)->rootSearchImplementation(board, principalVariation, maxDepth, alpha, beta);
    }

    void setClock(Clock& clock)
    {
        this->clock = clock;
    }

    void setEvaluator(Evaluator& evaluator)
    {
        this->evaluator = evaluator;
    }

    bool wasSearchAborted()
    {
        return this->abortedSearch;
    }
};
