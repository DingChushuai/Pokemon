#pragma once
#include "PokemonLib.h"
class Combat
{
public:
    Combat() {};
    ~Combat() {};
    void InitWildCombat(int id, int level,PokemonLib& pokemonLib); 
    void InitTrainerCombat(int battleId, PokemonLib& pokemonLib);
private:
    vector<vector<float>> damageTable;  //属性相克表,构造函数中初始化
};

