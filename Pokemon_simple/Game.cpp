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

/*
const enum GameSence
{
	START_MENU = 0, //��ʼ�˵�:to GAME GAMEOVER
	GAME,       //��Ϸ������:to SETTING POKEMON_LIB BACKPACK POKEMON_CENTER SHOP COMBAT DEBUG
	SETTING,    //���ý���
	POKEMON_LIB,    //�����ο����:to POKEMON_INFO
	POKEMON_INFO,   //��������Ϣ����
	BACKPACK,       //��������
	POKEMON_CENTER, //���������Ľ���
	SHOP,           //�̵����:to SHOOSE_BUY_OR_SELL
	SHOOSE_BUY_OR_SELL, //ѡ�������۽���: to BUY_ITEM SELL_POKEMON SELL_ITEM
	BUY_ITEM,
	SELL_POKEMON,
	SELL_ITEM,
	COMBAT,         //ս������
	DEBUG           //���Խ���
};
*/

void Game::Run()
{
	while (gameSenceStack.empty() == false)
	{
		ClearScreen();
		cout<< "GameScence: " << gameSence << endl;
		gameSence= gameSenceStack.back();
		soundPlayer.AdjustMusic(gameSence);
		sceneDrawer.draw(gameSence, &money, currentMap, &log, &combat);
		switch (gameSence)
		{
			case START_MENU:
			{
				vector<Text> Menu;
				Menu.push_back(Text("1. ��ʼ����Ϸ\n"));
				Menu.push_back(Text("2. ������Ϸ  \n"));
				Menu.push_back(Text("3. �˳���Ϸ  \n"));
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
				Menu.push_back(Text("1. ������Ϸ\n"));
				Menu.push_back(Text("2. ������Ϸ\n"));
				Menu.push_back(Text("3. ���ر���\n"));
				Menu.push_back(Text("4. ���沢�˳�\n"));
				Menu.push_back(Text("5. �������˳�\n"));
				int choice = command.chooseFromList(Menu);
				if (choice == 1)
				{
					Save();
					Text("��Ϸ�ѱ���", GREEN, CYAN).Print();
					log.AddLog(Text("��ǰ�����ѱ���!", GREEN));
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
					options.push_back(Text("1. �������\n"));
					options.push_back(Text("2. ��������\n"));
					options.push_back(Text("3. �����ֿ��еı�����\n"));
					int choice = command.chooseFromList(options);
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
                int choice = command.chooseFromList(props);
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
                int choice = command.chooseFromList(pokemonNames);
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
				gameSenceStack.pop_back();
                break;
			}
		}
	}
}

void Game::Init()
{
}

void Game::Load()
{
}

void Game::Save()
{
}

void Game::ActOnMap()
{

}

void Game::UseProp(Prop* prop)
{
}

