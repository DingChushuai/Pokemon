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
    DEBUG,           //���Խ���
    WORLD_MAP 
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

//�����ض��ַ��з��ַ���
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

//��ȡ��ǰ���λ��
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

//���ù��λ��
inline void GotoXY(int x, int y) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos = { (SHORT)x, (SHORT)y };
    SetConsoleCursorPosition(hConsole, pos);
}

//����
inline void ClearScreen()
{
    system("cls");
}

//���ع��
inline void HideCursor() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    cursorInfo.dwSize = 100; // ���İٷֱȴ�С
    cursorInfo.bVisible = FALSE; // ��겻�ɼ�
    SetConsoleCursorInfo(hConsole, &cursorInfo);
}

//��ʾ���
inline  void ShowCursor() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    cursorInfo.dwSize = 100;
    cursorInfo.bVisible = TRUE; // ���ɼ�
    SetConsoleCursorInfo(hConsole, &cursorInfo);
}

#endif
