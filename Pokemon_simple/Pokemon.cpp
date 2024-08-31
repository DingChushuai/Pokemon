#include "Pokemon.h"
#pragma once

Pokemon::Pokemon(int ID, int level)
{
}

Pokemon::Pokemon(const Pokemon& other)
{
}

Pokemon::~Pokemon()
{
}

vector<Text> Pokemon::GetDetail()
{
    return vector<Text>();
}

int Pokemon::GetSellPrice()
{
    return 0;
}

string Pokemon::GetTypeName(int typeID)
{
    return string();
}

string Pokemon::GetStatuName(int statuID)
{
    return string();
}

Text Pokemon::LevelUp()
{
    return Text();
}

Text Pokemon::Evolve()
{
    return Text();
}

int Pokemon::GetBasicExperience()
{
    return 0;
}

Text Pokemon::GetExperience(int experience)
{
    return Text();
}

int Pokemon::GetCaptureRate()
{
    return 0;
}

void Pokemon::GetBasicValue(Value)
{
}

int Pokemon::GetRandomIndividualValue()
{
    return 0;
}

int Pokemon::CalculateExperienceToNextLevel()
{
    return 0;
}

Pokemon::ATTRIBUTE Pokemon::CalculateAttribute()
{
    return ATTRIBUTE();
}

