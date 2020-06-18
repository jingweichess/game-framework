#pragma once

#include <chrono>

#include <ctime>

#include "../types/depth.h"
#include "../types/nodecount.h"

enum ClockType {
    NO_CLOCK,
    SEARCHTIME, SEARCHDEPTH, SEARCHNODES, SEARCHLEVEL
};

typedef std::chrono::steady_clock SteadyClock;

class Clock {
protected:
    ClockType clockType;

    Depth maxSearchDepth;
    NodeCount maxSearchNodes;
    std::time_t currentSearchTime, maxSearchTime;

    NodeCount nps;

    struct {
        NodeCount moves;
        std::time_t milliseconds, increment;
    } Level;

    NodeCount movesLeft;
    std::time_t engineTimeLeft, opponentTimeLeft;

    std::chrono::time_point<SteadyClock> startTime;

    bool minimumDepthReached;

    bool handleSearchLevel(NodeCount nodeCount);
public:
    Clock();
    ~Clock();

    void initializeClock();

    std::time_t getElapsedTime(NodeCount nodeCount);
    bool shouldContinueSearch(Depth depth, NodeCount nodeCount);

    void setClockDepth(Depth depth);
    void setClockEngineTimeLeft(std::time_t engineTimeLeft);
    void setClockLevel(NodeCount moveCount, std::time_t milliseconds, std::time_t increment);
    void setClockNodes(NodeCount nodeCount);
    void setClockNps(NodeCount nps);
    void setClockOpponentTimeLeft(std::time_t opponentTimeLeft);
    void setClockSearchTime(std::time_t milliseconds);

    void startClock();
};
