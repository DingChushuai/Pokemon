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
            info.Add("�Ѿ�����");
            return info;
        }
        else
        {
            pokemonInLib.push_back(p); 
            Text info;
            info.Add("[" + p->name + "]", GREEN);
            info.Add("�Ѿ����뱦���ο�");
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
    info.Add("�ֿ��е�"); 
    info.Add(pokemonName1, GREEN); 
    info.Add("������,"); 
    info.Add(pokemonName2, RED); 
    info.Add("�ѽ���ֿ�.\n");
    return info;
}

Text PokemonLib::AddPokemonToGame(int indexInLib)
{
    string pokemonName1 = "[" + GetPokemonInLib(indexInLib)->name + "]"; 
    pokemonInGame.push_back(GetPokemonInLib(indexInLib));
    pokemonInLib.erase(pokemonInLib.begin() + indexInLib - 1);
    Text info;
    info.Add("�ֿ��е�");
    info.Add(pokemonName1, GREEN);
    info.Add("������.\n");
    return info;
}

vector<Text> PokemonLib::GetPokemonInGameInfo()
{
    //TODO:
    //���������еı����εļ�����Ϣ
    //����:����,Ѫ��,״̬,����,�ȼ�
    //Ѫ��,�������� 10/100
    return vector<Text>();
}

vector<Text> PokemonLib::GetPokemonInLibInfo()
{
    //TODO:
    //���ؿ��еı����εļ�����Ϣ
    //����:����,Ѫ��,״̬,����,�ȼ�
    //Ѫ��,�������� 10/100
    return vector<Text>();
}

vector<Text> PokemonLib::GetPokemonSellPrice()
{
    //TODO:
    //���ؿ��еı����ε�������Ϣ
    //����:����,�ȼ�,�����۸�
    return vector<Text>();
}

void PokemonLib::Save()
{
    //TODO:
    //���������еı�������Ϣ
    //������еı�������Ϣ
    //���浽PokemonLib_State��:POKEMONLIB_STATE_PATH
    //�����ʽ�ο�README.md
    //�˺�������鷳
    //������Load����һͬ���
}

void PokemonLib::Load()
{
    //TODO:
    //���ر�������Ϣ
    //��Save������Ӧ
    //��ϸ��Ϣ�鿴Save����
}
