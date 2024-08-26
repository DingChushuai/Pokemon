#pragma once

#include "SoundPlayer.h"
#include "Log.h"
#include "SceneDrawer.h"
#include "NPC.h"

class Game
{
    const enum GameSence
    {
        START_MENU = 0, //开始菜单:to GAME GAMEOVER
        GAME,       //游戏主界面:to SETTING POKEMON_LIB BACKPACK POKEMON_CENTER SHOP COMBAT DEBUG
        SETTING,    //设置界面
        POKEMON_LIB,    //宝可梦库界面:to POKEMON_INFO
        POKEMON_INFO,   //宝可梦信息界面
        BACKPACK,       //背包界面
        POKEMON_CENTER, //宝可梦中心界面
        SHOP,           //商店界面:to SHOOSE_BUY_OR_SELL
        SHOOSE_BUY_OR_SELL, //选择购买或出售界面: to BUY_ITEM SELL_POKEMON SELL_ITEM
        BUY_ITEM,
        SELL_POKEMON,
        SELL_ITEM,
        COMBAT,         //战斗界面
        DEBUG           //调试界面
    };

public:
    Game() : sceneDrawer() { gameSenceStack.push_back(START_MENU);};
    ~Game() {};
    void Run();
    int playerX, playerY;
    int money;
    bool inCombat;
    GameSence gameSence;
    SoundPlayer soundPlayer;
    Log log;
    SceneDrawer sceneDrawer;
    vector<GameSence> gameSenceStack;
    vector<NPC> npcs;

};

