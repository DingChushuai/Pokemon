#pragma once

#ifndef TOOLS_H
#define TOOLS_H

const enum Color
{
    None = 0,	//����̨Ĭ�����Ӧ���ǰ�ɫ
    RED,
    GREEN,
    BLUE,
    YELLOW,
    CYAN,		//ǳ��ɫ
    MAGENTA,	//��ɫ
    GRAY,		//��ɫ
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
inline pair<int, int> GetPos();		//��ȡ��ǰ���λ��
inline void GotoXY(int x, int y);	//�ƶ���굽ָ��λ��
inline void ClearScreen();				//����

#endif
