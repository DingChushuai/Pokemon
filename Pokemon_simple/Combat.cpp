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
    text.Add("你换上了 ");
	text.Add(pokemon->name, GREEN);
	pokemonNow->buff = { 0 };
    pokemonNow = pokemon;
    return text;
}

bool Combat::TryToEscape()
{
	/*
	在通常情况下,逃走的成功率计算公式为 F = (A * 32) / B + 30 * C。其中：
	A为逃走方宝可梦的当前速度,计算飞毛腿等速度加成效果。
	B为对方宝可梦的当前速度除以4再对256取余。
	C为本次对战中逃走方失败的逃走次数+1。
	对于幽灵属性的宝可梦,无论速度多高,一定能在野生对战中逃走,无论对方的特性是什么以及自己处于什么状态。
	对于那些非幽灵属性的宝可梦,若F大于255,则逃走成功。否则在0到255之间生成一个随机数D。若D小于F则逃走成功,否则逃走失败。
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
	myPokemonInfo.Add(" 状态:" + pokemonNow->GetStatuName(pokemonNow->statu) + "\n");
	texts.push_back(myPokemonInfo);

	Text enemyPokemonInfo;
	enemyPokemonInfo.Add("对手的 ");
	enemyPokemonInfo.Add(enemyNow->name, GREEN);
	enemyPokemonInfo.Add(" Level:");
	enemyPokemonInfo.Add(to_string(enemyNow->level), YELLOW);
	enemyPokemonInfo.Add(" HP:");
	enemyPokemonInfo.Add(to_string(enemyNow->attribute.hp) + "/" + to_string(enemyNow->attribute.maxHp), YELLOW);
	enemyPokemonInfo.Add(" 状态:" + enemyNow->GetStatuName(enemyNow->statu) + "\n");
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
		info += skill->skillName + "  属性:" + skill->GetTypeName(skill->skillID);
		info += "  ";
		switch (skill->type)
		{
		case 0:
			info += "类型: 物理  ";
			break;
		case 1:
			info += "类型: 特殊  ";
			break;
		case 2:
			info += "类型: 变化  ";
			break;
		}
		info += "威力:" + to_string(skill->power) + "  PP: " + to_string(skill->PP);
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
