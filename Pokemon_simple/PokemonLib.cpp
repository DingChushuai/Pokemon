#include "PokemonLib.h"
#pragma once
#include<fstream>
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
    vector<Text> infos;
    for (auto& po : pokemonInGame)
    {
        Text info;
        info.Add(po->name, BLUE);
        info.Add(", Ѫ��: ");
        info.Add(to_string(po->attribute.hp) + "/" + to_string(po->attribute.maxHp), RED);
        info.Add(", ״̬: " + po->GetStatuName(po->statu));
        info.Add(", ����: ");
        info.Add(to_string(po->experience) + "/" +to_string(po->experienceToNextLevel), GREEN);
        info.Add(", �ȼ�: " + to_string(po->level));

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
        info.Add(", Ѫ��: ");
        info.Add(to_string(po->attribute.hp) + "/" + to_string(po->attribute.maxHp), RED);
        info.Add(", ״̬: " + po->GetStatuName(po->statu));
        info.Add(", ����: ");
        info.Add(to_string(po->experience) + "/" + to_string(po->experienceToNextLevel), GREEN);
        info.Add(", �ȼ�: " + to_string(po->level));

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
        sellInfo.Add(", �ȼ�: ");
        sellInfo.Add(to_string(po->level), MAGENTA);
        sellInfo.Add(", �����۸�: ");
        sellInfo.Add(to_string(po->GetSellPrice()), CYAN);
        sellInfo.Add("\n");
        info.push_back(sellInfo);
        
    }
     return info;
}

void PokemonLib::Save()
{
    ofstream ofs;
    ofs.open(POKEMONLIB_STATE_PATH, ios::out);
    for (int i = 0; i < pokemonInGame.size(); i++)
    {
        ofs << pokemonInGame[i]->ID << "," << pokemonInGame[i]->name << "," << pokemonInGame[i]->type.first << "," << pokemonInGame[i]->type.second << "," << pokemonInGame[i]->level
            << "," << pokemonInGame[i]->experience << "," << pokemonInGame[i]->experienceToNextLevel << "," << pokemonInGame[i]->statu << ","
            << pokemonInGame[i]->attribute.hp << "/" << pokemonInGame[i]->attribute.maxHp << "/" << pokemonInGame[i]->attribute.attack << "/" << pokemonInGame[i]->attribute.defense
            << "/" << pokemonInGame[i]->attribute.speed << "/" << pokemonInGame[i]->attribute.specialAttack << "/" << pokemonInGame[i]->attribute.specialDefense << "/" << pokemonInGame[i]->attribute.speed
            << "," << pokemonInGame[i]->evolutionLevel << "," << pokemonInGame[i]->evolutionID << "," << pokemonInGame[i]->captureRate << "," << pokemonInGame[i]->growthRate << ","
            << pokemonInGame[i]->basicExperience << ","
            << pokemonInGame[i]->ethnicValue.hp << "/" << pokemonInGame[i]->ethnicValue.attack << "/" << pokemonInGame[i]->ethnicValue.defense << "/" << pokemonInGame[i]->ethnicValue.specialAttack << "/"
            << pokemonInGame[i]->ethnicValue.specialDefense << "/" << pokemonInGame[i]->ethnicValue.speed << ","
            << pokemonInGame[i]->individualValue.hp << "/" << pokemonInGame[i]->individualValue.attack << "/" << pokemonInGame[i]->individualValue.defense << "/" << pokemonInGame[i]->individualValue.specialAttack << "/"
            << pokemonInGame[i]->individualValue.specialDefense << "/" << pokemonInGame[i]->individualValue.speed << ","
            << pokemonInGame[i]->basicValue.hp << "/" << pokemonInGame[i]->basicValue.attack << "/" << pokemonInGame[i]->basicValue.defense << "/" << pokemonInGame[i]->basicValue.specialAttack << "/"
            << pokemonInGame[i]->basicValue.specialDefense << "/" << pokemonInGame[i]->basicValue.speed << ",";
            
            for (int j = 0; j < pokemonInGame[i]->skills.size(); j++)
            {
               
            }




    }
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
    ifstream ifs;
    ifs.open(POKEMONLIB_STATE_PATH, ios::in);
    //TODO:
    //���ر�������Ϣ
    //��Save������Ӧ
    //��ϸ��Ϣ�鿴Save����
}
