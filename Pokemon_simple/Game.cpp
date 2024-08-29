#include "Game.h"
#pragma once

Game::Game()
{
	gameSenceStack.push_back(START_MENU);
    gameSence = START_MENU;
	playerX= 0;
    playerY= 0;
    money = 0;
    currentMap = nullptr;
	inCombat = false;
	pokemonNow = nullptr;
	HideCursor(); 
}

void Game::Run()
{
	while (gameSenceStack.empty() == false)
	{
		ClearScreen();
		gameSence = gameSenceStack.back();
		cout<< "GameScence: " << gameSence << endl;
		soundPlayer.AdjustMusic(gameSence);
		sceneDrawer.draw(gameSence, money, currentMap, &log, &combat);
		switch (gameSence)
		{
			case START_MENU:
			{
				vector<Text> Menu;
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
			}
			case GAME:
			{
				ActOnMap();
				break;
			}
			case SETTING:
			{
                vector<Text> Menu;
				Menu.push_back(Text("1. 保存游戏\n"));
				Menu.push_back(Text("2. 返回游戏\n"));
				Menu.push_back(Text("3. 返回标题\n"));
				Menu.push_back(Text("4. 保存并退出\n"));
				Menu.push_back(Text("5. 不保存退出\n"));
				int choice = command.chooseFromList(Menu);
				if (choice == 1)
				{
					Save();
					Text("游戏已保存", GREEN, GRAY).Print();
					log.AddLog(Text("当前进度已保存!", GREEN));
					command.Pause();
				}
				else if (choice == 2)
				{
					gameSenceStack.pop_back();
				}
				else if (choice == 3)
				{
					gameSenceStack.clear();
					gameSenceStack.push_back(START_MENU);
				}
				else if (choice == 4)
				{
					Save();
					gameSenceStack.clear();
				}
				else if (choice == 5)
				{
					gameSenceStack.clear();
				}
			break;
			}
			case POKEMON_LIB:
			{
				{
					vector<Text> pokemonsInGame = pokemonLib.GetPokemonInGameInfo();
					if (pokemonsInGame.size() == 0)
					{
                        Text("\n你的队伍中没有宝可梦，请先获取一只宝可梦!\n", RED, GRAY).Print();
                        command.Pause();
                        gameSenceStack.pop_back();
                        break;

					}
					int choice = command.chooseFromList(pokemonsInGame);
                    if (choice == 0) { gameSenceStack.pop_back(); break; }
					pokemonNow = pokemonLib.GetPokemonInGame(choice); 
                    gameSenceStack.push_back(POKEMON_INFO);
				}
                break;
			}
            case POKEMON_INFO:
            {
				{
					pokemonNow->PrintDetail();
					command.Pause();
					gameSenceStack.pop_back();
				}
				break;
            }
			case BACKPACK:
			{
				{
					vector<Text> props = backpack.GetPropsInfo();
                    if (props.size() == 0)
                    {
                        Text("\n你的背包中没有道具，请先获取一些道具!\n", RED, GRAY).Print();
                        command.Pause();
                        gameSenceStack.pop_back();
                        break;
                    }
					int choice = command.chooseFromList(props,10);
                    if (choice == 0) { gameSenceStack.pop_back(); break; } 
					Prop* PropNow = backpack.GetPropFromIndex(choice);
					if (!PropNow->IsCanUseInField())
					{
						Text("\n该道具无法在野外使用!\n", RED).Print();
                        command.Pause();
						gameSenceStack.pop_back();
						break;
					}
					UseProp(PropNow);
				}
                break;
			}
			case  POKEMON_CENTER:
			{
				{
					vector<Text> pokemonsIngame = pokemonLib.GetPokemonInGameInfo();
					vector<Text> pokemonsInLib = pokemonLib.GetPokemonInLibInfo();
					if (pokemonsIngame.size() == 0)
					{
						Text("\n你的队伍中没有宝可梦，请先获取一只宝可梦!\n", RED, GRAY).Print();
                        command.Pause();
                        gameSenceStack.pop_back();
						break;
					}
					if (pokemonsInLib.size() == 0)
					{
						Text("\n你的仓库中没有宝可梦，请获取更多宝可梦后再来看看吧!\n", RED, GRAY).Print();
						command.Pause();
						gameSenceStack.pop_back();
						break;
					}
					command.PrintfList(pokemonsIngame);
					Text("\n选择一只库中的宝可梦交换或查看详细信息\n", None, GRAY).Print();
					int indexInLib = command.chooseFromList(pokemonsInLib, 20);
					if (indexInLib == 0) { gameSenceStack.pop_back(); break; }
					vector<Text> options;
					options.push_back(Text("1. 查看详细信息\n"));
					options.push_back(Text("2. 交换宝可梦\n"));
					int choice = command.chooseFromList(options);
					if (choice == 1)
					{
						pokemonNow = pokemonLib.GetPokemonInLib(indexInLib);
						gameSenceStack.push_back(POKEMON_INFO);
						break;
					}
					else if (choice == 2)
					{
						if (pokemonsIngame.size() >= MAX_POKEMON_INGAME)
						{
							int indexInGame = command.chooseFromList(pokemonsIngame);
							if (indexInGame == 0) { break; }
							pokemonLib.SwitchPokemon(indexInLib, indexInGame);
							string pokemonName1 = "[" + pokemonLib.GetPokemonInLib(indexInLib)->name + "]";
							string pokemonName2 = "[" + pokemonLib.GetPokemonInGame(indexInGame)->name + "]";
							Text info;
							info.Add("仓库中的");
							info.Add(pokemonName1, GREEN);
							info.Add("已上阵,");
							info.Add(pokemonName2, RED);
							info.Add("已进入仓库.\n");
							log.AddLog(info);
						}
						else
						{
							pokemonLib.AddPokemonToGame(indexInLib);
							string pokemonName1 = "[" + pokemonLib.GetPokemonInLib(indexInLib)->name + "]";
							Text info;
							info.Add("仓库中的");
							info.Add(pokemonName1, GREEN);
							info.Add("已上阵.\n");
							log.AddLog(info);
						}
					}
				}
				break;
			}
			case SHOP:
			{
				{
					gameSenceStack.push_back(SHOOSE_BUY_OR_SELL);
				}
				break;
			}
			case SHOOSE_BUY_OR_SELL:
			{
				{
					vector<Text> options;
					options.push_back(Text("1. 购买道具\n"));
					options.push_back(Text("2. 卖出道具\n"));
					options.push_back(Text("3. 卖出仓库中的宝可梦\n"));
					int choice = command.chooseFromList(options,3);
                    if (choice == 0) { gameSenceStack.pop_back(); gameSenceStack.pop_back(); break; }
					if (choice == 1) { gameSenceStack.push_back(BUY_ITEM); }
					else if (choice == 2) { gameSenceStack.push_back(SELL_ITEM); }
					else if (choice == 3) { gameSenceStack.push_back(SELL_POKEMON); }
				}
                break;
			}
			case BUY_ITEM:
			{
				vector<Text> props = shop.GetPropsInShop();
				int choice = command.chooseFromList(props);
				if (choice == 0) { gameSenceStack.pop_back(); break; }
				int price = shop.GetPriceOfProp(choice);
				if (money < price)
				{
                    Text("\n你的钱不够了，请先去赚点钱吧!\n", RED).Print();
					command.Pause();
                    gameSenceStack.pop_back();
					break;
				}
				int maxCount = money / price;
				int count = command.ChooseCount(maxCount);
                if (count == 0) { gameSenceStack.pop_back(); break; }
                money -= price * count;
				Prop buyedProp = shop.BuyProp(choice, count);
				backpack.AddProp(&buyedProp);
				Text info;
                info.Add("你购买了");
                info.Add(buyedProp.GetName(), GREEN);
                info.Add("x");
                info.Add(to_string(count), YELLOW);
                log.AddLog(info);
				info.Print();
                command.Pause();
                gameSenceStack.pop_back();
                break;
			}
            case SELL_ITEM:
			{
				vector<Text> props = backpack.GetPropsSellPrice();
                int choice = command.chooseFromList(props);
                if (choice == 0) { gameSenceStack.pop_back(); break; }
				Prop* prop = backpack.GetPropFromIndex(choice);
				int price = prop->GetSellPrice();
                int count = command.ChooseCount(prop->GetNum());
                if (count == 0) { gameSenceStack.pop_back(); break; }
                money += price * count;
				backpack.ReduceProp(choice, count);
                Text info;
                info.Add("你卖出了"); 
                info.Add(prop->GetName(), GREEN); 
                info.Add("x"); 
                info.Add(to_string(count), YELLOW); 
                log.AddLog(info); 
                info.Print();
                command.Pause(); 
                gameSenceStack.pop_back(); 
                break;
			}
			case SELL_POKEMON:
			{
                vector<Text> pokemonNames = pokemonLib.GetPokemonSellPrice();
                int choice = command.chooseFromList(pokemonNames);
                if (choice == 0) { gameSenceStack.pop_back(); break; }
                Pokemon* pokemon = pokemonLib.GetPokemonInLib(choice);
                int price = pokemon->GetSellPrice();
                money += price;
                pokemonLib.DeletePokemon(pokemon);
                Text info;
                info.Add("你卖出了");
                info.Add(pokemon->name, GREEN);
                log.AddLog(info);
                info.Print();
                command.Pause();
                gameSenceStack.pop_back();
                break;
			}
			case COMBAT:
			{
				gameSenceStack.pop_back();
				break;
			}
			case DEBUG:
			{
				gameSenceStack.pop_back();
                break;
			}
			case WORLD_MAP:  
			{
				{
					command.Pause();
					gameSenceStack.pop_back();
				}
                break;
			}
		}
	}
}

void Game::Init()
{
	playerX = 1;
    playerY = 8;
	money = 0;
	inCombat = false;
	Map* map1= new Map(1);
	currentMap = map1;
	soundPlayer.PlayMusic(SoundPlayer::MUSIC_ZhenXinZhen);
}

void Game::Load()
{
}

void Game::Save()
{
}

void Game::ActOnMap()
{
	pair<int, int> pos = GetPos();
	int maxX = currentMap->getMapWidth();
    int maxY = currentMap->getMapHeight();
	for (int i = 0; i < maxY; i++)
	{
		for (int j = 0; j < maxX; j++)
		{
			Map::MapBlock  block = currentMap->getMapBlock(j,i); 
			Text(string(1, block.symbol), block.color).Print();
		}
        cout << endl; 
	}
	GotoXY(pos.first + playerX, pos.second + playerY);
	Text("@", MAGENTA).Print();
	while (true)
	{
		char cmd = command.GetCommand({ UP,DOWN,LEFT,RIGHT,ESC,OPEN_BACKPACK,POKEMON_LIST,OPEN_WORLD_MAP });
		if (cmd == ESC)
		{
			gameSenceStack.push_back(SETTING);
			break;
		}
		else if (cmd == OPEN_BACKPACK)
		{
			gameSenceStack.push_back(BACKPACK);
			break;
		}
        else if (cmd == POKEMON_LIST)
        {
            gameSenceStack.push_back(POKEMON_LIB);
            break;
        }
        else if (cmd == OPEN_WORLD_MAP)
        {
            gameSenceStack.push_back(WORLD_MAP);
            break;
        }
		else
		{
            int newX = playerX;
            int newY = playerY;
            switch (cmd)
            {
            case UP: if(newY>=0) newY--; break;
            case DOWN:if(newY<maxY) newY++; break;
            case LEFT:if(newX>=0) newX--; break; 
            case RIGHT:if(newX<maxX) newX++; break; 
            }
            Map::MapBlock block = currentMap->getMapBlock(newX, newY);
			Map::MapBlock blockOld = currentMap->getMapBlock(playerX, playerY);
			if (block.type == Map::EMPTY)
			{
				GotoXY(pos.first + playerX, pos.second + playerY);
                Text(string(1, blockOld.symbol), blockOld.color).Print();
                playerX = newX;
                playerY = newY;
                GotoXY(pos.first + playerX, pos.second + playerY);
                Text("@", MAGENTA).Print();
				soundPlayer.Play_Sound(SoundPlayer::SOUND_CHOOSE);
            }
            else if (block.type == Map::WALL)
            {
				//do nothing
			}
			else if (block.type == Map::GRASS)
			{
				GotoXY(pos.first + playerX, pos.second + playerY);
				Text(string(1, blockOld.symbol), blockOld.color).Print();
				playerX = newX;
				playerY = newY;
				GotoXY(pos.first + playerX, pos.second + playerY);
				Text("@", MAGENTA).Print();
			}
			else if (block.type == Map::EXIT)
			{

			}
			else if (block.type == Map::SHOP)
			{
				gameSenceStack.push_back(SHOP);
                break;
			}
			else if (block.type == Map::HOSPITAL)
			{

			}
			else if (block.type == Map::POKEMON_CENTER)
			{
				gameSenceStack.push_back(POKEMON_CENTER);
                break;
			}

		}
	}
}

void Game::UseProp(Prop* prop)
{
}

