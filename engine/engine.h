#pragma once

#include <iostream>
#include <string>

#include "../comm/comm.h"

#include "../player/player.h"

template <class T, class Communicator>
class Engine
{
protected:
    Communicator communicator;
public:
    Engine() {}
    ~Engine() {}

    void start(int argc, char** argv)
    {
        for (int i = 1; i < argc; i++) {
            std::string arg = std::string(argv[i]);
            this->communicator.processCommand(arg);
        }

        while (!this->communicator.isFinished()) {
            std::string cmd;

            if (!std::getline(std::cin, cmd)) {
                cmd = "quit";
            }

            this->communicator.processCommand(cmd);
        }
    }
};
