#pragma once

#include <string>

template <class T>
class Communicator
{
protected:
    bool finished;
public:
    Communicator()
    {
        this->finished = false;
    }

    ~Communicator() {}

    void finish()
    {
        this->finished = true;
    }

    bool isFinished()
    {
        return this->finished;
    }
	
    void processCommand(std::string& cmd)
    {
        static_cast<T*>(this)->processCommandImplementation(cmd);
    }
};
