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
				break;
		}
	}
}
