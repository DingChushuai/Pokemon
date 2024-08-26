#pragma once

#ifndef TOOLS_H
#define TOOLS_H

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
#define SKILL_INFO_PATH = "resources/Skill_Info.csv"

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
inline int stoi(const string& s);
inline pair<int, int> GetPos();		//获取当前光标位置
inline void GotoXY(int x, int y);	//移动光标到指定位置
inline void ClearScreen();				//清屏

#endif
