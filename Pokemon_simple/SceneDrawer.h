#pragma once
#ifndef SCENEDRAWER_H
#define SCENEDRAWER_H

#include "tools.h"
#include "Map.h"
#include "Log.h"
#include "PokemonLib.h"
#include "Combat.h"

class SceneDrawer
{
public:
    SceneDrawer(){};
    void draw(GameSence gs, int* money = 0, Map* map = nullptr, Log* log = nullptr, Combat* combat = nullptr);    //������Ϸ״̬���Ƴ���, ֻ���ƹ̶�����Ĳ���, ������ѡ����仯�Ĳ�����Command�����
private:
    void drawMenu();    //ֻ����gamebar
    void drawGame(int money, Map* map, Log* log);    //չʾ����͵�ͼ������Ϣ��Log, ���ڲ�����ı��ͼ��Ϣ, ������Command�����
    void drawSetting(); //ֻ��ʾ"����", ��Ϊ���õľ������ݻ�����ѡ����仯, ѡ�е�ѡ��������, ������Command�����
    void drawPokemonLib(); //ֻ��ʾ"�����ο�", ��Ϊ�����ο�ľ������ݻ�����ѡ����仯
    void drawPokemonInfo(Pokemon* pokemon); //��ʾ"��������Ϣ"
    void drawBackpack(); //ֻ��ʾ"����", ��Ϊ�����ľ������ݻ�����ѡ����仯
    void drawPokemonCenter(); //��ʾ"����������", ��Я���ı�������Ϣ
    void drawShop(int money); //ֻ��ʾ"�̵�"��Ǯ����Ϣ, ��Ϊ�̵�ľ������ݻ�����ѡ����仯
    void drawShooseBuyOrSell(); //ֻ��ʾ"ѡ��������"
    void drawBuyItem(); //ֻ��ʾ"������Ʒ"
    void drawSellPokemon(); //ֻ��ʾ"���۱�����"
    void drawSellItem(); //ֻ��ʾ"������Ʒ"
    void drawCombat(Combat* combat); //��ʾ"ս��", ��ս����Ϣ
    void drawDebug(); //��ʾ"����"�͵��Եİ�������
};

#endif // !SCENEDRAWER_H
