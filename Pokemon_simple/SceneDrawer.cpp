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
	Text("当前为'菜单'界面\n", Color::YELLOW).Print();
}

void SceneDrawer::drawGame(int money, Map* map, Log* log)
{
	//之前组长说这部分很复杂先留着
}

void SceneDrawer::drawSetting()
{
	Text("当前为'设置'界面\n", Color::BLUE).Print();
}

void SceneDrawer::drawPokemonLib()
{
	Text("当前为'宝可梦库'界面\n", Color::GREEN).Print();
}

void SceneDrawer::drawPokemonInfo(Pokemon* pokemon)
{
	pokemon->Print();//打印宝可梦基本信息
}

void SceneDrawer::drawBackpack()
{
	Text("当前为'背包'界面\n", Color::RED).Print();
}


void SceneDrawer::drawPokemonCenter(Pokemon *pokemon)
{
	pokemon->PrintDetail();//打印宝可梦详细信息
}

void SceneDrawer::drawShop(int money)
{
	Text("当前为'商店'界面\n 你当前拥有金币数量为", Color::MAGENTA).Print();
	printf("%d", money);
}


void SceneDrawer::drawShooseBuyOrSell()
{
	Text("选择购买或出售\n", Color::GRAY).Print();
}

void SceneDrawer::drawBuyItem()
{
	Text("购买物品\n", Color::RED).Print();
}

void SceneDrawer::drawSellPokemon()
{
	Text("出售宝可梦\n", Color::RED).Print();
}

void SceneDrawer::drawSellItem()
{
	Text("出售物品\n", Color::RED).Print();
}

void SceneDrawer::drawCombat(Combat* combat)
{
	//combat战斗系统还没做好
}

void SceneDrawer::drawDebug()
{
	//这部分不知道怎么搞
}
void drawWorldMap(Map* map)
{
	//没在map文件里找到打印地图的函数？
}