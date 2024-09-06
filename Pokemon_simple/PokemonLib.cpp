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
    info.Add("已进入仓库.");
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
        info.Add(po->name + 
            "  血量:" + to_string(po->attribute.hp) + "/" + to_string(po->attribute.maxHp)+ 
            "  状态: " + po->GetStatuName(po->statu) + 
            "  经验: " + to_string(po->experience) + "/" + to_string(po->experienceToNextLevel) + 
            "  等级: " + to_string(po->level)
        );
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
        info.Add(po->name +
            "  血量:" + to_string(po->attribute.hp) + "/" + to_string(po->attribute.maxHp) +
            "  状态: " + po->GetStatuName(po->statu) +
            "  经验: " + to_string(po->experience) + "/" + to_string(po->experienceToNextLevel) +
            "  等级: " + to_string(po->level)
        );
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
        sellInfo.Add(po->name + 
            "  血量:" + to_string(po->attribute.hp) + "/" + to_string(po->attribute.maxHp) +
            "  等级: " + to_string(po->level) +
            "  售卖价格: " + to_string(po->GetSellPrice())
        );
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
                ofs << pokemonInGame[i]->skills[j].skillID << "|" << pokemonInGame[i]->skills[j].skillName << "|" << pokemonInGame[i]->skills[j].skillDescription << "|" << pokemonInGame[i]->skills[j].type << "|"
                    << pokemonInGame[i]->skills[j].skillType << "|" << pokemonInGame[i]->skills[j].power << "|" << pokemonInGame[i]->skills[j].accuracy << "|" << pokemonInGame[i]->skills[j].PP << "|" << pokemonInGame[i]->skills[j].maxPP << "|"
                    << pokemonInGame[i]->skills[j].skillEffect << "|";
                       for (int k = 0; k < pokemonInGame[i]->skills[j].effectParam.size(); k++)
                       {
                           ofs<<pokemonInGame[i]->skills[j].effectParam[k]<<"\\";
                       }        
                       ofs << "|" << pokemonInGame[i]->skills[j].mustHit << "|" << pokemonInGame[i]->skills[j].priority;
            }
            ofs << endl;
    }
    for (int i = 0; i < pokemonInLib.size(); i++)
    {
        ofs << pokemonInLib[i]->ID << "," << pokemonInLib[i]->name << "," << pokemonInLib[i]->type.first << "," << pokemonInLib[i]->type.second << "," << pokemonInLib[i]->level
            << "," << pokemonInLib[i]->experience << "," << pokemonInLib[i]->experienceToNextLevel << "," << pokemonInLib[i]->statu << ","
            << pokemonInLib[i]->attribute.hp << "/" << pokemonInLib[i]->attribute.maxHp << "/" << pokemonInLib[i]->attribute.attack << "/" << pokemonInLib[i]->attribute.defense
            << "/" << pokemonInLib[i]->attribute.speed << "/" << pokemonInLib[i]->attribute.specialAttack << "/" << pokemonInLib[i]->attribute.specialDefense << "/" << pokemonInLib[i]->attribute.speed
            << "," << pokemonInLib[i]->evolutionLevel << "," << pokemonInLib[i]->evolutionID << "," << pokemonInLib[i]->captureRate << "," << pokemonInLib[i]->growthRate << ","
            << pokemonInLib[i]->basicExperience << ","
            << pokemonInLib[i]->ethnicValue.hp << "/" << pokemonInLib[i]->ethnicValue.attack << "/" << pokemonInLib[i]->ethnicValue.defense << "/" << pokemonInLib[i]->ethnicValue.specialAttack << "/"
            << pokemonInLib[i]->ethnicValue.specialDefense << "/" << pokemonInLib[i]->ethnicValue.speed << ","
            << pokemonInLib[i]->individualValue.hp << "/" << pokemonInLib[i]->individualValue.attack << "/" << pokemonInLib[i]->individualValue.defense << "/" << pokemonInLib[i]->individualValue.specialAttack << "/"
            << pokemonInLib[i]->individualValue.specialDefense << "/" << pokemonInLib[i]->individualValue.speed << ","
            << pokemonInLib[i]->basicValue.hp << "/" << pokemonInLib[i]->basicValue.attack << "/" << pokemonInLib[i]->basicValue.defense << "/" << pokemonInLib[i]->basicValue.specialAttack << "/"
            << pokemonInLib[i]->basicValue.specialDefense << "/" << pokemonInLib[i]->basicValue.speed << ",";

        for (int j = 0; j < pokemonInLib[i]->skills.size(); j++)
        {
            ofs << pokemonInLib[i]->skills[j].skillID << "|" << pokemonInLib[i]->skills[j].skillName << "|" << pokemonInLib[i]->skills[j].skillDescription << "|" << pokemonInLib[i]->skills[j].type << "|"
                << pokemonInLib[i]->skills[j].skillType << "|" << pokemonInLib[i]->skills[j].power << "|" << pokemonInLib[i]->skills[j].accuracy << "|" << pokemonInLib[i]->skills[j].PP << "|" << pokemonInLib[i]->skills[j].maxPP << "|"
                << pokemonInLib[i]->skills[j].skillEffect << "|";
            for (int k = 0; k < pokemonInLib[i]->skills[j].effectParam.size(); k++)
            {
                ofs << pokemonInLib[i]->skills[j].effectParam[k] << "\\";
            }
            ofs << "|" << pokemonInLib[i]->skills[j].mustHit << "|" << pokemonInLib[i]->skills[j].priority;
        }

        ofs << endl;

    }
    ofs.close();
}

void PokemonLib::Load()
{
    int count = 0;
    int k;
    ifstream ifs;
    ifs.open(POKEMONLIB_STATE_PATH, ios::in);
    string rea;
    vector<string>data;
    vector<string>attri, ethnic, individual, basic, skl;
    while (getline(ifs, rea))
    {
        data = Split(rea, ',');
        Pokemon* a = new Pokemon;
        a->ID = stoi(data[0]);
        a->name = data[1];
        a->type.first =(Type)stoi( data[2]);
        a->type.second = (Type)stoi(data[3]);
        a->level = stoi(data[4]);
        a->experience = stoi(data[5]);
        a->experienceToNextLevel = stoi(data[6]);
        k = stoi(data[7]);
        switch (k)
        {
        case 0:a->statu = Pokemon::None;
        case 1:a->statu = Pokemon::Poison;
        case 2:a->statu = Pokemon::Paralysis;
        case 3:a->statu = Pokemon::Burn;
        case 4:a->statu = Pokemon::Sleep;
        case 5:a->statu = Pokemon::Freeze;
        case 6:a->statu = Pokemon::Frostbite;
        }
        attri = Split(data[8], '/');
        a->attribute.hp = stoi(attri[0]);
        a->attribute.maxHp = stoi(attri[1]);
        a->attribute.attack = stoi(attri[2]);
        a->attribute.defense = stoi(attri[3]);
        a->attribute.speed = stoi(attri[4]);
        a->attribute.specialAttack = stoi(attri[5]);
        a->attribute.specialDefense= stoi(attri[6]);

        a->evolutionLevel = stoi(data[9]);
        a->evolutionID = stoi(data[10]);
        a->captureRate = stoi(data[11]);
        a->growthRate = stoi(data[12]);
        a->basicExperience = stoi(data[13]);
        
        ethnic = Split(data[14], '/');
        a->ethnicValue.hp = stoi(ethnic[0]);
        a->ethnicValue.attack = stoi(ethnic[1]);
        a->ethnicValue.defense = stoi(ethnic[2]);
        a->ethnicValue.defense = stoi(ethnic[3]);
        a->ethnicValue.specialAttack = stoi(ethnic[4]);
        a->ethnicValue.specialDefense = stoi(ethnic[5]);
        a->ethnicValue.speed = stoi(attri[6]);
        
        individual = Split(data[15], '/');
        a->individualValue.hp = stoi(individual[0]);
        a->individualValue.attack = stoi(individual[1]);
        a->individualValue.defense = stoi(individual[2]);
        a->individualValue.defense = stoi(individual[3]);
        a->individualValue.specialAttack = stoi(individual[4]);
        a->individualValue.specialDefense = stoi(individual[5]);
        a->individualValue.speed = stoi(individual[6]);

        basic = Split(data[16], '/');
        a->basicValue.hp = stoi(basic[0]);
        a->basicValue.attack = stoi(basic[1]);
        a->basicValue.defense = stoi(basic[2]);
        a->basicValue.defense = stoi(basic[3]);
        a->basicValue.specialAttack = stoi(basic[4]);
        a->basicValue.specialDefense = stoi(basic[5]);
        a->basicValue.speed = stoi(basic[6]);


        skl=Split(data[17],'/')
         
            count++;
        if (count > 6)     pokemonInLib.push_back(a);
        else  pokemonInGame.push_back(a);
    }
}
