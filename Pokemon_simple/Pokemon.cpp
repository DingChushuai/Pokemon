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

bool Pokemon::UseSkill(Skill* skill, Pokemon* user, Pokemon* target)
{
    return false;
}

void Pokemon::Print()
{
}

void Pokemon::PrintDetail()
{
}

int Pokemon::GetSellPrice()
{
    return 0;
}
