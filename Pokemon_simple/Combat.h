#pragma once
#include "PokemonLib.h"
#include "Log.h"
class Combat
{
public:
    Combat() {};
    ~Combat() {};
    void InitWildCombat(int id, int level,PokemonLib* pokemonLib); 
    void InitTrainerCombat(int battleId, PokemonLib* pokemonLib);
    PokemonLib* pokemonLib;
    vector<Pokemon*> myPokemons;
    vector<Pokemon*> enemyPokemons; 
    Pokemon* pokemonNow;
    Pokemon* enemyNow;
    vector<Pokemon*> pokemonAvailable();
    vector<Pokemon*> enemyAvailable(); 
    vector<Text> PokemonAvailableText();
    Text ChangePokemon(Pokemon* pokemon);
    bool TryToEscape();
    vector<Text> ShowPokemonInfo(); //显示敌我方宝可梦信息
    vector<Text> ShowPokemonSkill();
    bool IsTrainerBattle();
    bool IsWildBattle();
    int GetExperienceFromBattle(Pokemon* beatenPokemon);
    void EndCombat();
    vector<vector<float>> damageTable;  //属性相克表,构造函数中初始化
    bool lastCombatWin; //上一次战斗是否胜利
    Log combatLog;  //战斗日志,战斗完成后清除
    bool isTrainer;
    int escapeFailedTimes; //逃跑失败次数 
    vector<pair<Pokemon*,Pokemon*>> beaten; //我方宝可梦战胜的敌方宝可梦, 用于计算战斗经验


};

