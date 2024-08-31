#pragma once
#include "PokemonLib.h"
#include "Text.h"
class Combat
{
public:
    Combat() {};
    ~Combat() {};
    void InitWildCombat(int id, int level,PokemonLib& pokemonLib); 
    void InitTrainerCombat(int battleId, PokemonLib& pokemonLib);
    vector<Pokemon*> myPokemons;
    vector<Pokemon*> enemyPokemons; 
    Pokemon* pokemonNow;
    Pokemon* enemyNow;
    vector<Pokemon*> pokemonAvailable();
    vector<Pokemon*> enemyAvailable(); 
    vector<Text> PokemonAvailableText();
    Text ChangePokemon(Pokemon* pokemon);
    bool TryToEscape();
    vector<Text> ShowPokemonInfo();
    bool IsTrainerBattle();
    bool IsWildBattle();
    void EndCombat();
    vector<vector<float>> damageTable;  //属性相克表,构造函数中初始化
    bool lastCombatWin; //上一次战斗是否胜利
private:
    bool isTrainer;
    vector<pair<Pokemon*,Pokemon*>> beaten; //我方宝可梦战胜的敌方宝可梦, 用于计算战斗经验


};

