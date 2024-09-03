#include "Combat.h"
#include <fstream>
using namespace std;
#pragma once

void Combat::InitWildCombat(int id, int level, PokemonLib* pokemonLib)
{
	myPokemons.clear();
    enemyPokemons.clear();
	this->pokemonLib = pokemonLib;
	for (int i = 0; i < MAX_POKEMON_INGAME; i++)
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
	for (int i = 0; i < MAX_POKEMON_INGAME; i++)
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
		Text text;
		text.Add(pokemon->name, YELLOW);
		text.Add(" Lv.");
		text.Add(to_string(pokemon->level), YELLOW);
		text.Add(" HP:");
		text.Add(to_string(pokemon->attribute.hp) + "/" + to_string(pokemon->attribute.maxHp), YELLOW);
		text.Add(pokemon->GetStatuName(pokemon->statu), CYAN);
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
	��ͨ������£����ߵĳɹ��ʼ��㹫ʽΪ F = (A * 32) / B + 30 * C�����У�
	AΪ���߷������εĵ�ǰ�ٶȣ������ë�ȵ��ٶȼӳ�Ч����
	BΪ�Է������εĵ�ǰ�ٶȳ���4�ٶ�256ȡ�ࡣ
	CΪ���ζ�ս�����߷�ʧ�ܵ����ߴ���+1��
	�����������Եı����Σ������ٶȶ�ߣ�һ������Ұ����ս�����ߣ����۶Է���������ʲô�Լ��Լ�����ʲô״̬��
	������Щ���������Եı����Σ���F����255�������߳ɹ���������0��255֮������һ�������D����DС��F�����߳ɹ�����������ʧ�ܡ�
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
	texts.push_back(myPokemonInfo);

	Text enemyPokemonInfo;
	enemyPokemonInfo.Add("���ֵ� ");
	enemyPokemonInfo.Add(enemyNow->name, GREEN);
	enemyPokemonInfo.Add(" Level:");
	enemyPokemonInfo.Add(to_string(enemyNow->level), YELLOW);
	enemyPokemonInfo.Add(" HP:");
	enemyPokemonInfo.Add(to_string(enemyNow->attribute.hp) + "/" + to_string(enemyNow->attribute.maxHp), YELLOW);
	texts.push_back(enemyPokemonInfo);

	return texts;
}

vector<Text> Combat::ShowPokemonSkill()
{
	vector<Text> skillTexts;
	vector<Skill>& skills = pokemonNow->skills;

	for (Skill& skill : skills)
	{
		Text text;
		text.Add(skill.skillName, GREEN);
		text.Add(": ");
		text.Add("����: ");
		text.Add(skill.GetTypeName(skill.skillID), CYAN);
		text.Add(", ");
		switch (skill.type)
		{
		case 0:
			text.Add("����: ����", MAGENTA);
			break;
		case 1:
			text.Add("����: ����", MAGENTA);
			break;
		case 2:
			text.Add("����: �仯", MAGENTA);
			break;
		}
		text.Add(", ");
		text.Add("����:");
		text.Add(to_string(skill.power), YELLOW);
		text.Add(", ");
		text.Add("PP: ");
		text.Add(to_string(skill.PP), YELLOW);

		// ��Text������ӵ�skillTexts������
		skillTexts.push_back(text);
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
	experience /= s;
	experience /= 7;
    return (int)experience;
}

void Combat::EndCombat()
{
	myPokemons.clear();
	enemyPokemons.clear();
	pokemonNow = nullptr;
	enemyNow = nullptr;
	isTrainer = false;
	escapeFailedTimes = 0;
	beaten.clear();
	combatLog.clearLog();
	//To do:
	//������ͻ�õĻ��������������Ӧ������
	//���ս����¼(��ȡ����)
	//�ش������ε�Ѫ��,״̬,����pp,��������
}
