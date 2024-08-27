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
				cout << "欢迎来到宝可梦世界" << endl;
				cout << "请选择一个选项" << endl;
				Menu.push_back(Text("1. 开始新游戏\n"));
				Menu.push_back(Text("2. 加载游戏  \n"));
				Menu.push_back(Text("3. 退出游戏  \n"));
                Menu.push_back(Text("4. 退出游戏  \n"));
                Menu.push_back(Text("5. 退出游戏  \n"));
				int choice = command.chooseFromList(Menu, 2);
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
