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
		ChangeMusic();
		switch (gameSence)
		{
			case START_MENU:
			{
				vector<Text> Menu;
				Menu.push_back(Text("1. 开始新游戏"));
				Menu.push_back(Text("2. 加载游戏"));
				Menu.push_back(Text("3. 退出游戏"));
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
				Menu.push_back(Text("1. 保存游戏"));
				Menu.push_back(Text("2. 返回游戏"));
				Menu.push_back(Text("3. 开关音乐"));
				Menu.push_back(Text("4. 保存并退出"));
				Menu.push_back(Text("5. 返回菜单"));
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
					if (soundPlayer.forbidMusic)
					{
                        soundPlayer.forbidMusic = false;
                        Text("音乐已开启", GREEN, GRAY).Print();
                        log.AddLog(Text("音乐已开启!", GREEN));
						command.Pause();
					}
					else
					{
                        soundPlayer.forbidMusic = true;
                        Text("音乐已关闭", GREEN, GRAY).Print();
                        log.AddLog(Text("音乐已关闭!", GREEN));
                        command.Pause();
					}
				}
				else if (choice == 4)
				{
					Save();
					gameSenceStack.clear();
				}
				else if (choice == 5)
				{
					gameSenceStack.clear();
                    gameSenceStack.push_back(START_MENU);
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
					options.push_back(Text("1. 购买道具"));
					options.push_back(Text("2. 卖出道具"));
					options.push_back(Text("3. 卖出仓库中的宝可梦"));
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
				int choice = command.chooseFromList(props,10);
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
                int choice = command.chooseFromList(props,10);
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
                int choice = command.chooseFromList(pokemonNames,10);
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
				Text("Debug:\ninput cmd:", RED).Print();
				string input;
                cin >> input;
                if (input == "") { gameSenceStack.pop_back(); break; }
                if (input == "exit") { gameSenceStack.pop_back(); break; }
				else if (input == "music")
				{
                    Text("input music id:", RED).Print();
                    int id;
					do {
						cin >> id;
						if (cin.fail())
						{
							cin.clear();
							cin.ignore(1024, '\n');
						}
					} while (id< 0 || id > 20);
                    soundPlayer.PlayMusic((SoundPlayer::SoundID)id);
					command.Pause();
				}
				else if (input == "money")
				{
					Text("input money to set:", RED).Print();
                    int money;
                    do {
                        cin >> money;
                        if (cin.fail())
                        {
                            cin.clear();
                            cin.ignore(1024, '\n');
                        }
                    } while (money < 0);
                    this->money = money;
					Text("money set to:").Print();
                    Text(to_string(money), YELLOW).Print(); 
					log.AddLog(Text("你的金币数量已更改为: " + to_string(money), YELLOW));
                    command.Pause();
                }
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
	maps.push_back(map1);

	//TODO: 从NPC_Info.txt读取所有NPC信息,数量为NPCS_COUNT
	//使用 new 创建新的对象, 构造函数使用NPC(int id);
	//正常情况下,NPC的id与NPC_Info.txt中的行数对应(从1开始)

	soundPlayer.PlayMusic(SoundPlayer::MUSIC_ZhenXinZhen);
	log.clearLog();
	log.AddLog(Text("欢迎来到宝可梦世界！",GREEN));
}

void Game::Load()
{
    //TODO: 从Game_State.txt读取
    //读取内容在README.md中有详细说明
	// 注意处理空文件的情况

    //TODO: 从NPC_State.csv读取,并存入npcs
    //读取内容在README.md中有详细说明
	//读取每个npc时使用 new 创建新的对象, 构造函数使用NPC(string info);
    //注意处理空文件的情况

    backpack.Load(); 
    pokemonLib.Load(); 
}

void Game::Save()
{
	//TODO: 储存到Game_State.txt
	//储存内容在README.md中有详细说明

	//TODO: 储存到NPC_State.csv
	//NPC: vector<NPC*> npcs;
	//储存内容在README.md中有详细说明
	backpack.Save();
	pokemonLib.Save();
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
	pair<int, int> logPos = GetPos();
	log.ShowLog();
	GotoXY(pos.first + playerX, pos.second + playerY);
	Text("@", MAGENTA).Print();
    
	while (true)
	{
		char cmd = command.GetCommand({ UP,DOWN,LEFT,RIGHT,ESC,OPEN_BACKPACK,POKEMON_LIST,OPEN_WORLD_MAP,COMMAND});
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
		else if (cmd == COMMAND)
		{
            gameSenceStack.push_back(DEBUG);
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

void Game::ChangeMusic()
{
	SoundPlayer::SoundID BGM;
	if (currentMap == nullptr) return;
	int mapID = currentMap->getMapID();
	switch (mapID)
	{
    	case 1: BGM = SoundPlayer::MUSIC_ZhenXinZhen; break; 
    	case 2: BGM = SoundPlayer::MUSIC_ChangPanShi; break; 
    	case 3: BGM = SoundPlayer::MUSIC_ShenHuiShi; break; 
    	case 4: BGM = SoundPlayer::MUSIC_HuaTianShi; break; 
    	case 5: BGM = SoundPlayer::MUSIC_CaiHongShi; break; 
    	case 6: BGM = SoundPlayer::MUSIC_HongLianDao; break; 
    	case 7: BGM = SoundPlayer::MUSIC_ZiYuanZhen; break; 
    	case 8: BGM = SoundPlayer::MUSIC_HuangJinShi; break; 
    	case 9: BGM = SoundPlayer::MUSIC_QianHongShi; break; 
		default: BGM = SoundPlayer::MUSIC_YeWai; break;
	}
    soundPlayer.PlayMusic(BGM);
}

bool Game::ChangeNPCState(NPC* npc)
{
	//TODO:
	//尝试改变NPC状态，如果成功返回true
	/*
	NPC改变的逻辑如下:
	先获取NPC的当前状态npc.GetState()
	获取NPC的状态类型stateAction[0]
	根据NPC的状态类型,和对应的状态参数stateAction[1 ~ n]
    根据状态类型和对应参数判断是否可以改变NPC状态
	一共8种可能的改变方式,每一种需要调用不同的类和函数,在README.md中有详细说明
	如果不清楚其中的某一种应该如何判断,在对应位置写上"//CAN NOT FINISH" 注释,我会补全
	如果可以改变NPC状态,将npc的state改为stateNext.并且返回true(别忘了可能的移动npc的位置)
    否则返回false
	*/
	return false;
}

