#include "Pokemon.h"
#pragma once

Pokemon::Pokemon(int ID, int level)
{
}

Pokemon::Pokemon(const Pokemon& other)
{
}

Pokemon::Pokemon(string name, pair<Type, Type> type, int hp, int maxHp, int level, int experience, int experienceToNextLevel, int attack, int defense, int speed, int specialAttack, int specialDefense, PokemonStatu statu, vector<Skill> skills, int evolutionLevel, int evolutionID, int captureRate)
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
