#include "SceneDrawer.h"
#pragma once

void SceneDrawer::draw(GameSence gs, int money, Map* map, Log* log, Combat* combat, Pokemon* pokemon)
{
	switch (gs) {
	case 0:
		SceneDrawer::drawMenu();
	case 1:
		SceneDrawer::drawGame(money, map, log);
		break;
	case 2:
		SceneDrawer::drawSetting();
		break;
	case 3:
		SceneDrawer::drawPokemonLib();
		break;
	case 4:
		SceneDrawer::drawPokemonInfo(pokemon);
		break;
	case 5:
		SceneDrawer::drawBackpack();
		break;
	case 6:
		SceneDrawer::drawPokemonCenter(pokemon);
		break;
	case 7:
		SceneDrawer::drawShop(money);
		break;
	case 8:
		SceneDrawer::drawShooseBuyOrSell();
		break;
	case 9:
		SceneDrawer::drawBuyItem();
		break;
	case 10:
		SceneDrawer::drawSellPokemon();
		break;
	case 11:
		SceneDrawer::drawSellItem();
		break;
	case 12:
		SceneDrawer::drawCombat(combat);
		break;
	case 13:
		SceneDrawer::drawDebug();
		break;
	case 14:
		SceneDrawer::drawWorldMap(map);
		break;
	}
}

void SceneDrawer::drawMenu()
{
	Text("��ǰΪ'�˵�'����\n", Color::YELLOW).Print();
}

void SceneDrawer::drawGame(int money, Map* map, Log* log)
{
	//֮ǰ�鳤˵�ⲿ�ֺܸ���������
}

void SceneDrawer::drawSetting()
{
	Text("��ǰΪ'����'����\n", Color::BLUE).Print();
}

void SceneDrawer::drawPokemonLib()
{
	Text("��ǰΪ'�����ο�'����\n", Color::GREEN).Print();
}

void SceneDrawer::drawPokemonInfo(Pokemon* pokemon)
{
	pokemon->Print();//��ӡ�����λ�����Ϣ
}

void SceneDrawer::drawBackpack()
{
	Text("��ǰΪ'����'����\n", Color::RED).Print();
}


void SceneDrawer::drawPokemonCenter(Pokemon *pokemon)
{
	pokemon->PrintDetail();//��ӡ��������ϸ��Ϣ
}

void SceneDrawer::drawShop(int money)
{
	Text("��ǰΪ'�̵�'����\n �㵱ǰӵ�н������Ϊ", Color::MAGENTA).Print();
	printf("%d", money);
}


void SceneDrawer::drawShooseBuyOrSell()
{
	Text("ѡ��������\n", Color::GRAY).Print();
}

void SceneDrawer::drawBuyItem()
{
	Text("������Ʒ\n", Color::RED).Print();
}

void SceneDrawer::drawSellPokemon()
{
	Text("���۱�����\n", Color::RED).Print();
}

void SceneDrawer::drawSellItem()
{
	Text("������Ʒ\n", Color::RED).Print();
}

void SceneDrawer::drawCombat(Combat* combat)
{
	//combatս��ϵͳ��û����
}

void SceneDrawer::drawDebug()
{
	//�ⲿ�ֲ�֪����ô��
}
void drawWorldMap(Map* map)
{
	//û��map�ļ����ҵ���ӡ��ͼ�ĺ�����
}