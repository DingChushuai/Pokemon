#pragma once
#ifndef SCENEDRAWER_H
#define SCENEDRAWER_H
#include "Game.h"

class SceneDrawer
{
public:
    SceneDrawer(Game& game):_game(&game) {};
    void draw();    //������Ϸ״̬���Ƴ���, ֻ���ƹ̶�����Ĳ���, ������ѡ����仯�Ĳ�����Command�����
private:
    Game* _game;
    void drawMenu();    //ֻ����gamebar
    void drawGame();    //չʾ����͵�ͼ������Ϣ��Log, ���ڲ�����ı��ͼ��Ϣ, ������Command�����
    void drawSetting(); //ֻ��ʾ"����", ��Ϊ���õľ������ݻ�����ѡ����仯, ѡ�е�ѡ��������, ������Command�����
    void drawPokemonLib(); //ֻ��ʾ"�����ο�", ��Ϊ�����ο�ľ������ݻ�����ѡ����仯
    void drawPokemonInfo(); //��ʾ"��������Ϣ"
    void drawBackpack(); //ֻ��ʾ"����", ��Ϊ�����ľ������ݻ�����ѡ����仯
    void drawPokemonCenter(); //��ʾ"����������", ��Я���ı�������Ϣ
    void drawShop(); //ֻ��ʾ"�̵�"��Ǯ����Ϣ, ��Ϊ�̵�ľ������ݻ�����ѡ����仯
    void drawShooseBuyOrSell(); //ֻ��ʾ"ѡ��������"
    void drawBuyItem(); //ֻ��ʾ"������Ʒ"
    void drawSellPokemon(); //ֻ��ʾ"���۱�����"
    void drawSellItem(); //ֻ��ʾ"������Ʒ"
    void drawCombat(); //��ʾ"ս��", ��ս����Ϣ
    void drawDebug(); //��ʾ"����"�͵��Եİ�������
};

#endif // !SCENEDRAWER_H
