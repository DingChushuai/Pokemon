#include "Combat.h"
#include <fstream>
using namespace std;
#pragma once

Combat::Combat()
{
	damageTable.resize(18, vector<float>(18));
	for (int i = 0; i < 18; i++)
	{
		for (int j = 0; j < 18; j++) damageTable[i][j] = 1.0;
	}
	vector<pair<int, int>> x2, xh, x0;
	x2 = { {1,0},{2,1},{13,1}, {17,1}, {5,2},{12,2} ,{14,2}, {4,3},{13,3},{},{},{} };
	xh = { {5,1},{6,1}, };
	x0 = { {7,0},{4,2} };
	for (pair<int, int> x : x2)
	{
		damageTable[x.first][x.second] = 2.0;
	}
	for (pair<int, int> x : xh)
	{
		damageTable[x.first][x.second] = 0.5;
	}
	for (pair<int, int> x : x0)
	{
		damageTable[x.first][x.second] = 0.0;
	}
}

void Combat::InitWildCombat(int id, int level, PokemonLib* pokemonLib)
{
	myPokemons.clear();
    enemyPokemons.clear();
	this->pokemonLib = pokemonLib;
	for (int i = 0; i < pokemonLib->pokemonInGame.size(); i++) 
	{
		Pokemon* pokemon = new Pokemon(*pokemonLib->GetPokemonInGame(i + 1));
		myPokemons.push_back(pokemon);
	}
	Pokemon* enemyPokemon = new Pokemon(id,level);
    enemyPokemons.push_back(enemyPokemon);
    pokemonNow = myPokemons[0];
    enemyNow = enemyPokemons[0];
	isTrainer = false;
	escapeFailedTimes = 0;
	combatLog.clearLog();
    beaten.clear();
	Text text;
	text.Add("��������һֻҰ����");
    text.Add(enemyNow->name,YELLOW);
    text.Add("! ս����ʼ!");
	combatLog.AddLog(text);
	text.Clear();
	text.Add("���ɳ���");
    text.Add(pokemonNow->name,YELLOW);
    text.Add("������!");
    combatLog.AddLog(text);

}

void Combat::InitTrainerCombat(int battleId, PokemonLib* pokemonLib)
{
	myPokemons.clear();
	enemyPokemons.clear();
	this->pokemonLib = pokemonLib;
	for (int i = 0; i < pokemonLib->pokemonInGame.size(); i++)
	{
		Pokemon* pokemon = new Pokemon(*pokemonLib->GetPokemonInGame(i + 1));
		myPokemons.push_back(pokemon);
	}
	string trainerName = "";
	ifstream battleFile(BATTLE_INFO_PATH);
	string line;
	while (getline(battleFile, line))
	{
		vector<string> info = Split(line, ',');
		if (stoi(info[0]) == battleId)
		{
            trainerName = info[1];
			vector<string> enemyInfo = Split(info[2], '/');
			for (auto& pokemonInfo : enemyInfo)
			{
                vector<string> pokemonInfoDetail = Split(pokemonInfo, '|');
                Pokemon* pokemon = new Pokemon(stoi(pokemonInfoDetail[0]), stoi(pokemonInfoDetail[1]));
                enemyPokemons.push_back(pokemon);
			}
            break;
		}
	}
	battleFile.close();
	pokemonNow = myPokemons[0];
	enemyNow = enemyPokemons[0];
	isTrainer = true;
	escapeFailedTimes = 0;
	combatLog.clearLog();
	beaten.clear();
	Text text;
	text.Add("����");
    text.Add(trainerName, YELLOW);
	text.Add("��ս����ʼ!");
	combatLog.AddLog(text);
	text.Clear();
	text.Add("���");
	text.Add(pokemonNow->name, YELLOW);
	text.Add("������!");
	combatLog.AddLog(text); 
	text.Clear();
	text.Add("�Է���");
	text.Add(enemyNow->name, YELLOW);
	text.Add("������!");
	combatLog.AddLog(text);
}

vector<Pokemon*> Combat::pokemonAvailable()
{
	vector<Pokemon*> available;
	for (auto& pokemon : myPokemons)
	{
		if (pokemon->attribute.hp > 0) available.push_back(pokemon);
	}
    return available;
}

vector<Pokemon*> Combat::enemyAvailable()
{
	vector<Pokemon*> available;
	for (auto& pokemon : enemyPokemons)
	{
        if (pokemon->attribute.hp > 0) available.push_back(pokemon);
	}
    return available;
}

vector<Text> Combat::PokemonAvailableText()
{
	vector<Pokemon*> available;
	for (auto& pokemon : myPokemons)
	{
		if (pokemon->attribute.hp > 0) available.push_back(pokemon);
	}
	vector<Text> texts;
	for (auto& pokemon : available)
	{
		string text;
		text += pokemon->name;
		text += " Lv.";
		text += to_string(pokemon->level);
		text += " HP:";
		text += to_string(pokemon->attribute.hp) + "/" + to_string(pokemon->attribute.maxHp);
		text += pokemon->GetStatuName(pokemon->statu);
		texts.push_back(Text(text));
	}
    return texts;
}

Text Combat::ChangePokemon(Pokemon* pokemon)
{
    Text text;
    text.Add("�㻻���� ");
	text.Add(pokemon->name, GREEN);
	pokemonNow->buff = { 0 };
    pokemonNow = pokemon;
    return text;
}

bool Combat::TryToEscape()
{
	/*
	��ͨ�������,���ߵĳɹ��ʼ��㹫ʽΪ F = (A * 32) / B + 30 * C�����У�
	AΪ���߷������εĵ�ǰ�ٶ�,�����ë�ȵ��ٶȼӳ�Ч����
	BΪ�Է������εĵ�ǰ�ٶȳ���4�ٶ�256ȡ�ࡣ
	CΪ���ζ�ս�����߷�ʧ�ܵ����ߴ���+1��
	�����������Եı�����,�����ٶȶ��,һ������Ұ����ս������,���۶Է���������ʲô�Լ��Լ�����ʲô״̬��
	������Щ���������Եı�����,��F����255,�����߳ɹ���������0��255֮������һ�������D����DС��F�����߳ɹ�,��������ʧ�ܡ�
	*/
	if(IsWildBattle())
		if(pokemonNow->type.first ==Type::GHOST || pokemonNow->type.second == Type::GHOST) return true;
	int A = pokemonNow->attribute.speed;
	A *= pokemonNow->GetBuffValue(pokemonNow->buff.speed); 
    int B = enemyNow->attribute.speed;
	B *= enemyNow->GetBuffValue(enemyNow->buff.speed);
    B /= 4;
    B %= 256;
    int C = escapeFailedTimes + 1;
    int F = (A * 32) / B + 30 * C;
    if(F > 255) return true;
    int D = rand() % 256;
    if(D < F) return true;
    escapeFailedTimes++;
	return false;
}

vector<Text> Combat::ShowPokemonInfo()
{
	vector<Text> texts;

	Text myPokemonInfo;
	myPokemonInfo.Add("��� ");
	myPokemonInfo.Add(pokemonNow->name, GREEN);
	myPokemonInfo.Add(" Level:");
	myPokemonInfo.Add(to_string(pokemonNow->level), YELLOW);
	myPokemonInfo.Add(" HP:");
	myPokemonInfo.Add(to_string(pokemonNow->attribute.hp) + "/" + to_string(pokemonNow->attribute.maxHp), YELLOW);
	myPokemonInfo.Add(" ״̬:" + pokemonNow->GetStatuName(pokemonNow->statu) + "\n");
	texts.push_back(myPokemonInfo);

	Text enemyPokemonInfo;
	enemyPokemonInfo.Add("���ֵ� ");
	enemyPokemonInfo.Add(enemyNow->name, GREEN);
	enemyPokemonInfo.Add(" Level:");
	enemyPokemonInfo.Add(to_string(enemyNow->level), YELLOW);
	enemyPokemonInfo.Add(" HP:");
	enemyPokemonInfo.Add(to_string(enemyNow->attribute.hp) + "/" + to_string(enemyNow->attribute.maxHp), YELLOW);
	enemyPokemonInfo.Add(" ״̬:" + enemyNow->GetStatuName(enemyNow->statu) + "\n");
	texts.push_back(enemyPokemonInfo);

	return texts;
}

vector<Text> Combat::ShowPokemonSkill()
{
	vector<Text> skillTexts;

	vector<Skill*> skills;
	for (int i = 0; i < pokemonNow->skills.size(); i++)
	{
		skills.push_back(&pokemonNow->skills[i]);
	}

	for (Skill* skill : skills)
	{
		string info="";
		info += skill->skillName + "  ����:" + skill->GetTypeName(skill->skillID);
		info += "  ";
		switch (skill->type)
		{
		case 0:
			info += "����: ����  ";
			break;
		case 1:
			info += "����: ����  ";
			break;
		case 2:
			info += "����: �仯  ";
			break;
		}
		info += "����:" + to_string(skill->power) + "  PP: " + to_string(skill->PP);
		skillTexts.push_back(Text(info));
	}

	return skillTexts;
}

bool Combat::IsTrainerBattle()
{
	return isTrainer;
}

bool Combat::IsWildBattle()
{
	return !isTrainer;
}

int Combat::GetExperienceFromBattle(Pokemon* beatenPokemon)
{
	float experience = beatenPokemon->GetBasicExperience();
	if(IsTrainerBattle()) experience *= 1.5f;
	experience *= 1.5f;
	experience *= beatenPokemon->level;
	int s = pokemonAvailable().size();
	if (s == 0) s = 1;
	experience /= s;
	experience /= 7;
    return (int)experience;
}

void Combat::EndCombat()
{
 	for (int i = 0; i < beaten.size(); i++)
	{
		pair<Pokemon*, Pokemon*> battleResult = beaten[i];
		combatLog.AddLog(battleResult.first->GetExperience(GetExperienceFromBattle(battleResult.second)));
		battleResult.first->AddBasicValue(battleResult.second->basicValue);
	}
	for (int i = 0; i < myPokemons.size(); i++)
	{
		pokemonLib->pokemonInGame[i]->attribute.hp = myPokemons[i]->attribute.hp;
		pokemonLib->pokemonInGame[i]->statu = myPokemons[i]->statu;
		pokemonLib->pokemonInGame[i]->basicValue = myPokemons[i]->basicValue;
		pokemonLib->pokemonInGame[i]->experience = myPokemons[i]->experience;
		for (int j = 0; j < myPokemons[i]->skills.size(); j++)
		{
            pokemonLib->pokemonInGame[i]->skills[j].PP = myPokemons[i]->skills[j].PP;
		}
	}
	myPokemons.clear();
	enemyPokemons.clear();
	pokemonNow = nullptr;
	enemyNow = nullptr;
	isTrainer = false;
	escapeFailedTimes = 0;
	beaten.clear();
	combatLog.clearLog();
}
