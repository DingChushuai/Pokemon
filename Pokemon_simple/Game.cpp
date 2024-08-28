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
				Menu.push_back(Text("1. ��ʼ����Ϸ\n"));
				Menu.push_back(Text("2. ������Ϸ  \n"));
				Menu.push_back(Text("3. �˳���Ϸ  \n"));
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
