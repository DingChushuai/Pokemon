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
	text.Add("你遇到了一只野生的");
    text.Add(enemyNow->name,YELLOW);
    text.Add("! 战斗开始!");
	combatLog.AddLog(text);
	text.Clear();
	text.Add("你派出的");
    text.Add(pokemonNow->name,YELLOW);
    text.Add("已上阵!");
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
	text.Add("你与");
    text.Add(trainerName, YELLOW);
	text.Add("的战斗开始!");
	combatLog.AddLog(text);
	text.Clear();
	text.Add("你的");
	text.Add(pokemonNow->name, YELLOW);
	text.Add("已上阵!");
	combatLog.AddLog(text); 
	text.Clear();
	text.Add("对方的");
	text.Add(enemyNow->name, YELLOW);
	text.Add("已上阵!");
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
    text.Add("你换上了 ");
	text.Add(pokemon->name, GREEN);
	pokemonNow->buff = { 0 };
    pokemonNow = pokemon;
    return text;
}

bool Combat::TryToEscape()
{
	/*
	在通常情况下，逃走的成功率计算公式为 F = (A * 32) / B + 30 * C。其中：
	A为逃走方宝可梦的当前速度，计算飞毛腿等速度加成效果。
	B为对方宝可梦的当前速度除以4再对256取余。
	C为本次对战中逃走方失败的逃走次数+1。
	对于幽灵属性的宝可梦，无论速度多高，一定能在野生对战中逃走，无论对方的特性是什么以及自己处于什么状态。
	对于那些非幽灵属性的宝可梦，若F大于255，则逃走成功。否则在0到255之间生成一个随机数D。若D小于F则逃走成功，否则逃走失败。
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
	myPokemonInfo.Add("你的 ");
	myPokemonInfo.Add(pokemonNow->name, GREEN);
	myPokemonInfo.Add(" Level:");
	myPokemonInfo.Add(to_string(pokemonNow->level), YELLOW);
	myPokemonInfo.Add(" HP:");
	myPokemonInfo.Add(to_string(pokemonNow->attribute.hp) + "/" + to_string(pokemonNow->attribute.maxHp), YELLOW);
	texts.push_back(myPokemonInfo);

	Text enemyPokemonInfo;
	enemyPokemonInfo.Add("对手的 ");
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
		text.Add("属性: ");
		text.Add(skill.GetTypeName(skill.skillID), CYAN);
		text.Add(", ");
		switch (skill.type)
		{
		case 0:
			text.Add("类型: 物理", MAGENTA);
			break;
		case 1:
			text.Add("类型: 特殊", MAGENTA);
			break;
		case 2:
			text.Add("类型: 变化", MAGENTA);
			break;
		}
		text.Add(", ");
		text.Add("威力:");
		text.Add(to_string(skill.power), YELLOW);
		text.Add(", ");
		text.Add("PP: ");
		text.Add(to_string(skill.PP), YELLOW);

		// 将Text对象添加到skillTexts向量中
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
	//将经验和获得的基础点数分配给对应宝可梦
	//添加战斗记录(获取经验)
	//回传宝可梦的血量,状态,技能pp,基础点数
}
