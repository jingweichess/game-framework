#pragma once

#include <map>
#include <string>

#include "../types/score.h"

class Personality {
protected:
    std::map<std::string, Score> parameterList;
public:
    using iterator = typename std::map<std::string, Score>::iterator;

    Personality();
    ~Personality();

    iterator begin();
    iterator end();

    void setParameter(std::string& name, Score score);
};
