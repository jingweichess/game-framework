#include "personality.h"

Personality::Personality()
{

}

Personality::~Personality()
{

}

Personality::iterator Personality::begin() {
    return this->parameterList.begin();
}

Personality::iterator Personality::end() {
    return this->parameterList.end();
}

void Personality::setParameter(std::string& name, Score score)
{
    //First, make sure the parameter exists
    this->parameterList[name];

    //Use a reference and add the incoming parameter to the existing one
    Score& oldScore = this->parameterList.find(name)->second;
    oldScore += score;
}
