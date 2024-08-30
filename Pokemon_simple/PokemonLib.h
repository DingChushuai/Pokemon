#pragma once
#include "Pokemon.h"

class PokemonLib
{
	vector<Pokemon> pokemonInGame;	//����ı�����
	vector<Pokemon> pokemonsInLib;	//�����α���
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

