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

void Game::Run()
{
	while (gameSenceStack.empty() == false)
	{
		ClearScreen();
		gameSence= gameSenceStack.back();
		soundPlayer.AdjustMusic(gameSence);
		sceneDrawer.draw(gameSence, &money, currentMap, &log, &combat);
		switch (gameSence)
		{
            case START_MENU:
				vector<Text> Menu;
				Menu.push_back(Text("1. ��ʼ����Ϸ\n"));
				Menu.push_back(Text("2. ������Ϸ\n"));
				Menu.push_back(Text("3. �˳���Ϸ\n"));
				int choice = command.chooseFromList(Menu);
				if (choice == 1)
				{

				}
				else if (choice == 2)
				{

				}
				else if (choice == 3 || choice == 0)
				{
					gameSenceStack.clear();
				}

				break;
		}
	}
}
