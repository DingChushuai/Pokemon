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
		//TODO:
		//���ر����ε�����,�ȼ�,Ѫ��, ״̬
	}
    return texts;
}

Text Combat::ChangePokemon(Pokemon* pokemon)
{
	//TODO:
	//�л�������
	//�޸�pokemonNow,���ǰһ�������ε�buff
	//�����л������ε�ս����־�ı�
    return Text();
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
	//TODO:
	//��ʾ��ǰ����˫���ı�������Ϣ
	//��������,�ȼ�,Ѫ��,״̬

	return vector<Text>();
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
	//TODO:
	//�����б���״̬����
	//������ͻ�õĻ��������������Ӧ������
	//���ս����¼(��ȡ����)
	//�ش������ε�Ѫ��,״̬,����pp,��������
	//(������)��ս��������,���±����εľ���,�ȼ�
}
