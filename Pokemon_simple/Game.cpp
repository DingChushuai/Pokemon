#include "Game.h"
#pragma once
#include <fstream>

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
				DrawTitle();
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
					Text("\n你上阵中的宝可梦：\n").Print();
					Text("\n选择并查看宝可梦的详细信息, ESC退出\n", RED, GRAY).Print();
					vector<Text> pokemonsInGame = pokemonLib.GetPokemonInGameInfo();
					if (pokemonsInGame.size() == 0)
					{
                        Text("\n你的队伍中没有宝可梦,请先获取一只宝可梦!\n", RED, GRAY).Print();
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
					vector<Text> props = backpack.GetPropsInfo();
                    if (props.size() == 0)
                    {
                        Text("\n你的背包中没有道具,请先获取一些道具!\n", RED, GRAY).Print();
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
				vector<Text> props = shop.GetPropsInShop();
				int choice = command.chooseFromList(props,10);
				if (choice == 0) { gameSenceStack.pop_back(); break; }
				int price = shop.GetPriceOfProp(choice);
				if (money < price)
				{
                    Text("\n你的钱不够了,请先去赚点钱吧!\n", RED).Print();
					command.Pause();
                    gameSenceStack.pop_back();
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
                log.AddLog(info);
				info.Print();
                command.Pause();
                gameSenceStack.pop_back();
                break;
			}
            case SELL_ITEM:
			{
				vector<Text> props = backpack.GetPropsSellPrice();
				if (props.size() == 0)
				{
					Text("\n你的背包中没有道具,请先去获取一些道具吧!\n", RED).Print();
                    command.Pause();
                    gameSenceStack.pop_back();
                    break;				}
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
				if (pokemonNames.size() == 0)
				{
                    Text("\n你的仓库中没有宝可梦,请先去抓一些宝可梦吧!\n", RED).Print();
                    command.Pause();
                    gameSenceStack.pop_back();
                    break;
				}
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
				if (pokemonLib.pokemonInGame.size() == 0)
				{
                    log.AddLog(Text("你没有可以战斗的宝可梦了,无法触发战斗!", RED));
					gameSenceStack.pop_back();
                    break;
				}
				StartCombat();
				combat.EndCombat();
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
				Text("command list:\n").Print();
				Text("music: change music now\n").Print();
                Text("money(m): set money number\n").Print();
                Text("exit(e): exit debug\n").Print();
				Text("Debug:\ninput cmd:", RED).Print();
				string input;
                cin >> input;
                if (input == "exit"  || input == "e") { gameSenceStack.pop_back(); break; }
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
                break;
			}
			case WORLD_MAP:  
			{
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
	playerX = 1;
    playerY = 8;
	money = 0;
	inCombat = false;
	Map* map0= new Map(0);
	currentMap = map0;
	maps.push_back(map0);

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
	int maxX = currentMap->getMapWidth();
    int maxY = currentMap->getMapHeight();
	for (auto npc : npcs)
	{
		if (npc->mapID == currentMap->getMapID())
		{
			Text(string(1, npc->name[0])+" : "+npc->name+"\t", GREEN).Print();
		}
	}
	cout << endl;
	pair<int, int> pos = GetPos();
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
	for (auto npc : npcs)
	{
		if (npc->mapID == currentMap->getMapID())
		{
			GotoXY(pos.first + npc->x, pos.second + npc->y);
            Text(string(1, npc->name[0]),GREEN,GRAY).Print();
		}
	}
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
            case UP: if(newY>0) newY--; break;
            case DOWN:if(newY<maxY-1) newY++; break;
            case LEFT:if(newX>0) newX--; break; 
            case RIGHT:if(newX<maxX-1) newX++; break; 
            }
            Map::MapBlock block = currentMap->getMapBlock(newX, newY);
			Map::MapBlock blockOld = currentMap->getMapBlock(playerX, playerY);
			bool isNPC = false;
			for (auto npc : npcs)
			{
				if (npc->mapID == currentMap->getMapID())
				{
					if (npc->x == newX && npc->y == newY)
					{
						if (ChangeNPCState(npc))
						{
                            isNPC = true;
							Text info;
							info.Add(npc->name, YELLOW);
                            info.Add(" : ");
                            info.Add(npc->GetTalk(), YELLOW);
							log.AddLog(info);
                            break;
						}
					}
				}
			}
            if (isNPC) break;
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
				vector<vector<int>> wilds = currentMap->getWildPokemon();
				int wild_index = -1;
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
					combat.InitWildCombat(wilds[wild_index][0], wilds[wild_index][1], &pokemonLib);
                    gameSenceStack.push_back(COMBAT);
                    break;
				}
			}
			else if (block.type == Map::EXIT)
			{
				Text info;
                info.Add("你离开了");
                info.Add(currentMap->getMapName(), YELLOW);
                info.Add("来到了");
                
				vector<int> newMap = currentMap->getExit(newX, newY);
				if (newMap.size() == 0)
				{
					break;
				}
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
				//TODO:
                //将玩家当前上阵的所有宝可梦的体力恢复到满值
				//打印一条log,并刷新log
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
	/*
		EREASE_STATUS,  //消除自身状态(PokemonStatu(0表示可以消除任何状态))
		CHANGE_POKEMON_ATTRBUTE,  //改变宝可梦属性(ATTRIBUTE,改变值,...)  //在野外使用为永久改变,在战斗中使用为临时改变
		CHANGE_SKILL_ATTRIBUTE,  //改变技能属性(改变条件,条件参数,技能属性,改变值,技能属性,改变值...)
		* 改变条件,条件参数:
		* 0.无条件(参数无效)
		* 1.技能类型(SkillType)
		* 2.技能属性(Type)
		技能属性id:
		1.power;              //威力
		2.accuracy;           //命中
		3.PP;                 //pp
		4.maxPP;              //最大pp
		
		BUFF,   //改变能力状态修正值(能力状态修正值,改变值,...)  //在战斗中临时改变
		HEAL,  //回复体力(濒死时是否可用,回复方式(0按百分比,1按具体值),百分比/具体值)
		GET_SKILL,   //使宝可梦获得技能(技能ID), 生效前需要判断是否合理
		CAPTURE,    //精灵球类型(捕获率加成,对特定的Type属性的宝可梦,特定捕获率加成)
		SPECIAL_PROP,  //特殊道具(特殊函数id,函数参数1,函数参数2...)
	*/
	switch (prop->GetType())
	{
        case 0:
		{
            break;
		}
        case 1:
		{
			if (inCombat)
			{
				vector<Pokemon*> pokes = combat.myPokemons;
				vector<Text> pokemonInfo;
				for (auto poke : pokes)
				{
					pokemonInfo.push_back(Text(poke->name + to_string(poke->attribute.hp) + "/" + to_string(poke->attribute.maxHp) + " HP" + poke->GetStatuName(poke->statu)));
				}
				int index = command.chooseFromList(pokemonInfo);

			}
		}
	}
}

void Game::UseSkill(Skill* skill, Pokemon* user,Pokemon* target)
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
	State state = npc->GetState();
	switch (state.stateAction[0])
	{
		case 0: 
		{
			npc->state = state.stateNext;
			return true;
		}
        case 1:
		{
			npc->mapID = state.stateAction[1];
			npc->x = state.stateAction[2];
            npc->y = state.stateAction[3];
			npc->state = state.stateNext;
            return true;
		}
		case 2 :
		{
			combat.InitTrainerCombat(state.stateAction[1],&pokemonLib);
			ClearScreen();
			StartCombat();
			if (combat.lastCombatWin)
			{
				npc->state = state.stateNext;
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
                        npc->state = state.stateNext;
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
                npc->state = state.stateNext;
                return true;
			}
            return false;
		}
        case 5:
		{
			if (backpack.GetProp_(state.stateAction[1])->GetNum() >= state.stateAction[2])
			{
				backpack.ReduceProp(state.stateAction[1], state.stateAction[2]);
                npc->state = state.stateNext;
                return true;
			}
            return false;
		}
        case 6:
		{
			if (pokemonLib.CheckPokemon(state.stateAction[1]))
			{
				npc->state = state.stateNext;
				return true;
			}
            return false;
		}
        case 7:
		{
			Pokemon* pokemon_add = new Pokemon(state.stateAction[1], state.stateAction[2]);
            pokemonLib.AddPokemon(pokemon_add);
            npc->state = state.stateNext;
            return true;
		}
        case 8:
		{
            backpack.AddProp(state.stateAction[1], state.stateAction[2]);
            npc->state = state.stateNext;
            return true;
		}
	}
	return false;
}

void Game::StartCombat() 
{
	inCombat = true;
	vector<Text> choose;
    choose.push_back(Text("1. 使用技能"));
    choose.push_back(Text("2. 使用道具"));
    choose.push_back(Text("3. 交换上阵"));
    choose.push_back(Text("4. 逃离战斗"));
	while (inCombat)
	{
		command.PrintfList(combat.ShowPokemonInfo());
		combat.combatLog.ShowLog();
		int choice = command.chooseFromList(choose);
		int pokemon_id;
		Pokemon* myPokemon = nullptr;
		Prop* myProp = nullptr;
		Skill* mySkill = nullptr;
		if (choice == 0)
		{
			continue;
		}
		else if (choice == 1)
		{
			Text("请选择要使用的技能:\n").Print();
			int skill_id = command.chooseFromList(combat.ShowPokemonSkill());
            if (skill_id == 0) continue;
			else
			{
				mySkill = &combat.pokemonNow->skills[skill_id - 1];
				if (mySkill->PP == 0)
				{
                    Text("技能PP不足,无法使用!",RED).Print();
					command.Pause();
                    continue;
				}
			}
		}
		else if (choice == 2)
		{
            Text("请选择要使用的道具:\n").Print();
			vector<Prop*> props = backpack.GetPropsCanUseInBattle();
			vector<Text> propList;
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
		else if (choice == 3)
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
		Skill* enamy_skill = &combat.enemyNow->skills[rand() % combat.enemyNow->skills.size()];
		int myFirst = mySkill->priority - enamy_skill->priority;
		if (myFirst == 0)
		{
			
			myFirst = combat.pokemonNow->attribute.speed* combat.pokemonNow->GetBuffValue(combat.pokemonNow->buff.speed) - combat.enemyNow->attribute.speed;
			if (myFirst == 0)
			{
				myFirst = rand() % 2;
			}
		}
		bool myHit, enamyHit;
		int myHitRate, enamyHitRate;
		myHitRate = mySkill->accuracy * combat.pokemonNow->GetBuffValue(combat.pokemonNow->buff.accuracy) / combat.enemyNow->GetBuffValue(combat.enemyNow->buff.evasion);
        enamyHitRate = enamy_skill->accuracy * combat.enemyNow->GetBuffValue(combat.enemyNow->buff.accuracy) / combat.pokemonNow-> GetBuffValue(combat.pokemonNow->buff.evasion);
		myHit = rand() % 100 < myHitRate;
        enamyHit = rand() % 100 < enamyHitRate;
		if (mySkill->mustHit) myHit = true;
        if (enamy_skill->mustHit) enamyHit = true;
		if (choice == 1)
		{
			if(myHit)
			{
				if (myFirst > 0) UseSkill(mySkill, combat.pokemonNow, combat.enemyNow);
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
			}
			else
			{
				mySkill->PP--;
				Text info;
				info.Add("你的");
				info.Add(combat.pokemonNow->name, GREEN);
                info.Add("使用了");
                info.Add(mySkill->skillName, GREEN);
                info.Add("但是被对方");
                info.Add(combat.enemyNow->name, GREEN);
                info.Add("躲过",RED);
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
                    info.Add("躲过",RED);
                    info.Add("了!");
					combat.combatLog.AddLog(info);
				}
			}
		}
		else if (choice == 2)
		{
			//使用道具
			UseProp(myProp);
			if (enamyHit)
			{
				UseSkill(enamy_skill, combat.enemyNow, combat.pokemonNow);
				if (combat.enemyNow->attribute.hp == 0)
				{
					combat.beaten.push_back({ combat.pokemonNow, combat.enemyNow });
					combat.lastCombatWin= true;
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
		else if (choice == 4)
		{
			if (combat.TryToEscape())
			{
                Text info;
                info.Add("你的");
                info.Add(combat.pokemonNow->name, GREEN);
                info.Add("成功逃脱了战斗!");
                log.AddLog(info);
				return;
			}
			else
			{
                Text info;
                info.Add("你的");
                info.Add(combat.pokemonNow->name, GREEN);
                info.Add("试图逃脱战斗,但是");
                info.Add("失败了!", RED);
                log.AddLog(info);
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
		}
		//结算状态
		if (combat.pokemonNow->attribute.hp <= 0)
		{
			combat.beaten.push_back({ combat.enemyNow, combat.pokemonNow });
			vector<Pokemon*> pokemonAlive = combat.pokemonAvailable();
			if (pokemonAlive.size() == 0)
			{
               combat.lastCombatWin = false;
               	return;
			}
			else
			{
				Text("请选择你要切换的宝可梦:\n").Print();
				int choose_pokemon = 0;
				do {
					choose_pokemon = command.chooseFromList(combat.PokemonAvailableText());
					combat.ChangePokemon(pokemonAlive[choose_pokemon - 1]);
					Text info;
                    info.Add("你的");
                    info.Add(combat.pokemonNow->name, GREEN);
                    info.Add("被");
                    info.Add(myPokemon->name, GREEN);
                    info.Add("替换了!");
                    combat.combatLog.AddLog(info);
				} while (!choose_pokemon);
			}
		}
		if (combat.enemyNow->attribute.hp <= 0)
		{
            combat.beaten.push_back({ combat.pokemonNow, combat.enemyNow });
			vector<Pokemon*> enemyPokemonAlive = combat.enemyAvailable();
			if (enemyPokemonAlive.size() == 0)
			{
                combat.lastCombatWin = true;
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
		}
	}
}

