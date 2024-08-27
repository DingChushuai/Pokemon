#pragma once
#include "Pokemon.h"

class PokemonLib
{
	vector<Pokemon> pokemonInGame;	//上阵的宝可梦
	vector<Pokemon> pokemonsInLib;	//宝可梦背包
public:
	PokemonLib();
	~PokemonLib();
};

