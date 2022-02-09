#include "personality.h"

Personality::Personality()
{
    this->ordinal = 0;
}

Personality::~Personality()
{

}

Personality::iterator Personality::begin()
{
    return this->parameterList.begin();
}

Personality::iterator Personality::end()
{
    return this->parameterList.end();
}

Score& Personality::operator[](std::string index)
{
    return this->parameterList[index];
}

bool Personality::operator> (const Personality& p) const
{
    return this->ordinal > p.ordinal;
}

void Personality::clear()
{
    this->parameterList.clear();
}

std::int32_t Personality::getOrdinal() const
{
    return this->ordinal;
}

Score Personality::getParameter(std::string& name) const
{
    return this->parameterList.find(name)->second;
}

void Personality::setOrdinal(std::int32_t ordinal)
{
    this->ordinal = ordinal;
}

void Personality::setParameter(std::string& name, Score score)
{
    //First, make sure the parameter exists
    this->parameterList[name];

    //Use a reference and add the incoming parameter to the existing one
    Score& oldScore = this->parameterList.find(name)->second;
    oldScore += score;
}
