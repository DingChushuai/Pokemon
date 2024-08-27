#include "Game.h"

Game::Game()
{
	gameSenceStack.push_back(START_MENU);
    gameSence = START_MENU;
	playerX= 0;
    playerY= 0;
    money = 0;
    currentMap = nullptr;
	inCombat = false;
}

/*
const enum GameSence
{
	START_MENU = 0, //开始菜单:to GAME GAMEOVER
	GAME,       //游戏主界面:to SETTING POKEMON_LIB BACKPACK POKEMON_CENTER SHOP COMBAT DEBUG
	SETTING,    //设置界面
	POKEMON_LIB,    //宝可梦库界面:to POKEMON_INFO
	POKEMON_INFO,   //宝可梦信息界面
	BACKPACK,       //背包界面
	POKEMON_CENTER, //宝可梦中心界面
	SHOP,           //商店界面:to SHOOSE_BUY_OR_SELL
	SHOOSE_BUY_OR_SELL, //选择购买或出售界面: to BUY_ITEM SELL_POKEMON SELL_ITEM
	BUY_ITEM,
	SELL_POKEMON,
	SELL_ITEM,
	COMBAT,         //战斗界面
	DEBUG           //调试界面
};
*/

void Game::Run()
{
	while (gameSenceStack.empty() == false)
	{
		ClearScreen();
		gameSence= gameSenceStack.back();
		soundPlayer.AdjustMusic(gameSence);
		sceneDrawer.draw(gameSence, &money, currentMap, &log, &combat);
		vector<Text> Menu;
		switch (gameSence)
		{
            case START_MENU:
				Menu.push_back(Text("1. 开始新游戏\n"));
				Menu.push_back(Text("2. 加载游戏  \n"));
				Menu.push_back(Text("3. 退出游戏  \n"));
				int choice = command.chooseFromList(Menu);
				if (choice == 1)
				{
					Init();
					gameSenceStack.push_back(GAME);
				}
				else if (choice == 2)
				{
					Load();
					gameSenceStack.push_back(GAME);
				}
				else if (choice == 3 || choice == 0)
				{
					gameSenceStack.clear();
				} 
				break;
            case GAME:

				break;

		}
	}
}

void Game::Init()
{
}

void Game::Load()
{
}

void Game::Save()
{
}

int Game::ActOnMap()
{
	return 0;
}
