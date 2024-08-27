#pragma once

#include "SoundPlayer.h"
#include "Log.h"
#include "SceneDrawer.h"
#include "NPC.h"

class Game
{
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

