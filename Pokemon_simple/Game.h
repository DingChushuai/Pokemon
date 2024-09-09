#pragma once

#include "SoundPlayer.h"
#include "Log.h"
#include "NPC.h"
#include "Map.h"
#include "Combat.h"
#include "Command.h"
#include "PokemonLib.h"
#include "Backpack.h"
#include "Shop.h"

class Game
{
public:
    Game(); 
    ~Game() {};
    void Run(); //游戏主循环
    int playerX, playerY;
    int money;
    bool inCombat;
    GameSence gameSence;    //当前游戏场景
    SoundPlayer soundPlayer;    //音效播放器
    Log log;    //日志
    Command command;    //指令分析器
    vector<GameSence> gameSenceStack;   //游戏场景栈
    vector<NPC*> npcs;  //NPC列表,一次性加载所有NPC
    vector<Map*> maps;  //地图列表,动态加载
    Map* currentMap;    //当前地图
    Combat combat;  //战斗系统
    PokemonLib pokemonLib; //宝可梦库
    Pokemon* pokemonNow;
    Backpack backpack;  //背包
    Shop shop;  //商店

private:
    void Init();    //新游戏初始化
    void Load();       //加载存档
    void Save();    //保存存档
    void DrawTitle();   //绘制标题
    void DrawWorldMap();    //绘制世界地图
    void ActOnMap();    //在地图上行动的主要逻辑
    bool UseProp(Prop* prop);   //使用道具,区分是在地图上使用还是战斗中使用
    void UseSkill(Skill* skill, Pokemon* user, Pokemon* target);    //使用技能
    void ChangeMusic(); //根据地图场景切换音乐
    bool ChangeNPCState(NPC* npc);  //尝试改变NPC状态,返回是否成功
    void StartCombat(); //开始战斗
};

