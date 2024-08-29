#pragma once
#include "Pokemon.h"

class PokemonLib
{
	vector<Pokemon> pokemonInGame;	//上阵的宝可梦
	vector<Pokemon> pokemonsInLib;	//宝可梦背包
public:
	PokemonLib();
	~PokemonLib();
    void AddPokemon(Pokemon p);
    bool DeletePokemon(Pokemon* p);
	Pokemon* CheckPokemon(int pokemonId);
	Pokemon* GetPokemonInGame(int index);	//start from 1
    Pokemon* GetPokemonInLib(int index);	//start from 1
	void SwitchPokemon(int indexInLib, int indexInGame);
	void AddPokemonToGame(int indexInLib);
	vector<Text> GetPokemonInGameInfo();
	vector<Text> GetPokemonInLibInfo();
	vector<Text> GetPokemonSellPrice();
	void Save();
    void Load();
};

