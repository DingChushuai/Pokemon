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
    Pokemon* temp = p1;
    pokemonInLib[indexInLib-1] = p2;
    pokemonInGame[indexInGame-1] = temp;
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
    pokemonInGame.push_back(GetPokemonInLib(indexInLib));
    pokemonInLib.erase(pokemonInLib.begin() + indexInLib - 1);
    Text info;
    info.Add("仓库中的");
    info.Add(pokemonName1, GREEN);
    info.Add("已上阵.\n");
    return info;
}

vector<Text> PokemonLib::GetPokemonInGameInfo()
{
    vector<Text> infos;
    for (auto& po : pokemonInGame)
    {
        Text info;
        info.Add(po->name, BLUE);
        info.Add(", 血量: ");
        info.Add(to_string(po->attribute.hp) + "/" + to_string(po->attribute.maxHp), RED);
        info.Add(", 状态: " + po->GetStatuName(po->statu));
        info.Add(", 经验: ");
        info.Add(to_string(po->experience) + "/" +to_string(po->experienceToNextLevel), GREEN);
        info.Add(", 等级: " + to_string(po->level));

        infos.push_back(info);
    }
    return infos;
}

vector<Text> PokemonLib::GetPokemonInLibInfo()
{
    vector<Text> infos;
    for (auto& po : pokemonInLib)
    {
        Text info;
        info.Add(po->name, BLUE);
        info.Add(", 血量: ");
        info.Add(to_string(po->attribute.hp) + "/" + to_string(po->attribute.maxHp), RED);
        info.Add(", 状态: " + po->GetStatuName(po->statu));
        info.Add(", 经验: ");
        info.Add(to_string(po->experience) + "/" + to_string(po->experienceToNextLevel), GREEN);
        info.Add(", 等级: " + to_string(po->level));

        infos.push_back(info);
    }
    return infos;
}

vector<Text> PokemonLib::GetPokemonSellPrice()
{
    vector<Text> info;

    for (auto po : pokemonInLib)
    {
        Text sellInfo;
        sellInfo.Add(po->name, BLUE);
        sellInfo.Add(", 等级: ");
        sellInfo.Add(to_string(po->level), MAGENTA);
        sellInfo.Add(", 售卖价格: ");
        sellInfo.Add(to_string(po->GetSellPrice()), CYAN);
        sellInfo.Add("\n");
        info.push_back(sellInfo);
        
    }
     return info;
}

void PokemonLib::Save()
{
    //TODO:
    //保存上阵中的宝可梦信息
    //保存库中的宝可梦信息
    //储存到PokemonLib_State中:POKEMONLIB_STATE_PATH
    //具体格式参考README.md
    //此函数相对麻烦
    //建议与Load函数一同完成
}

void PokemonLib::Load()
{
    //TODO:
    //加载宝可梦信息
    //与Save函数对应
    //详细信息查看Save函数
}
