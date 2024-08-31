#include "Combat.h"
#pragma once

void Combat::InitWildCombat(int id, int level, PokemonLib& pokemonLib)
{
}

void Combat::InitTrainerCombat(int battleId, PokemonLib& pokemonLib)
{
}

vector<Pokemon*> Combat::pokemonAvailable()
{
	return vector<Pokemon*>();
}

vector<Pokemon*> Combat::enemyAvailable()
{
	return vector<Pokemon*>();
}

vector<Text> Combat::PokemonAvailableText()
{
	return vector<Text>();
}

Text Combat::ChangePokemon(Pokemon* pokemon)
{
	return Text();
}

bool Combat::TryToEscape()
{
	return false;
}

vector<Text> Combat::ShowPokemonInfo()
{
	return vector<Text>();
}

bool Combat::IsTrainerBattle()
{
	return false;
}

bool Combat::IsWildBattle()
{
	return false;
}

void Combat::EndCombat()
{
}
