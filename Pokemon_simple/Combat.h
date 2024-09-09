#pragma once
#include "PokemonLib.h"
#include "Log.h"
class Combat
{
public:
    Combat();
    ~Combat() {};
    void InitWildCombat(int id, int level,PokemonLib* pokemonLib);  //初始化野生宝可梦战斗
    void InitTrainerCombat(int battleId, PokemonLib* pokemonLib);   //初始化训练家战斗
    PokemonLib* pokemonLib; //引用Game中的宝可梦库
    vector<Pokemon*> myPokemons;    //我方宝可梦,由宝可梦仓库复制临时的样本
    vector<Pokemon*> enemyPokemons;     //敌方宝可梦
    Pokemon* pokemonNow; //当前战斗的宝可梦
    Pokemon* enemyNow;  //当前战斗的敌方宝可梦
    vector<Pokemon*> pokemonAvailable();    //返回当前可用的宝可梦
    vector<Pokemon*> enemyAvailable();  //返回当前可用的敌方宝可梦
    vector<Text> PokemonAvailableText();    //返回当前可用的宝可梦的文本
    Text ChangePokemon(Pokemon* pokemon);   //更换宝可梦
    bool TryToEscape();     //尝试逃跑
    vector<Text> ShowPokemonInfo(); //显示敌我方宝可梦信息
    vector<Text> ShowPokemonSkill();    //显示当前宝可梦技能
    bool IsTrainerBattle();
    bool IsWildBattle();
    int GetExperienceFromBattle(Pokemon* beatenPokemon);    //计算战斗经验
    void EndCombat();   //战斗结束,清空战斗数据,回传战斗结果
    vector<vector<float>> damageTable;  //属性相克表,构造函数中初始化
    bool lastCombatWin; //上一次战斗是否胜利
    Log combatLog;  //战斗日志,战斗完成后清除
    bool isTrainer; //是否是训练家战斗
    int escapeFailedTimes; //逃跑失败次数 
    vector<pair<Pokemon*,Pokemon*>> beaten; //我方宝可梦战胜的敌方宝可梦, 用于计算战斗经验


};

