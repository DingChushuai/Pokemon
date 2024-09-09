#include "Game.h"
#pragma once
#include <fstream>

Game::Game()
{
	//初始化状态栈和各个组件
	gameSenceStack.push_back(START_MENU);
    gameSence = START_MENU;
	playerX= 0;
    playerY= 0;
    money = 0;
    currentMap = nullptr;
	inCombat = false;
	pokemonNow = nullptr;
	HideCursor(); //隐藏光标
}

void Game::Run()
{
	//游戏主循环,根据状态栈来切换游戏场景
	while (gameSenceStack.empty() == false)
	{
		ClearScreen();	//切换场景时清屏
		gameSence = gameSenceStack.back();
		ChangeMusic();	//切换场景时切换音乐
		switch (gameSence)
		{
			case START_MENU:
			{
				//游戏开始菜单,选择开始新游戏,加载游戏或退出游戏
				DrawTitle();
				Text("操作提示: ws(ad)选择, ESC退出 (空格)确认\n").Print();
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
				//游戏主场景,玩家控制角色在地图上移动
				ActOnMap();
				break;
			}
			case SETTING:
			{
				//设置菜单,选择保存游戏,返回游戏,开关音乐,保存并退出,返回菜单
				Text("设置\n",GREEN).Print();
				Text("操作提示: ws(ad)选择, ESC退出 (空格)确认\n").Print();
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
				//查看宝可梦队伍
				{
					Text("\n你上阵中的宝可梦：\n").Print();
					Text("\n选择并查看宝可梦的详细信息, ESC退出\n", YELLOW, GRAY).Print();
					vector<Text> pokemonsInGame = pokemonLib.GetPokemonInGameInfo();
					if (pokemonsInGame.size() == 0)
					{
                        Text("\n你的队伍中没有宝可梦,请先获取一只宝可梦!\n", RED).Print();
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
				//从宝可梦队伍中选择一只宝可梦查看详细信息
				{
					command.PrintfList(pokemonNow->GetDetail());
					Text("按任意键返回").Print();
					command.Pause();
					gameSenceStack.pop_back();
				}
				break;
            }
			case BACKPACK:
			{
				{
					//查看背包,选择道具使用
					vector<Text> props = backpack.GetPropsInfo();
                    if (props.size() == 0)
                    {
                        Text("\n你的背包中没有道具,请先获取一些道具!\n", RED).Print();
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
				//宝可梦中心,选择宝可梦交换,宝可梦优先存入队伍,不会出现队伍不满6个而仓库有宝可梦的情况
				{
					vector<Text> pokemonsIngame = pokemonLib.GetPokemonInGameInfo();
					vector<Text> pokemonsInLib = pokemonLib.GetPokemonInLibInfo();
					if (pokemonsIngame.size() == 0)
					{
						Text("\n你的队伍中没有宝可梦,请先获取一只宝可梦!\n", RED, GRAY).Print();
                        command.Pause();
                        gameSenceStack.pop_back();
						break;
					}
					if (pokemonsInLib.size() == 0)
					{
						Text("\n你的仓库中没有宝可梦,请获取更多宝可梦后再来看看吧!\n", RED, GRAY).Print();
						command.Pause();
						gameSenceStack.pop_back();
						break;
					}
					for (int i = 0; i < pokemonsIngame.size(); i++)
					{
						pokemonsIngame[i].Print();
						cout << endl;
					}
					Text("\n选择一只库中的宝可梦交换或查看详细信息\n", YELLOW, GRAY).Print();
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
							log.AddLog(pokemonLib.SwitchPokemon(indexInLib, indexInGame));
						}
						else
						{
							log.AddLog(pokemonLib.AddPokemonToGame(indexInLib));
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
				//商店,购买道具
				Text("你的金币:"+to_string(money), YELLOW).Print();
				Text("商品列表:").Print();
				vector<Text> props = shop.GetPropsInShop();
				int choice = command.chooseFromList(props, 10);
				while (choice)
				{
					int price = shop.GetPriceOfProp(choice);
					if (money < price)
					{
						Text("\n你的金币不够了,请先去赚点金币吧!\n", RED).Print();
						command.Pause();
						break;
					}
					int maxCount = money / price;
					int count = command.ChooseCount(maxCount);
					if (count == 0) { gameSenceStack.pop_back(); break; }
					money -= price * count;
					Prop buyedProp = shop.BuyProp(choice, count);
					backpack.AddProp(new Prop(buyedProp));
					Text info;
					info.Add("你购买了");
					info.Add(buyedProp.GetName(), GREEN);
					info.Add("x");
					info.Add(to_string(count), YELLOW);
					info.Add("，花费了");
                    info.Add(to_string(price * count), YELLOW);
                    info.Add("金币");
					log.AddLog(info);
					info.Print();
					command.Pause();
					ClearScreen();
                    props = shop.GetPropsInShop();
				    if (props.size() == 0) { gameSenceStack.pop_back(); break; }
					choice = command.chooseFromList(props, 10);
				}
                gameSenceStack.pop_back();
                break;
			}
            case SELL_ITEM:
			{
				//商店,卖出道具
				vector<Text> props = backpack.GetPropsSellPrice();
				if (props.size() == 0)
				{
					Text("\n你的背包中没有道具,请先去获取一些道具吧!\n", RED).Print();
                    command.Pause();
                    gameSenceStack.pop_back();
                    break;
				}
                int choice = command.chooseFromList(props,10);
				while (choice)
				{
					Prop* prop = backpack.GetPropFromIndex(choice);
					int price = prop->GetSellPrice();
					int count = command.ChooseCount(prop->GetNum());
					if (count == 0) { gameSenceStack.pop_back(); break; }
					money += price * count;
					backpack.ReduceProp(prop,count);
					Text info;
					info.Add("你卖出了");
					info.Add(prop->GetName(), GREEN);
					info.Add("x");
					info.Add(to_string(count), YELLOW);
                    info.Add("，获得了");
                    info.Add(to_string(price * count), YELLOW);
                    info.Add("金币");
					log.AddLog(info);
					info.Print();
					command.Pause();
					ClearScreen();
                    props = backpack.GetPropsSellPrice();
                    if (props.size() == 0) { gameSenceStack.pop_back(); break; }
					choice = command.chooseFromList(props, 10);
				}
                gameSenceStack.pop_back(); 
                break;
			}
			case SELL_POKEMON:
			{
				//商店,卖出宝可梦
                vector<Text> pokemonNames = pokemonLib.GetPokemonSellPrice();
				if (pokemonNames.size() == 0)
				{
                    Text("\n你的仓库中没有宝可梦,请先去抓一些宝可梦吧!\n", RED).Print();
                    command.Pause();
                    gameSenceStack.pop_back();
                    break;
				}
                int choice = command.chooseFromList(pokemonNames,10);
                while (choice)
				{
					Pokemon* pokemon = pokemonLib.GetPokemonInLib(choice);
					int price = pokemon->GetSellPrice();
					money += price;
					pokemonLib.DeletePokemon(pokemon);
					Text info;
					info.Add("你卖出了");
					info.Add(pokemon->name, GREEN);
                    info.Add("，获得了");
                    info.Add(to_string(price), YELLOW);
                    info.Add("金币");
					log.AddLog(info);
					info.Print();
					command.Pause();
					ClearScreen();
					pokemonNames = pokemonLib.GetPokemonSellPrice();
					if (pokemonNames.size() == 0) { gameSenceStack.pop_back(); break; }
					choice = command.chooseFromList(pokemonNames, 10);
                }
                gameSenceStack.pop_back();
                break;
			}
			case COMBAT:
			{
				//触发与野生宝可梦的战斗
				if (pokemonLib.pokemonInGame.size() == 0 || combat.pokemonAvailable().size() == 0)
				{
					log.AddLog(Text("你没有可以战斗的宝可梦了,无法触发战斗!", RED));
					gameSenceStack.pop_back();
					break;
				}
				StartCombat();
				combat.EndCombat();
				//判断升级
				for (auto& pokemon : pokemonLib.pokemonInGame)
				{
					if (pokemon->CanLevelUp())
					{
						log.AddLog(pokemon->LevelUp());
					}
				}
				gameSenceStack.pop_back();
				break;
			}
			case DEBUG:
			{
				//debug指令
				Text("指令表:\n").Print();
				Text("金币(m):设置金币数量\n").Print();
				Text("升级(l): 给所有宝可梦升一级\n").Print();
				Text("退出(e): 退出debug\n").Print();
				Text("Debug:\n输入指令:", RED).Print();
				string input;
                cin >> input;
                if (input == "exit"  || input == "e") { gameSenceStack.pop_back(); break; }
				
				else if (input == "money" || input == "m") 
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
				else if (input == "levelup" || input == "l")
				{
					for (auto& pokemon : pokemonLib.pokemonInGame)
					{
						pokemon->GetExperience(pokemon->experienceToNextLevel);
						log.AddLog(Text("你的宝可梦" +pokemon->name + "获得了" + to_string(pokemon->experienceToNextLevel) + "经验")); 
						log.AddLog(pokemon->LevelUp());
					}
				}
                break;
			}
			case WORLD_MAP:  
			{
				//世界地图
				{
                    Text("这里是世界地图:\n", GREEN).Print();
                    DrawWorldMap();
					Text("按任意键返回游戏").Print();
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
	//初始化新游戏
	playerX = 35;
    playerY = 4;
	money = 2000;
	inCombat = false;
	Map* map0= new Map(0);
	currentMap = map0;
	maps.push_back(map0);
	pokemonLib.pokemonInGame.clear();
    pokemonLib.pokemonInLib.clear();
    npcs.clear();
	for (int i = 1; i <= NPCS_COUNT; i++)
	{
		NPC* npc = new NPC(i);
		npcs.push_back(npc);
	}
	soundPlayer.PlayMusic(SoundPlayer::MUSIC_ZhenXinZhen);
	log.clearLog();
	log.AddLog(Text("欢迎来到宝可梦世界！请使用全屏游玩.\n"
		"\n这里有着大量神奇的精灵宝可梦等待着你去探索和发现，在探索的途中，你会遇到许多人物，他们对你或是指引或是挑战(温馨提示:1个npc可能不止一次对话哦）,请开始你的宝可梦之旅吧!",GREEN));
}

void Game::Load()
{
	//载入游戏
	ifstream game_state;
	game_state.open(GAME_STATE_PATH);
	bool hasData = false;
	if (game_state.is_open())
	{
        string line;
		getline(game_state, line);
		if (line != "")
		{
			vector<string> data = Split(line, ',');
            playerX = stoi(data[0]);
            playerY = stoi(data[1]);
            Map* loadmap = new Map(stoi(data[2]));
            currentMap = loadmap;
            maps.push_back(loadmap);
            money = stoi(data[3]);
            hasData = true;
		}
		else
		{
			hasData = false;
		}
		if (hasData)
		{
            log.AddLog(Text("成功载入游戏", GREEN));
		}
	}
	game_state.close();
	if (!hasData)
	{
		Text("没有找到存档，将创建新存档", RED).Print();
		command.Pause();
		Init();
		return;
	}
	npcs.clear();
    ifstream npc_state;
    npc_state.open(NPC_STATE_PATH);
	if (npc_state.is_open())
	{
		for (int i = 0; i < NPCS_COUNT; i++)
		{
			string line;
			getline(npc_state, line);
			vector<string> data = Split(line, ',');
			NPC* npc = new NPC(stoi(data[0]));
			npc->state = stoi(data[1]);
			npc->mapID = stoi(data[2]);
			npc->x = stoi(data[3]);
			npc->y = stoi(data[4]);
			npcs.push_back(npc);
		}
	}
    backpack.Load(); 
    pokemonLib.Load(); 
}

void Game::Save()
{
	//保存游戏
	ofstream game_state;
    game_state.open(GAME_STATE_PATH);
    if (game_state.is_open())
    {
        game_state << playerX << "," << playerY << "," << currentMap->getMapID() << "," << money << endl;
    }
    game_state.close();
	ofstream npc_state;
    npc_state.open(NPC_STATE_PATH);
	if (npc_state.is_open())
	{
		for (auto npc : npcs)
		{
            npc_state << npc->ID << "," << npc->state << "," << npc->mapID << "," << npc->x << "," << npc->y << endl;
		}
	}
	backpack.Save();
	pokemonLib.Save();
}

void Game::DrawTitle()
{
	ifstream gamebar(GAMEBAR_PATH);
	if (gamebar.is_open())
	{
		string line;
		while (getline(gamebar, line))
		{
			Text(line, YELLOW).Print();
			cout << endl;
		}
	}
}

void Game::DrawWorldMap()
{
	ifstream worldMap(WORLD_MAP_PATH); 
	if (worldMap.is_open()) 
	{
		string line;
		while (getline(worldMap, line)) 
		{
			Text(line, YELLOW).Print(); 
			cout << endl;
		}
	}
}

void Game::ActOnMap()
{
	//在地图上行动的逻辑
	Text("这里是: " + currentMap->getMapName(), GREEN).Print();
	Text("\n拥有金币： " + to_string(money), YELLOW).Print();
	Text("\n操作提示: wasd:上左下右移动,e:打开背包,f:查看宝可梦,ESC:进入设置,m:查看地图,'/':进入修改器(debug时用) ").Print();
	cout << endl; 
	int maxX = currentMap->getMapWidth();
    int maxY = currentMap->getMapHeight();
	//遍历npc并选出在当前地图上的npc,显示尾号对应的npc名称
	for (auto npc : npcs)
	{
		if (npc->mapID == currentMap->getMapID())
		{
			Text(to_string(npc->ID % 10) +" : "+npc->name+"\t", GREEN).Print();
		}
	}
	cout << endl;
	command.PrintfList(currentMap->getTexts());	//打印地图说明
	cout << endl;
	pair<int, int> pos = GetPos();
	//打印地图
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
	//打印npc,使用尾号代替显示
	for (auto npc : npcs)
	{
		if (npc->mapID == currentMap->getMapID())
		{
			GotoXY(pos.first + npc->x, pos.second + npc->y);
            Text(to_string(npc->ID%10), GREEN).Print();
		}
	}
	GotoXY(pos.first + playerX, pos.second + playerY);
	Text("@", MAGENTA).Print();	//打印玩家
	
	while (true)
	{
		//获取指令
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
			//移动玩家
            int newX = playerX;
            int newY = playerY;
			//获取新的坐标
            switch (cmd)
            {
            case UP: if(newY>0) newY--; break;
            case DOWN:if(newY<maxY-1) newY++; break;
            case LEFT:if(newX>0) newX--; break; 
            case RIGHT:if(newX<maxX-1) newX++; break; 
            }
            Map::MapBlock block = currentMap->getMapBlock(newX, newY);
			Map::MapBlock blockOld = currentMap->getMapBlock(playerX, playerY);
			//优先判断是否是npc
			bool isNPC = false;
			for (auto npc : npcs)
			{
				if (npc->mapID == currentMap->getMapID())
				{
					if (npc->x == newX && npc->y == newY)
					{
						isNPC = true;
						if (ChangeNPCState(npc))	//尝试改变npc状态,并显示成功/失败的对话
						{
							Text info;
							info.Add(npc->name, GREEN);
                            info.Add(" : ");
                            info.Add(npc->GetTalk(), YELLOW);
							log.AddLog(info);
							npc->state = npc->GetState().stateNext;
						}
						else
						{
							Text info; 
							info.Add(npc->name, GREEN); 
							info.Add(" : "); 
							info.Add(npc->GetNotFinishTalk(), YELLOW);
							log.AddLog(info);
						}
						break;
					}
				}
			}
            if (isNPC) break;
			//依次判断新位置的坐标类型
			if (block.type == Map::EMPTY)
			{
				//只更改两个位置显示的内容
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
				//草丛,随机遇到野生宝可梦
				GotoXY(pos.first + playerX, pos.second + playerY);
				Text(string(1, blockOld.symbol), blockOld.color).Print();
				playerX = newX;
				playerY = newY;
				GotoXY(pos.first + playerX, pos.second + playerY);
				Text("@", MAGENTA).Print();
				vector<vector<int>> wilds = currentMap->getWildPokemon();
				int wild_index = -1;
				//依次判断是否遇到野生宝可梦
				for (int i = 0; i < wilds.size(); i++)
				{
					if (rand() % wilds[i][2] == 0)
					{
                        wild_index = i;
                        break;
					}
				}
				if (wild_index != -1)
				{
					if (pokemonLib.pokemonInGame.size() > 0)
					{
						combat.InitWildCombat(wilds[wild_index][0], wilds[wild_index][1], &pokemonLib);	//初始化战斗
						gameSenceStack.push_back(COMBAT);
					}
                    break;
				}
			}
			else if (block.type == Map::EXIT)
			{
				//切换地图
				Text info;
                info.Add("你离开了");
                info.Add(currentMap->getMapName(), YELLOW);
                info.Add("来到了");
                //获取出口信息
				vector<int> newMap = currentMap->getExit(newX, newY);
				if (newMap.size() == 0)
				{
					break;
				}
				//判断是否已经存在该地图
				for (auto map : maps)
				{
					if (map->getMapID() == newMap[0])
					{
                        currentMap = map;
						info.Add(currentMap->getMapName(), YELLOW);
                        log.AddLog(info);
                        playerX = newMap[1];
                        playerY = newMap[2];
                        break;
					}
				}
				//如果不存在,则创建新的地图
				if (currentMap->getMapID() != newMap[0])
				{
                    currentMap = new Map(newMap[0]);
					info.Add(currentMap->getMapName(), YELLOW);
                    log.AddLog(info);
                    maps.push_back(currentMap);
                    playerX = newMap[1];
                    playerY = newMap[2];
				}
				break;
			}
			else if (block.type == Map::SHOP)
			{
				gameSenceStack.push_back(SHOP);
                break;
			}
			else if (block.type == Map::HOSPITAL)
			{
				//宝可梦医院,恢复所有宝可梦的HP和PP
				for (auto poke : pokemonLib.pokemonInGame)
				{
                    poke->attribute.hp = poke->attribute.maxHp;
					poke->statu = Pokemon::PokemonStatu::None;
					for (int i = 0; i < poke->skills.size(); i++)
					{
                        poke->skills[i].PP = poke->skills[i].maxPP;
					}
				}
                log.AddLog(Text("你的宝可梦已恢复到最佳状态!",GREEN));
                break;
			}
			else if (block.type == Map::POKEMON_CENTER)
			{
				gameSenceStack.push_back(POKEMON_CENTER);
                break;
			}
		}
	}
}

bool Game::UseProp(Prop* prop)
{
	//根据道具类型和使用场景使用道具
	//道具类型信息参考README.md
	switch (prop->GetType())
	{
        case 0:
		{
            return false;
		}
        case 1:
		{
			//消除状态
			if (inCombat)
			{
				vector<Pokemon*> pokes = combat.myPokemons;
				vector<Text> pokemonInfo;
				for (auto poke : pokes)
				{
					pokemonInfo.push_back(Text(poke->name + to_string(poke->attribute.hp) + "/" + to_string(poke->attribute.maxHp) + " HP" + poke->GetStatuName(poke->statu)));
				}
				int index;
				do {
					index = command.chooseFromList(pokemonInfo);
				} while (index == 0);
				Pokemon* poke = pokes[index - 1];
				vector<int> param = prop->GetEffectPara();
				if (poke->statu == param[0]|| param[0] == 0)
				{
					poke->statu = (Pokemon::PokemonStatu)0;
					Text info;
                    info.Add("宝可梦");
                    info.Add(poke->name, YELLOW);
                    info.Add("的状态恢复正常了");
					combat.combatLog.AddLog(info);
					return true;
				}
				else
				{
                    Text info;
                    info.Add("宝可梦");
                    info.Add(poke->name, YELLOW);
                    info.Add("的状态无法被");
                    info.Add(prop->GetName(), YELLOW);
                    info.Add("消除");
                    combat.combatLog.AddLog(info);
					return false;
				}
			}
			else
			{
				vector<Pokemon*> pokes = pokemonLib.pokemonInGame;
                vector<Text> pokemonInfo;
				for (auto poke : pokes)
				{
					 pokemonInfo.push_back(Text(poke->name + to_string(poke->attribute.hp) + "/" + to_string(poke->attribute.maxHp) + " HP" + poke->GetStatuName(poke->statu)));
				}
                int index;
                do {
                index = command.chooseFromList(pokemonInfo);
				} while (index == 0);
                Pokemon* poke = pokes[index - 1];
                vector<int> param = prop->GetEffectPara();
				if (poke->statu == param[0] || param[0] == 0)
				{
					poke->statu = (Pokemon::PokemonStatu)0;
					Text info;
					info.Add("宝可梦");
					info.Add(poke->name, YELLOW);
					info.Add("的状态恢复正常了");
					log.AddLog(info);
                    return true;
				}
			}
            break;
		}
        case 2:
		{
			//提升基础点数
			vector<Pokemon*> pokes;
            pokes = pokemonLib.pokemonInGame;
			vector<Text> pokemonInfo;
			for (auto poke : pokes)
			{
				 pokemonInfo.push_back(Text(poke->name + to_string(poke->attribute.hp) + "/" + to_string(poke->attribute.maxHp) + " HP" + poke->GetStatuName(poke->statu)));
			}
            int index;
            do {
            index = command.chooseFromList(pokemonInfo);
            } while (index == 0);
            Pokemon* poke = pokes[index - 1];
            vector<int> param = prop->GetEffectPara();
			for (int i = 0; i < param.size(); i += 2)
			{
				switch (param[i])
				{
					case 0: poke->basicValue.hp += param[i + 1]; break;
                    case 1: poke->basicValue.attack += param[i + 1]; break;
                    case 2: poke->basicValue.defense += param[i + 1]; break;
                    case 3: poke->basicValue.speed += param[i + 1]; break;
                    case 4: poke->basicValue.specialAttack += param[i + 1]; break;
                    case 5: poke->basicValue.specialDefense += param[i + 1]; break;
				}
			}
            Text info;
            info.Add("宝可梦");
            info.Add(poke->name, YELLOW);
            info.Add("的属性提升了");
            log.AddLog(info);
            return true;
        	break;
		}
        case 3:
		{
			//提升技能效果
			vector<Pokemon*> pokes;
			if (inCombat) pokes = combat.myPokemons;
			else pokes = pokemonLib.pokemonInGame;
			vector<Text> pokemonInfo;
			for (auto poke : pokes)
			{
				Text skillInfo;
				skillInfo.Add(poke->name + "   ");
				for (auto skill : poke->skills)
				{
					skillInfo.Add(skill.skillName + " " + to_string(skill.PP) + "/" + to_string(skill.maxPP) + " PP");
				}
				pokemonInfo.push_back(skillInfo);
			}
			int index;
			do {
				index = command.chooseFromList(pokemonInfo);
			} while (index == 0);
			Pokemon* poke = pokes[index - 1];
			vector<Text> skillInfo;
			for (auto skill : poke->skills)
			{
				skillInfo.push_back(Text(skill.skillName + " " + to_string(skill.PP) + "/" + to_string(skill.maxPP) + " PP"));
			}
			int skillIndex;
			do {
				skillIndex = command.chooseFromList(skillInfo);
			} while (skillIndex == 0);
			Skill* skill = &poke->skills[skillIndex - 1];
			vector<int> param = prop->GetEffectPara();
			if (param[0]==1)
			{
                if (param[1] != skill->skillType) return false;
			}
			if (param[0] == 2)
			{
                if (param[1] != skill->type) return false;
			}
			for (int i = 2; i < param.size(); i += 2)
			{
				switch (param[i])
				{
					case 1:skill->power += param[i + 1]; break;
                    case 2:skill->accuracy += param[i + 1]; break;
                    case 3:skill->PP += param[i + 1]; break;
                    case 4:skill->maxPP += param[i + 1]; break;
				}
			}
            Text info;
            info.Add("技能");
            info.Add(skill->skillName, YELLOW);
            info.Add("的属性提升了");
			if (inCombat) combat.combatLog.AddLog(info);
            else log.AddLog(info);
            return true;
		}
        case 4:
		{
			//提升战斗属性
			Pokemon* poke = combat.pokemonNow;
            vector<int> param = prop->GetEffectPara();
			for (int i = 0; i < param.size(); i += 2)
			{
				switch (param[i])
				{
				case 1:poke->buff.attack += param[i + 1];if (poke->buff.attack > 6) poke->buff.attack = 6; break;
                case 2:poke->buff.defense += param[i + 1]; if (poke->buff.defense > 6) poke->buff.defense = 6; break;
                case 3:poke->buff.speed += param[i + 1]; if (poke->buff.speed > 6) poke->buff.speed = 6; break;
                case 4:poke->buff.specialAttack += param[i + 1]; if (poke->buff.specialAttack > 6) poke->buff .specialAttack = 6; break;
	            case 5:poke->buff.specialDefense += param[i + 1]; if (poke->buff.specialDefense > 6) poke->buff.specialDefense = 6; break;
				case 6:poke->buff.accuracy += param[i + 1]; if (poke->buff.accuracy > 6) poke->buff.accuracy = 6; break;
                case 7:poke->buff.evasion += param[i + 1]; if (poke->buff.evasion > 6) poke->buff.evasion = 6; break;
				}
			}
			Text info;
            info.Add("宝可梦");
            info.Add(poke->name, YELLOW);
            info.Add("的战斗属性提升了!");
            log.AddLog(info);
            return true;
            break;
		}
		case 5:
		{
			//恢复宝可梦血量
			Pokemon* poke;
			if(inCombat)
				poke = combat.pokemonNow;
			else
			{
                vector<Pokemon*> pokes = pokemonLib.pokemonInGame;
                int index;
				Text("选择一个宝可梦使用道具:\n").Print();
                do {
                    index = command.chooseFromList(pokemonLib.GetPokemonInGameInfo());
                } while (index == 0);
                poke = pokes[index - 1];
            }
            vector<int> param = prop->GetEffectPara();
			//回复体力(濒死时是否可用,回复方式(0按百分比,1按具体值),百分比/具体值)
			if (param[0] == 0)
			{
				if (poke->attribute.hp == 0)
				{
					if(inCombat) combat.combatLog.AddLog(Text("宝可梦濒死,不能使用回复道具!", RED));
                    else log.AddLog(Text("宝可梦濒死,不能使用回复道具!", RED));
                    return false;
				}
			}
			if (param[1] == 0)
			{
                poke->attribute.hp += poke->attribute.maxHp * param[2] / 100;
			}
			else
			{
				poke->attribute.hp += param[2];
			}
            if (poke->attribute.hp > poke->attribute.maxHp) poke->attribute.hp = poke->attribute.maxHp;
			if(inCombat) combat.combatLog.AddLog(Text("宝可梦体力回复成功!当前生命:" + to_string(poke->attribute.hp) + " / " + to_string(poke->attribute.maxHp), GREEN));
            else log.AddLog(Text("宝可梦体力回复成功!当前生命:" + to_string(poke->attribute.hp) + " / " + to_string(poke->attribute.maxHp), GREEN));
			soundPlayer.Play_Sound(SoundPlayer::SOUND_HEAL);
			return true;
		}
		case 7:
		{
			//捕捉宝可梦
			Pokemon* poke = combat.enemyNow;
			if (combat.IsTrainerBattle())
			{
				combat.combatLog.AddLog(Text("不能捕捉训练家的宝可梦!", RED));
                break;
			}
			float C = poke->GetCaptureRate();
			float D = 1.0;
			vector<int> param = prop->GetEffectPara();
			D *= param[0];
			float E = 1.0;
			if(poke->statu == Pokemon::Sleep || poke->statu == Pokemon::Freeze) E *= 2;
            if (poke->statu == Pokemon::Burn || poke->statu == Pokemon::Paralysis || poke->statu == Pokemon::Poison) E *= 1.5;
			int B = (poke->attribute.maxHp * 3 - 2 * poke->attribute.hp) * C / poke->attribute.maxHp * 3 * D * E;
            if (B > 255) B = 255;
			bool success = rand() % 256 < B;
			if (success)
			{
                Text info;
                info.Add("你使用");
                info.Add(prop->GetName(), YELLOW);
                info.Add("成功捕捉了");
                info.Add(poke->name, YELLOW);
                info.Add("!");
                log.AddLog(info);
                combat.combatLog.AddLog(info);
				pokemonLib.AddPokemon(new Pokemon(*poke));
				poke->attribute.hp= 0;
			}
			else
			{
                Text info;
                info.Add("你使用");
                info.Add(prop->GetName(), YELLOW);
                info.Add("失败了!");
                combat.combatLog.AddLog(info);
			}
			backpack.ReduceProp(prop);
            break;
		}
	}
}

void Game::UseSkill(Skill* skill, Pokemon* user,Pokemon* target)
{
	//根据技能类型进行攻击
	//技能类型信息详见README.md
    if (user->attribute.hp <= 0) return;
	Type type = skill->type;
	Type type1, type2;
	type1 = target->type.first;
	type2 = target->type.second;
	float typeEffect = 1.0;
	if (type1 != Type::NONE) typeEffect *= combat.damageTable[type][type1];
    if (type2 != Type::NONE) typeEffect *= combat.damageTable[type][type2];
	if (typeEffect == 0.0)
	{
		Text info;
        info.Add(user->name, GREEN);
        info.Add("的技能");
        info.Add(skill->skillName, YELLOW);
        info.Add("对");
        info.Add(target->name, GREEN);
        info.Add("没有效果!");
		combat.combatLog.AddLog(info);
        return;
	}
	float damage = 0.0;
	if(skill->skillType ==Skill::PHYSICAL)
	damage = (2 * user->level + 10) * user->attribute.attack *user->GetBuffValue(user->buff.attack) * skill->power / (250 * target->attribute.defense * target->GetBuffValue(target->buff.defense)) + 2;
    else if (skill->skillType == Skill::SPECIAL)
    damage = (2 * user->level + 10) * user->attribute.specialAttack * user->GetBuffValue(user->buff.specialAttack) * skill->power / (250 * target->attribute.specialDefense * target->GetBuffValue(target->buff.specialDefense)) + 2;
    damage *= typeEffect;
	if (damage < 1.0) damage = 1.0;
	int randHitMusic = rand() % 3;	//随机播放攻击音效
	switch (randHitMusic)
	{
		case 0:soundPlayer.Play_Sound(SoundPlayer::SOUND_HIT_1);
        	break;
        case 1:soundPlayer.Play_Sound(SoundPlayer::SOUND_HIT_2);
            break;
        case 2:soundPlayer.Play_Sound(SoundPlayer::SOUND_HIT_3);
            break;
	}
	Text info;
	switch (skill->skillEffect)
	{
	case 0:
		info.Add(user->name, GREEN);
		info.Add("使用了技能");
		info.Add(skill->skillName, YELLOW);
		info.Add("对");
		info.Add(target->name, GREEN);
		info.Add("造成了");
		info.Add(to_string((int)damage), RED);
		info.Add("点伤害!");
		if (typeEffect == 2.0) info.Add(" 效果拔群!");
		else if (typeEffect == 1.0) info.Add(" 效果一般!");
		else if (typeEffect == 0.5) info.Add(" 效果不好!");
		else if (typeEffect == 0.25) info.Add(" 效果极差!");
		combat.combatLog.AddLog(info);
		target->attribute.hp -= (int)damage;
		if (target->attribute.hp <= 0) target->attribute.hp = 0;
        return;
	case 1:
	{
		int min = skill->effectParam[0], max = skill->effectParam[1];
		int random = rand() % (max - min + 1) + min;
		info.Add(user->name, GREEN);
		info.Add("使用了技能");
		info.Add(skill->skillName, YELLOW);
		info.Add("对");
		info.Add(target->name, GREEN);
		info.Add("造成了");
		info.Add(to_string(random), RED);
		info.Add("次攻击,共造成了");
		info.Add(to_string(random * damage), RED);
		info.Add("点伤害!");
		combat.combatLog.AddLog(info);
		target->attribute.hp -= (int)(random * damage);
		if (target->attribute.hp <= 0) target->attribute.hp = 0;
		return;
	}
    case 2:
	{
		info.Add(user->name, GREEN);
		info.Add("使用了技能");
		info.Add(skill->skillName, YELLOW);
		info.Add("对");
		info.Add(target->name, GREEN);
		info.Add("造成了");
		info.Add(to_string((int)damage), RED);
		info.Add("点伤害!");
		if (typeEffect == 2.0) info.Add(" 效果拔群!");
		else if (typeEffect == 1.0) info.Add(" 效果一般!");
		else if (typeEffect == 0.5) info.Add(" 效果不好!");
		else if (typeEffect == 0.25) info.Add(" 效果极差!");
		for (int i = 0; i < skill->effectParam.size(); i+=2)
		{
			int statuID = skill->effectParam[i];
			int chance = skill->effectParam[i + 1];
			if (rand() % 100 < chance)
			{
				target->statu = (Pokemon::PokemonStatu)statuID;
				info.Add("并且");
				info.Add(target->name, GREEN);
				info.Add("受到了");
				info.Add(target->GetStatuName(target->statu), RED);
				info.Add("状态!");
				break;
			}
		}
        combat.combatLog.AddLog(info);
        target->attribute.hp -= (int)damage;
        if (target->attribute.hp <= 0) target->attribute.hp = 0;
        return;
	}
    case 3:
	{
		info.Add(user->name, GREEN);
		info.Add("使用了技能");
		info.Add(skill->skillName, YELLOW);
		info.Add("对");
		info.Add(target->name, GREEN);
		info.Add("造成了");
		info.Add(to_string((int)damage), RED);
		info.Add("点伤害!");
		if (typeEffect == 2.0) info.Add(" 效果拔群!");
		else if (typeEffect == 1.0) info.Add(" 效果一般!");
		else if (typeEffect == 0.5) info.Add(" 效果不好!");
		else if (typeEffect == 0.25) info.Add(" 效果极差!");
		for (int i = 0; i < skill->effectParam.size(); i += 3)
		{
			int buffID = skill->effectParam[i];
            int changeWay = skill->effectParam[i + 1];
			int value = skill->effectParam[i + 2];
			if (changeWay == 1)
			{
				switch (buffID)
				{
                    case 1: user->buff.attack += value; break;
                    case 2: user->buff.defense += value; break;
                    case 3: user->buff.speed += value; break;
                    case 4: user->buff.specialAttack += value; break;
                    case 5: user->buff.specialDefense += value; break;
                    case 6: user->buff.accuracy += value; break;
                    case 7: user->buff.evasion += value; break;
				}
			}
			else if (changeWay == 2)
			{
				switch (buffID)
				{
                    case 1: user->buff.attack = value; break;
                    case 2: user->buff.defense = value; break;
                    case 3: user->buff.speed = value; break;
                    case 4: user->buff.specialAttack = value; break;
                    case 5: user->buff.specialDefense = value; break;
                    case 6: user->buff.accuracy = value; break;
                    case 7: user->buff.evasion = value; break;
				}
			}
		}
		info.Add(user->name, GREEN);
        info.Add("的战斗属性发生了改变!");
        combat.combatLog.AddLog(info);
        target->attribute.hp -= (int)damage;
        if (target->attribute.hp <= 0) target->attribute.hp = 0;
        return;
	}
    case 4:
	{
		info.Add(user->name, GREEN);
		info.Add("使用了技能");
		info.Add(skill->skillName, YELLOW);
		info.Add("对");
		info.Add(target->name, GREEN);
		info.Add("造成了");
		info.Add(to_string((int)damage), RED);
		info.Add("点伤害!");
		if (typeEffect == 2.0) info.Add(" 效果拔群!");
		else if (typeEffect == 1.0) info.Add(" 效果一般!");
		else if (typeEffect == 0.5) info.Add(" 效果不好!");
		else if (typeEffect == 0.25) info.Add(" 效果极差!");
		for (int i = 0; i < skill->effectParam.size(); i += 3)
		{
			int buffID = skill->effectParam[i];
			int changeWay = skill->effectParam[i + 1];
			int value = skill->effectParam[i + 2];
			if (changeWay == 1)
			{
				switch (buffID)
				{
				case 1: target->buff.attack += value; break;
				case 2: target->buff.defense += value; break;
				case 3: target->buff.speed += value; break;
				case 4: target->buff.specialAttack += value; break;
				case 5: target->buff.specialDefense += value; break;
				case 6: target->buff.accuracy += value; break;
				case 7: target->buff.evasion += value; break;
				}
			}
			else if (changeWay == 2)
			{
				switch (buffID)
				{
				case 1: target->buff.attack = value; break;
				case 2: target->buff.defense = value; break;
				case 3: target->buff.speed = value; break;
				case 4: target->buff.specialAttack = value; break;
				case 5: target->buff.specialDefense = value; break;
				case 6: target->buff.accuracy = value; break;
				case 7: target->buff.evasion = value; break;
				}
			}
		}
		info.Add(target->name, GREEN);
		info.Add("的战斗属性发生了改变!");
		combat.combatLog.AddLog(info);
		target->attribute.hp -= (int)damage;
		if (target->attribute.hp <= 0) target->attribute.hp = 0;
		return;
	}
    case 5:
	{
		for (int i = 0; i < skill->effectParam.size(); i += 3)
		{
			int buffID = skill->effectParam[i];
			int changeWay = skill->effectParam[i + 1];
			int value = skill->effectParam[i + 2];
			if (changeWay == 1)
			{
				switch (buffID)
				{
				case 1: user->buff.attack += value; break;
				case 2: user->buff.defense += value; break;
				case 3: user->buff.speed += value; break;
				case 4: user->buff.specialAttack += value; break;
				case 5: user->buff.specialDefense += value; break;
				case 6: user->buff.accuracy += value; break;
				case 7: user->buff.evasion += value; break;
				}
			}
			else if (changeWay == 2)
			{
				switch (buffID)
				{
				case 1: user->buff.attack = value; break;
				case 2: user->buff.defense = value; break;
				case 3: user->buff.speed = value; break;
				case 4: user->buff.specialAttack = value; break;
				case 5: user->buff.specialDefense = value; break;
				case 6: user->buff.accuracy = value; break;
				case 7: user->buff.evasion = value; break;
				}
			}
		}
		info.Add(user->name, GREEN);
		info.Add("使用技能");
        info.Add(skill->skillName, GREEN);
        info.Add("!使");
		info.Add(user->name, GREEN);
		info.Add("的战斗属性发生了改变!");
		combat.combatLog.AddLog(info);
        return;
	}
	case 6:
	{
		for (int i = 0; i < skill->effectParam.size(); i += 3)
		{
			int buffID = skill->effectParam[i];
			int changeWay = skill->effectParam[i + 1];
			int value = skill->effectParam[i + 2];
			if (changeWay == 1)
			{
				switch (buffID)
				{
				case 1: target->buff.attack += value; break;
				case 2: target->buff.defense += value; break;
				case 3: target->buff.speed += value; break;
				case 4: target->buff.specialAttack += value; break;
				case 5: target->buff.specialDefense += value; break;
				case 6: target->buff.accuracy += value; break;
				case 7: target->buff.evasion += value; break;
				}
			}
			else if (changeWay == 2)
			{
				switch (buffID)
				{
				case 1: target->buff.attack = value; break;
				case 2: target->buff.defense = value; break;
				case 3: target->buff.speed = value; break;
				case 4: target->buff.specialAttack = value; break;
				case 5: target->buff.specialDefense = value; break;
				case 6: target->buff.accuracy = value; break;
				case 7: target->buff.evasion = value; break;
				}
			}
		}
		info.Add(user->name, GREEN);
		info.Add("使用技能");
		info.Add(skill->skillName, GREEN);
		info.Add("!使");
		info.Add(target->name, GREEN);
		info.Add("的战斗属性发生了改变!");
		combat.combatLog.AddLog(info);
        return;
	}
    case 7:
	{
		for (int i = 0; i < skill->effectParam.size(); i += 2)
		{
			int statuID = skill->effectParam[i];
			int chance = skill->effectParam[i + 1];
			if (rand() % 100 < chance)
			{
				info.Add(user->name, GREEN);
                info.Add("使用技能");
                info.Add(skill->skillName, GREEN);
                info.Add("!使");
				target->statu = (Pokemon::PokemonStatu)statuID;
				info.Add(target->name, GREEN);
				info.Add("受到了");
				info.Add(target->GetStatuName(target->statu), RED);
				info.Add("状态!");
				break;
			}
		}
		combat.combatLog.AddLog(info);
		return;
	}
	}
}

void Game::ChangeMusic()
{
	//根据地图改变背景音乐
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
	//根据NPC状态改变NPC状态
	State state = npc->GetState();
	switch (state.stateAction[0])
	{
		case 0: 
		{
			return true;
		}
        case 1:
		{
			npc->mapID = state.stateAction[1];
			npc->x = state.stateAction[2];
            npc->y = state.stateAction[3];
            return true;
		}
		case 2 :
		{
			if (pokemonLib.pokemonInGame.size() == 0)
			{
				log.AddLog(Text("你没有可以战斗的宝可梦了,无法触发战斗!", RED));
				break;
			}
			ClearScreen();
			combat.InitTrainerCombat(state.stateAction[1], &pokemonLib);
			StartCombat();
			combat.EndCombat();
			combat.combatLog.ShowLog();
			command.Pause();
			for (auto& pokemon : pokemonLib.pokemonInGame)
			{
				if (pokemon->CanLevelUp())
				{
					log.AddLog(pokemon->LevelUp());
				}
			}
			if (combat.lastCombatWin)
			{
                return true;
			}
            return false;
		}
		case 3:
		{
			for (auto& npc1 : npcs)
			{
				if (npc1->ID == state.stateAction[1])
				{
					if (npc1->state == state.stateAction[2])
					{
                        return true;
					}
				}
			}
            return false;
		}
        case 4:
		{
			if (backpack.GetProp_(state.stateAction[1]))
			{
                return true;
			}
            return false;
		}
        case 5:
		{
			if (backpack.GetProp_(state.stateAction[1])->GetNum() >= state.stateAction[2])
			{
				backpack.ReduceProp(state.stateAction[1], state.stateAction[2]);
                return true;
			}
            return false;
		}
        case 6:
		{
			if (pokemonLib.CheckPokemon(state.stateAction[1]))
			{
				return true;
			}
            return false;
		}
        case 7:
		{
			Pokemon* pokemon_add = new Pokemon(state.stateAction[1], state.stateAction[2]);
            pokemonLib.AddPokemon(pokemon_add);
			Text info;
            info.Add(npc->name,GREEN);
            info.Add("给了你一只");
            info.Add(pokemon_add->name, YELLOW);
			info.Add("!可在宝可梦中心查看。");
			log.AddLog(info);
            return true;
		}
        case 8:
		{
            backpack.AddProp(state.stateAction[1], state.stateAction[2]);
			Text info;
            info.Add(npc->name,GREEN);
            info.Add("给了你");
			info.Add(backpack.GetProp_(state.stateAction[1])->GetName(), YELLOW);
            info.Add("x");
            info.Add(to_string(state.stateAction[2]), YELLOW);
            info.Add("!");
            log.AddLog(info); 
            return true;
		}
	}
	return false;
}

void Game::StartCombat() 
{
	//初始化战斗
	if (pokemonLib.pokemonInGame.size() == 0 || combat.pokemonAvailable().size() == 0)
	{
		log.AddLog(Text("你没有可以战斗的宝可梦了,无法触发战斗!", RED));
        return;
	}
	inCombat = true;
	int pokemon_id;
	Pokemon* myPokemon = nullptr;
	Prop* myProp = nullptr;
	Skill* mySkill = nullptr;
	bool myAction = true;
	bool enemyAction = true;
	vector<Text> choose;	//选择列表
    choose.push_back(Text("1. 使用技能"));
    choose.push_back(Text("2. 使用道具"));
    choose.push_back(Text("3. 交换上阵"));
    choose.push_back(Text("4. 逃离战斗"));
	while (inCombat)
	{
		ClearScreen();
		command.PrintfList(combat.ShowPokemonInfo());
		combat.combatLog.ShowLog();
		//结束战斗判断
		if (combat.pokemonNow->attribute.hp <= 0)
		{
			combat.beaten.push_back({ combat.enemyNow, combat.pokemonNow });
			vector<Pokemon*> pokemonAlive = combat.pokemonAvailable();
			if (pokemonAlive.size() == 0)
			{

				combat.lastCombatWin = false;
				inCombat = false;
				soundPlayer.Play_Sound(SoundPlayer::MUSIC_Lose);
				return;
			}
			else
			{
				//如果没有宝可梦存活,则切换宝可梦
				Text("请选择你要切换的宝可梦:\n").Print();
				int choose_pokemon = 0;
				do {
					choose_pokemon = command.chooseFromList(combat.PokemonAvailableText());
					
					Text info;
					info.Add("你的");
					info.Add(combat.pokemonNow->name, GREEN);
					combat.ChangePokemon(pokemonAlive[choose_pokemon - 1]); 
					info.Add("被");
					info.Add(combat.pokemonNow->name, GREEN);
					info.Add("替换了!");
					combat.combatLog.AddLog(info);
				} while (!choose_pokemon);
			}
			continue;
		}
		if (combat.enemyNow->attribute.hp <= 0)
		{
			combat.beaten.push_back({ combat.pokemonNow, combat.enemyNow });
			vector<Pokemon*> enemyPokemonAlive = combat.enemyAvailable();
			if (enemyPokemonAlive.size() == 0)
			{
				combat.lastCombatWin = true;
				inCombat = false;
				soundPlayer.Play_Sound(SoundPlayer::MUSIC_Win);
				return;
			}
			else
			{
				Text info;
				info.Add("对方");
				info.Add(combat.enemyNow->name, GREEN);
				info.Add("被击败了!");
				combat.combatLog.AddLog(info);
				combat.enemyNow = enemyPokemonAlive[rand() % enemyPokemonAlive.size()];
				info.Add("对方");
				info.Add("派出了");
				info.Add(combat.enemyNow->name, GREEN);
				combat.combatLog.AddLog(info);
			}
			continue;
		}
		if (myAction)	//如果玩家可以行动
		{
			int choice = command.chooseFromList(choose);
			//选择行动
			if (choice == 0)
			{
				continue;
			}
			else if (choice == 1)	//使用技能
			{
				Text("请选择要使用的技能:\n").Print();
				int skill_id = command.chooseFromList(combat.ShowPokemonSkill());
				if (skill_id == 0) continue;
				else
				{
					mySkill = &combat.pokemonNow->skills[skill_id - 1];
					if (mySkill->PP == 0)
					{
						Text("技能PP不足,无法使用!", RED).Print();
						command.Pause();
						continue;
					}
				}
			}
			else if (choice == 2)	//使用道具
			{

				vector<Prop*> props = backpack.GetPropsCanUseInBattle();
				if (props.size() == 0)
				{
					Text("没有可用的道具,无法使用!").Print();
					command.Pause();
					continue;
				}
				vector<Text> propList;
				Text("请选择要使用的道具:\n").Print();
				for (auto prop : props)
				{
					propList.push_back(Text(prop->GetName() + " x" + to_string(prop->GetNum()) + prop->GetDescription()));
				}
				int prop_id = command.chooseFromList(propList);
				if (prop_id == 0) continue;
				else
				{
					myProp = props[prop_id - 1];
				}
			}
			else if (choice == 3)	//交换宝可梦
			{
				vector<Pokemon*> pokemons = combat.pokemonAvailable();
				if (pokemons.size() == 0)
				{
					Text("没有可用的宝可梦,无法交换").Print();
					continue;
				}
				else
				{
					Text("请选择要交换的宝可梦:\n").Print();
					pokemon_id = command.chooseFromList(combat.PokemonAvailableText());
					if (pokemon_id == 0) continue;
					else
					{
						myPokemon = pokemons[pokemon_id - 1];
					}
				}
			}

			if (choice == 1)
			{
			}
			else if (choice == 2)
			{
				UseProp(myProp);
			}
			else if (choice == 3)
			{
				Text info;
				info.Add("你的");
				info.Add(combat.pokemonNow->name, GREEN);
				info.Add("被");
				info.Add(myPokemon->name, GREEN);
				info.Add("替换了!");
				combat.ChangePokemon(myPokemon);
				combat.combatLog.AddLog(info);
			}
			else if (choice == 4)	//逃跑
			{
				if (combat.TryToEscape())
				{
					Text info;
					info.Add("你的");
					info.Add(combat.pokemonNow->name, GREEN);
					info.Add("成功逃脱了战斗!");
					log.AddLog(info);
					inCombat = false;
					soundPlayer.Play_Sound(SoundPlayer::MUSIC_Lose);
					return;
				}
				else
				{
					Text info;
					info.Add("你的");
					info.Add(combat.pokemonNow->name, GREEN);
					info.Add("试图逃脱战斗,但是");
					info.Add("失败了!", RED);
					combat.combatLog.AddLog(info);
				}
			}

			if (choice == 1)
			{
				//判断是否命中,技能优先级
				Skill* enamy_skill = &combat.enemyNow->skills[rand() % combat.enemyNow->skills.size()];
				int myFirst = 0;
				if (mySkill != nullptr)
					myFirst = mySkill->priority - enamy_skill->priority;
				if (myFirst == 0)
				{
					myFirst = combat.pokemonNow->attribute.speed * combat.pokemonNow->GetBuffValue(combat.pokemonNow->buff.speed) - combat.enemyNow->attribute.speed;
					if (myFirst == 0)
					{
						myFirst = rand() % 2;
					}
				}
				bool myHit, enamyHit;
				int myHitRate, enamyHitRate;
				myHitRate = mySkill->accuracy * combat.pokemonNow->GetBuffValue(combat.pokemonNow->buff.accuracy) / combat.enemyNow->GetBuffValue(combat.enemyNow->buff.evasion);
				enamyHitRate = enamy_skill->accuracy * combat.enemyNow->GetBuffValue(combat.enemyNow->buff.accuracy) / combat.pokemonNow->GetBuffValue(combat.pokemonNow->buff.evasion);
				myHit = rand() % 100 < myHitRate;
				enamyHit = rand() % 100 < enamyHitRate;
				if (mySkill->mustHit) myHit = true;
				if (enamy_skill->mustHit) enamyHit = true;
				if (myHit)
				{
					if (myFirst > 0) 
					UseSkill(mySkill, combat.pokemonNow, combat.enemyNow);
					if (combat.enemyNow->attribute.hp > 0)
					{
						if (enamyHit)
						{
							UseSkill(enamy_skill, combat.enemyNow, combat.pokemonNow);
						}
						else
						{
							Text info;
							info.Add("对方");
							info.Add(combat.enemyNow->name, GREEN);
							info.Add("使用了");
							info.Add(enamy_skill->skillName, GREEN);
							info.Add("但是被你的");
							info.Add(combat.pokemonNow->name, GREEN);
							info.Add("躲过", RED);
							info.Add("了!");
							combat.combatLog.AddLog(info);
						}
					}
					if(myFirst<= 0) UseSkill(mySkill, combat.pokemonNow, combat.enemyNow);
				}
				else
				{
					Text info;
					info.Add("你的");
					info.Add(combat.pokemonNow->name, GREEN);
					info.Add("使用了");
					info.Add(mySkill->skillName, GREEN);
					info.Add("但是被对方");
					info.Add(combat.enemyNow->name, GREEN);
					info.Add("躲过", RED);
					info.Add("了!");
					combat.combatLog.AddLog(info);
					if (enamyHit)
					{
						UseSkill(enamy_skill, combat.enemyNow, combat.pokemonNow);
					}
					else
					{
						Text info;
						info.Add("对方");
						info.Add(combat.enemyNow->name, GREEN);
						info.Add("使用了");
						info.Add(enamy_skill->skillName, GREEN);
						info.Add("但是被你的");
						info.Add(combat.pokemonNow->name, GREEN);
						info.Add("躲过", RED);
						info.Add("了!");
						combat.combatLog.AddLog(info);
					}
				}
				mySkill->PP--;
				enamy_skill->PP--;
			}
			else
			{
				Skill* enamy_skill = &combat.enemyNow->skills[rand() % combat.enemyNow->skills.size()];
				bool  enamyHit;
				int  enamyHitRate;
				enamyHitRate = enamy_skill->accuracy * combat.enemyNow->GetBuffValue(combat.enemyNow->buff.accuracy) / combat.pokemonNow->GetBuffValue(combat.pokemonNow->buff.evasion);
				enamyHit = rand() % 100 < enamyHitRate;
				if (enamy_skill->mustHit) enamyHit = true;
				if (enamyHit)
				{
					UseSkill(enamy_skill, combat.enemyNow, combat.pokemonNow);
					if (combat.enemyNow->attribute.hp == 0)
					{
						combat.beaten.push_back({ combat.pokemonNow, combat.enemyNow });
						combat.lastCombatWin = true;
						soundPlayer.Play_Sound(SoundPlayer::MUSIC_Win);
						return;
					}
				}
				else
				{
					Text info;
					info.Add("对方");
					info.Add(combat.enemyNow->name, GREEN);
					info.Add("使用了");
					info.Add(enamy_skill->skillName, GREEN);
					info.Add("但是被你的");
					info.Add(combat.pokemonNow->name, GREEN);
					info.Add("躲过", RED);
					info.Add("了!");
					combat.combatLog.AddLog(info);
				}
				enamy_skill->PP--;
			}
		}
		else
		{
			Text info; 
            info.Add("你的");
            info.Add(combat.pokemonNow->name, GREEN);
            info.Add("处于");
            info.Add(combat.pokemonNow->GetStatuName(combat.pokemonNow->statu), RED);
            info.Add("状态，无法行动!");
            combat.combatLog.AddLog(info);
			if (enemyAction)
			{
				Skill* enamy_skill = &combat.enemyNow->skills[rand() % combat.enemyNow->skills.size()];
				bool  enamyHit;
				int  enamyHitRate;
				enamyHitRate = enamy_skill->accuracy * combat.enemyNow->GetBuffValue(combat.enemyNow->buff.accuracy) / combat.pokemonNow->GetBuffValue(combat.pokemonNow->buff.evasion);
				enamyHit = rand() % 100 < enamyHitRate;
				if (enamy_skill->mustHit) enamyHit = true;
				if (enamyHit)
				{
					UseSkill(enamy_skill, combat.enemyNow, combat.pokemonNow);
					if (combat.enemyNow->attribute.hp == 0)
					{
						combat.beaten.push_back({ combat.pokemonNow, combat.enemyNow });
						combat.lastCombatWin = true;
						soundPlayer.Play_Sound(SoundPlayer::MUSIC_Win);
						return;
					}
				}
			}
			else
			{
				Text info;
                info.Add("对方");
                info.Add(combat.enemyNow->name, GREEN);
                info.Add("处于");
                info.Add(combat.enemyNow->GetStatuName(combat.enemyNow->statu), RED);
                info.Add("状态，无法行动!");
                combat.combatLog.AddLog(info);
			}
		}
		//我方宝可梦状态判断
		if (combat.pokemonNow->statu == Pokemon::Poison)
		{
			int damage = combat.pokemonNow->attribute.maxHp / 8;
			if (damage >15) damage = 15;
            if (damage < 1) damage = 1;
            combat.pokemonNow->attribute.hp -= damage;
			if (combat.pokemonNow->attribute.hp < 0) combat.pokemonNow->attribute.hp = 0;
            Text info;
            info.Add("你的");
            info.Add(combat.pokemonNow->name, GREEN);
            info.Add("受到");
            info.Add(std::to_string(damage), RED);
            info.Add("点毒伤!");
            combat.combatLog.AddLog(info);
		}
		else if (combat.pokemonNow->statu == Pokemon::Paralysis)
		{
			myAction = rand() % 100 < 75;
		}
		else if (combat.pokemonNow->statu == Pokemon::Burn) 
		{
			int damage = combat.pokemonNow->attribute.maxHp / 16;
			if (damage > 15) damage = 15;
			if (damage < 1) damage = 1;
			combat.pokemonNow->attribute.hp -= damage;
            if (combat.pokemonNow->attribute.hp < 0) combat.pokemonNow->attribute.hp = 0;
			Text info;
			info.Add("你的");
			info.Add(combat.pokemonNow->name, GREEN);
			info.Add("受到");
			info.Add(std::to_string(damage), RED);
			info.Add("点毒伤!");
			combat.combatLog.AddLog(info);
		}
		else if (combat.pokemonNow->statu == Pokemon::Sleep)
		{
			if (rand() % 100 < 20) 
			{
				myAction = true, combat.pokemonNow->statu = Pokemon::None;
                Text info;
                info.Add("你的");
                info.Add(combat.pokemonNow->name, GREEN);
                info.Add("从睡眠中苏醒!");
                combat.combatLog.AddLog(info);
			}
            else myAction = false;
		}
		else if (combat.pokemonNow->statu == Pokemon::Freeze)
		{
			if (rand() % 100 < 10)
			{
                myAction = true, combat.pokemonNow->statu = Pokemon::None;
                Text info;
                info.Add("你的");
                info.Add(combat.pokemonNow->name, GREEN);
                info.Add("从冰冻中苏醒!");
                combat.combatLog.AddLog(info);
			}
            else myAction = false;
		}
		else if (combat.pokemonNow->statu == Pokemon::Frostbite)
		{
			if (combat.pokemonNow->type.first == Type::ICE || combat.pokemonNow->type.second == Type::ICE)
			{
				Text info;
                info.Add("你的");
                info.Add(combat.pokemonNow->name, GREEN);
                info.Add("不受冻伤影响!");
                combat.combatLog.AddLog(info);
			}
            else
			{
				int damage = combat.pokemonNow->attribute.maxHp / 16;
				combat.pokemonNow->attribute.hp -= damage;
				if (combat.pokemonNow->attribute.hp < 0) combat.pokemonNow->attribute.hp = 0;
				Text info;
				info.Add("你的");
				info.Add(combat.pokemonNow->name, GREEN);
				info.Add("受到");
				info.Add(std::to_string(damage), RED);
				info.Add("点冻伤!");
				combat.combatLog.AddLog(info); 
			}
		}
		//敌方宝可梦状态判断
		if (combat.enemyNow->statu == Pokemon::Poison)
		{
			int damage = combat.enemyNow->attribute.maxHp / 8;
			if (damage > 15) damage = 15;
			if (damage < 1) damage = 1;
			combat.enemyNow->attribute.hp -= damage;
			if (combat.enemyNow->attribute.hp < 0) combat.enemyNow->attribute.hp = 0;
			Text info;
			info.Add("对方的");
			info.Add(combat.enemyNow->name, GREEN);
			info.Add("受到");
			info.Add(std::to_string(damage), RED);
			info.Add("点毒伤!");
			combat.combatLog.AddLog(info);
		}
		else if (combat.enemyNow->statu == Pokemon::Paralysis)
		{
			myAction = rand() % 100 < 75;
		}
		else if (combat.enemyNow->statu == Pokemon::Burn)
		{
			int damage = combat.enemyNow->attribute.maxHp / 16;
			if (damage > 15) damage = 15;
			if (damage < 1) damage = 1;
			combat.enemyNow->attribute.hp -= damage;
			if (combat.enemyNow->attribute.hp < 0) combat.enemyNow->attribute.hp = 0;
			Text info;
			info.Add("对方的");
			info.Add(combat.enemyNow->name, GREEN);
			info.Add("受到");
			info.Add(std::to_string(damage), RED);
			info.Add("点毒伤!");
			combat.combatLog.AddLog(info);
		}
		else if (combat.enemyNow->statu == Pokemon::Sleep)
		{
			if (rand() % 100 < 20)
			{
				myAction = true, combat.enemyNow->statu = Pokemon::None;
				Text info;
				info.Add("对方的");
				info.Add(combat.enemyNow->name, GREEN);
				info.Add("从睡眠中苏醒!");
				combat.combatLog.AddLog(info);
			}
			else myAction = false;
		}
		else if (combat.enemyNow->statu == Pokemon::Freeze)
		{
			if (rand() % 100 < 10)
			{
				myAction = true, combat.enemyNow->statu = Pokemon::None;
				Text info;
				info.Add("对方的");
				info.Add(combat.enemyNow->name, GREEN);
				info.Add("从冰冻中苏醒!");
				combat.combatLog.AddLog(info);
			}
			else myAction = false;
		}
		else if (combat.enemyNow->statu == Pokemon::Frostbite)
		{
			if (combat.enemyNow->type.first == Type::ICE || combat.enemyNow->type.second == Type::ICE)
			{
				Text info;
				info.Add("对方的");
				info.Add(combat.enemyNow->name, GREEN);
				info.Add("不受冻伤影响!");
				combat.combatLog.AddLog(info);
			}
			else
			{
				int damage = combat.enemyNow->attribute.maxHp / 16;
				combat.enemyNow->attribute.hp -= damage;
				if (combat.enemyNow->attribute.hp < 0) combat.enemyNow->attribute.hp = 0;
				Text info;
				info.Add("对方的");
				info.Add(combat.enemyNow->name, GREEN);
				info.Add("受到");
				info.Add(std::to_string(damage), RED);
				info.Add("点冻伤!");
				combat.combatLog.AddLog(info);
			}
		}
	}
}