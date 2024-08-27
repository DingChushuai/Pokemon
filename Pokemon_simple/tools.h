#pragma once

#ifndef TOOLS_H
#define TOOLS_H

#ifndef GAME_SENCE
#define GAME_SENCE
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
#endif

const enum Color
{
    None = 0,	//控制台默认输出应该是白色
    RED,
    GREEN,
    BLUE,
    YELLOW,
    CYAN,		//浅蓝色
    MAGENTA,	//紫色
    GRAY,		//灰色
};

#define NPC_INFO_PATH = "resources/NPC_Info.csv"
#define POKEMON_INFO_PATH = "resources/Pokemon_Info.csv"
#define PROP_INFO_PATH = "resources/Prop_Info.csv"
#define SKILL_INFO_PATH = "Skill_Info.csv"

#define  NPC_STATE_PATH = "saves/NPC_State.csv"
#define  POKEMON_STATE_PATH = "saves/Pokemon_State.csv"
#define  BACKPACK_STATE_PATH = "saves/Backpack_State.csv"

#pragma once
#include <string>
#include <vector>
#include <Windows.h>
#include <cstdlib>
using namespace std;

inline vector<string> Split(const string& s, char delimiter);
inline int Stoi(const string& s);
inline pair<int, int> GetPos();		//获取当前光标位置
inline void GotoXY(int x, int y);	//移动光标到指定位置
inline void ClearScreen();				//清屏

#endif
