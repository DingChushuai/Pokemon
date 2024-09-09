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
    void Run(); //��Ϸ��ѭ��
    int playerX, playerY;
    int money;
    bool inCombat;
    GameSence gameSence;    //��ǰ��Ϸ����
    SoundPlayer soundPlayer;    //��Ч������
    Log log;    //��־
    Command command;    //ָ�������
    vector<GameSence> gameSenceStack;   //��Ϸ����ջ
    vector<NPC*> npcs;  //NPC�б�,һ���Լ�������NPC
    vector<Map*> maps;  //��ͼ�б�,��̬����
    Map* currentMap;    //��ǰ��ͼ
    Combat combat;  //ս��ϵͳ
    PokemonLib pokemonLib; //�����ο�
    Pokemon* pokemonNow;
    Backpack backpack;  //����
    Shop shop;  //�̵�

private:
    void Init();    //����Ϸ��ʼ��
    void Load();       //���ش浵
    void Save();    //����浵
    void DrawTitle();   //���Ʊ���
    void DrawWorldMap();    //���������ͼ
    void ActOnMap();    //�ڵ�ͼ���ж�����Ҫ�߼�
    bool UseProp(Prop* prop);   //ʹ�õ���,�������ڵ�ͼ��ʹ�û���ս����ʹ��
    void UseSkill(Skill* skill, Pokemon* user, Pokemon* target);    //ʹ�ü���
    void ChangeMusic(); //���ݵ�ͼ�����л�����
    bool ChangeNPCState(NPC* npc);  //���Ըı�NPC״̬,�����Ƿ�ɹ�
    void StartCombat(); //��ʼս��
};

