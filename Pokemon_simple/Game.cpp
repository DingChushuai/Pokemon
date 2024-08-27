#include "Game.h"

Game::Game()
{
	gameSenceStack.push_back(START_MENU);
}

void Game::Run()
{
	while (gameSenceStack.empty() == false)
	{
		gameSence= gameSenceStack.back();
		soundPlayer.AdjustMusic(gameSence);
		sceneDrawer.draw(gameSence, &money, currentMap, &log, &combat);
		switch (gameSence)
		{
            case START_MENU:
				vector<Text> Menu;
				Menu.push_back(Text("1. ��ʼ����Ϸ"));
				Menu.push_back(Text("2. ������Ϸ"));
				Menu.push_back(Text("3. �˳���Ϸ"));
				int choice = command.chooseFromList(Menu);
				if (choice == 1)
				{

				}
				else if (choice == 2)
				{

				}
				else if (choice == 3)
				{
					gameSenceStack.clear();
				}

				break;
		}
	}
}
