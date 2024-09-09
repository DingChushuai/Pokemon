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
    DEBUG,           //调试界面
    WORLD_MAP 
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
    GRAY,		//白色
    BLACK,		//黑色
};

#define NPC_INFO_PATH "NPC_Info.csv"
#define POKEMON_INFO_PATH "Pokemon_Info.csv"
#define PROP_INFO_PATH "Prop_Info.csv"
#define SKILL_INFO_PATH "Skill_Info.csv"
#define BATTLE_INFO_PATH "Battle_Info.csv"

#define  NPC_STATE_PATH "NPC_State.csv"
#define  POKEMONLIB_STATE_PATH "PokemonLib_State.csv"
#define  BACKPACK_STATE_PATH "Backpack_State.csv"
#define  GAME_STATE_PATH "Game_State.txt"

#define  WORLD_MAP_PATH "worldmap.txt"
#define  GAMEBAR_PATH "gamebar.txt"

#define PROPS_COUNT 70
#define NPCS_COUNT 37
#define MAX_POKEMON_INGAME 6

#pragma once
#include <string>
#include <vector>
#include <Windows.h>
#include <windows.h>
#include <cstdlib>
using namespace std;

//按照特定字符切分字符串
inline vector<string> Split(const string& s, char delimiter)
{
    vector<string>out;
    string temp = "";
    for (int i = 0; i < s.size(); i++)
    {
        if (s[i] == delimiter) { out.push_back(temp); temp = ""; }
        else temp += s[i];
    }
    out.push_back(temp);
    return out;
}

//获取当前光标位置
inline pair<int, int> GetPos() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO  pos;
    if (GetConsoleScreenBufferInfo(hConsole,&pos)) {
        return make_pair(pos.dwCursorPosition.X, pos.dwCursorPosition.Y);
    }
    else {
        return make_pair(-1, -1);
    }
}

//设置光标位置
inline void GotoXY(int x, int y) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos = { (SHORT)x, (SHORT)y };
    SetConsoleCursorPosition(hConsole, pos);
}

//清屏
inline void ClearScreen()
{
    system("cls");
}

//隐藏光标
inline void HideCursor() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    cursorInfo.dwSize = 100; // 光标的百分比大小
    cursorInfo.bVisible = FALSE; // 光标不可见
    SetConsoleCursorInfo(hConsole, &cursorInfo);
}

//显示光标
inline  void ShowCursor() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    cursorInfo.dwSize = 100;
    cursorInfo.bVisible = TRUE; // 光标可见
    SetConsoleCursorInfo(hConsole, &cursorInfo);
}

#endif
