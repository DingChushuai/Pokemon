#pragma once
#include "Pokemon.h"

class PokemonLib
{
	vector<Pokemon*> pokemonInGame;	//����ı�����
	vector<Pokemon*> pokemonInLib;	//�����α���
public:
	PokemonLib();
	~PokemonLib();
    Text AddPokemon(Pokemon* p);
    bool DeletePokemon(Pokemon* p);
	Pokemon* CheckPokemon(int pokemonId);
	Pokemon* GetPokemonInGame(int index);	//start from 1
    Pokemon* GetPokemonInLib(int index);	//start from 1
	Text SwitchPokemon(int indexInLib, int indexInGame);
	Text AddPokemonToGame(int indexInLib);
	vector<Text> GetPokemonInGameInfo();
	vector<Text> GetPokemonInLibInfo();
	vector<Text> GetPokemonSellPrice();
	void Save();
    void Load();
};

