#pragma once
#include "Pokemon.h"

class PokemonLib
{
public:
	vector<Pokemon*> pokemonInGame;	//上阵的宝可梦
	vector<Pokemon*> pokemonInLib;	//宝可梦背包
	PokemonLib();
	~PokemonLib();
    Text AddPokemon(Pokemon* p);
    bool DeletePokemon(Pokemon* p);
	Pokemon* CheckPokemon(int pokemonId);
	Pokemon* GetPokemonInGame(int index);	//start from 1
    Pokemon* GetPokemonInLib(int index);	//start from 1
	Text SwitchPokemon(int indexInLib, int indexInGame);	//交换上阵宝可梦和背包宝可梦
	Text AddPokemonToGame(int indexInLib);
	vector<Text> GetPokemonInGameInfo();
	vector<Text> GetPokemonInLibInfo();
	vector<Text> GetPokemonSellPrice();
	void Save();
    void Load();
};

