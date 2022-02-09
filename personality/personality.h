#pragma once

#include <cstdint>
#include <map>
#include <string>
#include <vector>

#include "../types/score.h"

class Personality {
protected:
    std::map<std::string, Score> parameterList;
    std::int32_t ordinal;
public:
    using iterator = typename std::map<std::string, Score>::iterator;

    Personality();
    ~Personality();

    iterator begin();
    iterator end();

    Score& operator[](std::string index);
    bool operator>(const Personality& p) const;

    void clear();
    std::int32_t getOrdinal() const;
    void setOrdinal(std::int32_t ordinal);

    Score getParameter(std::string& name) const;
    void setParameter(std::string& name, Score score);
};

typedef std::vector<Personality> PersonalityList;
