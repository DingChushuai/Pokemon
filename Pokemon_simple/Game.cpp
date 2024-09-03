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
				Menu.push_back(Text("1. ��ʼ����Ϸ"));
				Menu.push_back(Text("2. ������Ϸ"));
				Menu.push_back(Text("3. �˳���Ϸ"));
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
				Menu.push_back(Text("1. ������Ϸ"));
				Menu.push_back(Text("2. ������Ϸ"));
				Menu.push_back(Text("3. ��������"));
				Menu.push_back(Text("4. ���沢�˳�"));
				Menu.push_back(Text("5. ���ز˵�"));
				int choice = command.chooseFromList(Menu);
				if (choice == 1)
				{
					Save();
					Text("��Ϸ�ѱ���", GREEN, GRAY).Print();
					log.AddLog(Text("��ǰ�����ѱ���!", GREEN));
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
                        Text("�����ѿ���", GREEN, GRAY).Print();
                        log.AddLog(Text("�����ѿ���!", GREEN));
						command.Pause();
					}
					else
					{
                        soundPlayer.forbidMusic = true;
                        Text("�����ѹر�", GREEN, GRAY).Print();
                        log.AddLog(Text("�����ѹر�!", GREEN));
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
					Text("\n�������еı����Σ�\n").Print();
					Text("\nѡ�񲢲鿴�����ε���ϸ��Ϣ, ESC�˳�\n", RED, GRAY).Print();
					vector<Text> pokemonsInGame = pokemonLib.GetPokemonInGameInfo();
					if (pokemonsInGame.size() == 0)
					{
                        Text("\n��Ķ�����û�б�����,���Ȼ�ȡһֻ������!\n", RED, GRAY).Print();
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
					Text("�����������").Print();
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
                        Text("\n��ı�����û�е���,���Ȼ�ȡһЩ����!\n", RED, GRAY).Print();
                        command.Pause();
                        gameSenceStack.pop_back();
                        break;
                    }
					int choice = command.chooseFromList(props,10);
                    if (choice == 0) { gameSenceStack.pop_back(); break; } 
					Prop* PropNow = backpack.GetPropFromIndex(choice);
					if (!PropNow->IsCanUseInField())
					{
						Text("\n�õ����޷���Ұ��ʹ��!\n", RED).Print();
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
						Text("\n��Ķ�����û�б�����,���Ȼ�ȡһֻ������!\n", RED, GRAY).Print();
                        command.Pause();
                        gameSenceStack.pop_back();
						break;
					}
					if (pokemonsInLib.size() == 0)
					{
						Text("\n��Ĳֿ���û�б�����,���ȡ���౦���κ�����������!\n", RED, GRAY).Print();
						command.Pause();
						gameSenceStack.pop_back();
						break;
					}
					command.PrintfList(pokemonsIngame);
					Text("\nѡ��һֻ���еı����ν�����鿴��ϸ��Ϣ\n", None, GRAY).Print();
					int indexInLib = command.chooseFromList(pokemonsInLib, 20);
					if (indexInLib == 0) { gameSenceStack.pop_back(); break; }
					vector<Text> options;
					options.push_back(Text("1. �鿴��ϸ��Ϣ\n"));
					options.push_back(Text("2. ����������\n"));
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
					options.push_back(Text("1. �������"));
					options.push_back(Text("2. ��������"));
					options.push_back(Text("3. �����ֿ��еı�����"));
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
                    Text("\n���Ǯ������,����ȥ׬��Ǯ��!\n", RED).Print();
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
                info.Add("�㹺����");
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
					Text("\n��ı�����û�е���,����ȥ��ȡһЩ���߰�!\n", RED).Print();
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
                info.Add("��������"); 
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
                    Text("\n��Ĳֿ���û�б�����,����ȥץһЩ�����ΰ�!\n", RED).Print();
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
                info.Add("��������");
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
                    log.AddLog(Text("��û�п���ս���ı�������,�޷�����ս��!", RED));
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
					log.AddLog(Text("��Ľ�������Ѹ���Ϊ: " + to_string(money), YELLOW));
                    command.Pause();
                }
                break;
			}
			case WORLD_MAP:  
			{
				{
                    Text("�����������ͼ:\n", GREEN).Print();
                    DrawWorldMap();
					Text("�������������Ϸ").Print();
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

	//TODO: ��NPC_Info.txt��ȡ����NPC��Ϣ,����ΪNPCS_COUNT
	//ʹ�� new �����µĶ���, ���캯��ʹ��NPC(int id);
	//���������,NPC��id��NPC_Info.txt�е�������Ӧ(��1��ʼ)

	soundPlayer.PlayMusic(SoundPlayer::MUSIC_ZhenXinZhen);
	log.clearLog();
	log.AddLog(Text("��ӭ�������������磡",GREEN));
}

void Game::Load()
{
    //TODO: ��Game_State.txt��ȡ
    //��ȡ������README.md������ϸ˵��
	// ע�⴦����ļ������

    //TODO: ��NPC_State.csv��ȡ,������npcs
    //��ȡ������README.md������ϸ˵��
	//��ȡÿ��npcʱʹ�� new �����µĶ���, ���캯��ʹ��NPC(string info);
    //ע�⴦����ļ������

    backpack.Load(); 
    pokemonLib.Load(); 
}

void Game::Save()
{
	//TODO: ���浽Game_State.txt
	//����������README.md������ϸ˵��

	//TODO: ���浽NPC_State.csv
	//NPC: vector<NPC*> npcs;
	//����������README.md������ϸ˵��
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
                info.Add("���뿪��");
                info.Add(currentMap->getMapName(), YELLOW);
                info.Add("������");
                
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
                //����ҵ�ǰ��������б����ε������ָ�����ֵ
				//��ӡһ��log,��ˢ��log
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
		EREASE_STATUS,  //��������״̬(PokemonStatu(0��ʾ���������κ�״̬))
		CHANGE_POKEMON_ATTRBUTE,  //�ı䱦��������(ATTRIBUTE,�ı�ֵ,...)  //��Ұ��ʹ��Ϊ���øı�,��ս����ʹ��Ϊ��ʱ�ı�
		CHANGE_SKILL_ATTRIBUTE,  //�ı似������(�ı�����,��������,��������,�ı�ֵ,��������,�ı�ֵ...)
		* �ı�����,��������:
		* 0.������(������Ч)
		* 1.��������(SkillType)
		* 2.��������(Type)
		��������id:
		1.power;              //����
		2.accuracy;           //����
		3.PP;                 //pp
		4.maxPP;              //���pp
		
		BUFF,   //�ı�����״̬����ֵ(����״̬����ֵ,�ı�ֵ,...)  //��ս������ʱ�ı�
		HEAL,  //�ظ�����(����ʱ�Ƿ����,�ظ���ʽ(0���ٷֱ�,1������ֵ),�ٷֱ�/����ֵ)
		GET_SKILL,   //ʹ�����λ�ü���(����ID), ��Чǰ��Ҫ�ж��Ƿ����
		CAPTURE,    //����������(�����ʼӳ�,���ض���Type���Եı�����,�ض������ʼӳ�)
		SPECIAL_PROP,  //�������(���⺯��id,��������1,��������2...)
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
    choose.push_back(Text("1. ʹ�ü���"));
    choose.push_back(Text("2. ʹ�õ���"));
    choose.push_back(Text("3. ��������"));
    choose.push_back(Text("4. ����ս��"));
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
			Text("��ѡ��Ҫʹ�õļ���:\n").Print();
			int skill_id = command.chooseFromList(combat.ShowPokemonSkill());
            if (skill_id == 0) continue;
			else
			{
				mySkill = &combat.pokemonNow->skills[skill_id - 1];
				if (mySkill->PP == 0)
				{
                    Text("����PP����,�޷�ʹ��!",RED).Print();
					command.Pause();
                    continue;
				}
			}
		}
		else if (choice == 2)
		{
            Text("��ѡ��Ҫʹ�õĵ���:\n").Print();
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
                Text("û�п��õı�����,�޷�����").Print();
                continue;
			}
			else
			{
                Text("��ѡ��Ҫ�����ı�����:\n").Print();
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
						info.Add("�Է�");
						info.Add(combat.enemyNow->name, GREEN);
						info.Add("ʹ����");
						info.Add(enamy_skill->skillName, GREEN);
						info.Add("���Ǳ����");
						info.Add(combat.pokemonNow->name, GREEN);
						info.Add("���", RED);
						info.Add("��!");
						combat.combatLog.AddLog(info);
					}
				}
			}
			else
			{
				mySkill->PP--;
				Text info;
				info.Add("���");
				info.Add(combat.pokemonNow->name, GREEN);
                info.Add("ʹ����");
                info.Add(mySkill->skillName, GREEN);
                info.Add("���Ǳ��Է�");
                info.Add(combat.enemyNow->name, GREEN);
                info.Add("���",RED);
				info.Add("��!");
				combat.combatLog.AddLog(info);
				if (enamyHit)
				{
                    UseSkill(enamy_skill, combat.enemyNow, combat.pokemonNow);
				}
				else
				{
                    Text info;
                    info.Add("�Է�");
                    info.Add(combat.enemyNow->name, GREEN);
                    info.Add("ʹ����");
                    info.Add(enamy_skill->skillName, GREEN);
                    info.Add("���Ǳ����");
                    info.Add(combat.pokemonNow->name, GREEN);
                    info.Add("���",RED);
                    info.Add("��!");
					combat.combatLog.AddLog(info);
				}
			}
		}
		else if (choice == 2)
		{
			//ʹ�õ���
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
				info.Add("�Է�");
				info.Add(combat.enemyNow->name, GREEN);
				info.Add("ʹ����");
				info.Add(enamy_skill->skillName, GREEN);
				info.Add("���Ǳ����");
				info.Add(combat.pokemonNow->name, GREEN);
				info.Add("���", RED);
				info.Add("��!");
				combat.combatLog.AddLog(info);
			}

		}
		else if (choice == 3)
		{
			Text info;
            info.Add("���");
            info.Add(combat.pokemonNow->name, GREEN);
            info.Add("��");
            info.Add(myPokemon->name, GREEN);
            info.Add("�滻��!");
			combat.ChangePokemon(myPokemon);
            combat.combatLog.AddLog(info);
			if (enamyHit)
			{
				UseSkill(enamy_skill, combat.enemyNow, combat.pokemonNow);
			}
			else
			{
				Text info;
				info.Add("�Է�");
				info.Add(combat.enemyNow->name, GREEN);
				info.Add("ʹ����");
				info.Add(enamy_skill->skillName, GREEN);
				info.Add("���Ǳ����");
				info.Add(combat.pokemonNow->name, GREEN);
				info.Add("���", RED);
				info.Add("��!");
				combat.combatLog.AddLog(info);
			}
		}
		else if (choice == 4)
		{
			if (combat.TryToEscape())
			{
                Text info;
                info.Add("���");
                info.Add(combat.pokemonNow->name, GREEN);
                info.Add("�ɹ�������ս��!");
                log.AddLog(info);
				return;
			}
			else
			{
                Text info;
                info.Add("���");
                info.Add(combat.pokemonNow->name, GREEN);
                info.Add("��ͼ����ս��,����");
                info.Add("ʧ����!", RED);
                log.AddLog(info);
				if (enamyHit)
				{
					UseSkill(enamy_skill, combat.enemyNow, combat.pokemonNow);
				}
				else
				{
					Text info;
					info.Add("�Է�");
					info.Add(combat.enemyNow->name, GREEN);
					info.Add("ʹ����");
					info.Add(enamy_skill->skillName, GREEN);
					info.Add("���Ǳ����");
					info.Add(combat.pokemonNow->name, GREEN);
					info.Add("���", RED);
					info.Add("��!");
					combat.combatLog.AddLog(info);
				}
			}
		}
		//����״̬
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
				Text("��ѡ����Ҫ�л��ı�����:\n").Print();
				int choose_pokemon = 0;
				do {
					choose_pokemon = command.chooseFromList(combat.PokemonAvailableText());
					combat.ChangePokemon(pokemonAlive[choose_pokemon - 1]);
					Text info;
                    info.Add("���");
                    info.Add(combat.pokemonNow->name, GREEN);
                    info.Add("��");
                    info.Add(myPokemon->name, GREEN);
                    info.Add("�滻��!");
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
                info.Add("�Է�");
                info.Add(combat.enemyNow->name, GREEN);
                info.Add("��������!");
                combat.combatLog.AddLog(info);
                combat.enemyNow = enemyPokemonAlive[rand() % enemyPokemonAlive.size()];
                info.Add("�Է�");
                info.Add("�ɳ���");
                info.Add(combat.enemyNow->name, GREEN);
                combat.combatLog.AddLog(info);
			}
		}
	}
}

