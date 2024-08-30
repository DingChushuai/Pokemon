#pragma once
#include "PokemonLib.h"
class Combat
{
public:
    Combat() {};
    ~Combat() {};
    void InitWildCombat(int id, int level,PokemonLib& pokemonLib); 
    void InitTrainerCombat(int battleId, PokemonLib& pokemonLib);
};

