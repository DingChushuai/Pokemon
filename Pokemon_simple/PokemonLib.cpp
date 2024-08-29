#include "PokemonLib.h"
#pragma once

PokemonLib::PokemonLib()
{
}

PokemonLib::~PokemonLib()
{
}

void PokemonLib::AddPokemon(Pokemon p)
{
}

bool PokemonLib::DeletePokemon(Pokemon* p)
{
    return false;
}

Pokemon* PokemonLib::CheckPokemon(int pokemonId)
{
    return nullptr;
}

Pokemon* PokemonLib::GetPokemonInGame(int index)
{
    return nullptr;
}

Pokemon* PokemonLib::GetPokemonInLib(int index)
{
    return nullptr;
}

void PokemonLib::SwitchPokemon(int indexInLib, int indexInGame)
{
}

void PokemonLib::AddPokemonToGame(int indexInLib)
{
}

vector<Text> PokemonLib::GetPokemonInGameInfo()
{
    return vector<Text>();
}

vector<Text> PokemonLib::GetPokemonInLibInfo()
{
    return vector<Text>();
}

vector<Text> PokemonLib::GetPokemonSellPrice()
{
    return vector<Text>();
}

void PokemonLib::Save()
{
}

void PokemonLib::Load()
{
}
