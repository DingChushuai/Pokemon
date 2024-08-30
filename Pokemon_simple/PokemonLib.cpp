#include "PokemonLib.h"
#pragma once

PokemonLib::PokemonLib()
{
    //do nothing
}

PokemonLib::~PokemonLib()
{
    //do nothing
}

Text PokemonLib::AddPokemon(Pokemon* p)
{
    if (p != nullptr)
    {
        if (pokemonInGame.size() < MAX_POKEMON_INGAME)
        {
            pokemonInGame.push_back(p);
            Text info;
            info.Add("[" + p->name + "]", GREEN);
            info.Add("已经上阵");
            return info;
        }
        else
        {
            pokemonInLib.push_back(p); 
            Text info;
            info.Add("[" + p->name + "]", GREEN);
            info.Add("已经存入宝可梦库");
            return info;
        }
    }

}

bool PokemonLib::DeletePokemon(Pokemon* p)
{
    if (p != nullptr)
    {
        for (auto pk : pokemonInLib)
        {
            if (pk == p)
            {
                pokemonInLib.erase(remove(pokemonInLib.begin(), pokemonInLib.end(), p), pokemonInLib.end());
                return true;
            }
        }
    }
    return false;
}

Pokemon* PokemonLib::CheckPokemon(int pokemonId)
{
    for (auto pk : pokemonInLib)
    {
        if (pk->ID == pokemonId)
        {
            return pk;
        }
    }
    return nullptr;
}

Pokemon* PokemonLib::GetPokemonInGame(int index)
{
    return pokemonInGame[index-1];
}

Pokemon* PokemonLib::GetPokemonInLib(int index)
{
    return pokemonInLib[index-1];
}

Text PokemonLib::SwitchPokemon(int indexInLib, int indexInGame)
{
    Pokemon* p1 = GetPokemonInLib(indexInLib); 
    Pokemon* p2 = GetPokemonInGame(indexInGame); 


    string pokemonName1 = "[" + p1->name + "]"; 
    string pokemonName2 = "[" + p2->name + "]"; 
    Text info; 
    info.Add("仓库中的"); 
    info.Add(pokemonName1, GREEN); 
    info.Add("已上阵,"); 
    info.Add(pokemonName2, RED); 
    info.Add("已进入仓库.\n");
    return info;
}

Text PokemonLib::AddPokemonToGame(int indexInLib)
{
    string pokemonName1 = "[" + GetPokemonInLib(indexInLib)->name + "]"; 
    Text info;
    info.Add("仓库中的");
    info.Add(pokemonName1, GREEN);
    info.Add("已上阵.\n");
    return info;
}

vector<Text> PokemonLib::GetPokemonInGameInfo()
{
    //TODO:
    //返回上阵中的宝可梦的简略信息
    //包括:名称,血量,状态,经验,等级
    //血量,经验类似 10/100
    return vector<Text>();
}

vector<Text> PokemonLib::GetPokemonInLibInfo()
{
    //TODO:
    //返回库中的宝可梦的简略信息
    //包括:名称,血量,状态,经验,等级
    //血量,经验类似 10/100
    return vector<Text>();
}

vector<Text> PokemonLib::GetPokemonSellPrice()
{
    //TODO:
    //返回库中的宝可梦的售卖信息
    //包括:名称,等级,售卖价格
    return vector<Text>();
}

void PokemonLib::Save()
{
}

void PokemonLib::Load()
{
}
