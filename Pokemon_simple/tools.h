#pragma once

#ifndef TOOLS_H
#define TOOLS_H

#ifndef GAME_SENCE
#define GAME_SENCE
const enum GameSence
{
    START_MENU = 0, //��ʼ�˵�:to GAME GAMEOVER
    GAME,       //��Ϸ������:to SETTING POKEMON_LIB BACKPACK POKEMON_CENTER SHOP COMBAT DEBUG
    SETTING,    //���ý���
    POKEMON_LIB,    //�����ο����:to POKEMON_INFO
    POKEMON_INFO,   //��������Ϣ����
    BACKPACK,       //��������
    POKEMON_CENTER, //���������Ľ���
    SHOP,           //�̵����:to SHOOSE_BUY_OR_SELL
    SHOOSE_BUY_OR_SELL, //ѡ�������۽���: to BUY_ITEM SELL_POKEMON SELL_ITEM
    BUY_ITEM,
    SELL_POKEMON,
    SELL_ITEM,
    COMBAT,         //ս������
    DEBUG           //���Խ���
};
#endif

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
    BLACK,		//��ɫ
};

#define NPC_INFO_PATH "NPC_Info.csv"
#define POKEMON_INFO_PATH "Pokemon_Info.csv"
#define PROP_INFO_PATH "Prop_Info.csv"
#define SKILL_INFO_PATH "Skill_Info.csv"

#define  NPC_STATE_PATH "NPC_State.csv"
#define  POKEMON_STATE_PATH "Pokemon_State.csv"
#define  BACKPACK_STATE_PATH "Backpack_State.csv"

#pragma once
#include <string>
#include <vector>
#include <Windows.h>
#include <cstdlib>
using namespace std;

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

inline int Stoi(const string& s)
{
    return atoi(s.c_str());
}

inline pair<int, int> GetPos()
{
    return make_pair(0, 0);
}
inline void GotoXY(int x, int y)
{

}
inline void ClearScreen()
{
    system("cls");
}

#endif
