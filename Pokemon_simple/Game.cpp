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
					vector<Text> pokemonsInGame = pokemonLib.GetPokemonInGameInfo();
					if (pokemonsInGame.size() == 0)
					{
                        Text("\n��Ķ�����û�б����Σ����Ȼ�ȡһֻ������!\n", RED, GRAY).Print();
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
                        Text("\n��ı�����û�е��ߣ����Ȼ�ȡһЩ����!\n", RED, GRAY).Print();
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
						Text("\n��Ķ�����û�б����Σ����Ȼ�ȡһֻ������!\n", RED, GRAY).Print();
                        command.Pause();
                        gameSenceStack.pop_back();
						break;
					}
					if (pokemonsInLib.size() == 0)
					{
						Text("\n��Ĳֿ���û�б����Σ����ȡ���౦���κ�����������!\n", RED, GRAY).Print();
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
							pokemonLib.SwitchPokemon(indexInLib, indexInGame);
							string pokemonName1 = "[" + pokemonLib.GetPokemonInLib(indexInLib)->name + "]";
							string pokemonName2 = "[" + pokemonLib.GetPokemonInGame(indexInGame)->name + "]";
							Text info;
							info.Add("�ֿ��е�");
							info.Add(pokemonName1, GREEN);
							info.Add("������,");
							info.Add(pokemonName2, RED);
							info.Add("�ѽ���ֿ�.\n");
							log.AddLog(info);
						}
						else
						{
							pokemonLib.AddPokemonToGame(indexInLib);
							string pokemonName1 = "[" + pokemonLib.GetPokemonInLib(indexInLib)->name + "]";
							Text info;
							info.Add("�ֿ��е�");
							info.Add(pokemonName1, GREEN);
							info.Add("������.\n");
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
                    Text("\n���Ǯ�����ˣ�����ȥ׬��Ǯ��!\n", RED).Print();
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
					log.AddLog(Text("��Ľ�������Ѹ���Ϊ: " + to_string(money), YELLOW));
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
	//���Ըı�NPC״̬������ɹ�����true
	/*
	NPC�ı���߼�����:
	�Ȼ�ȡNPC�ĵ�ǰ״̬npc.GetState()
	��ȡNPC��״̬����stateAction[0]
	����NPC��״̬����,�Ͷ�Ӧ��״̬����stateAction[1 ~ n]
    ����״̬���ͺͶ�Ӧ�����ж��Ƿ���Ըı�NPC״̬
	һ��8�ֿ��ܵĸı䷽ʽ,ÿһ����Ҫ���ò�ͬ����ͺ���,��README.md������ϸ˵��
	�����������е�ĳһ��Ӧ������ж�,�ڶ�Ӧλ��д��"//CAN NOT FINISH" ע��,�һᲹȫ
	������Ըı�NPC״̬,��npc��state��ΪstateNext.���ҷ���true(�����˿��ܵ��ƶ�npc��λ��)
    ���򷵻�false
	*/
	return false;
}

