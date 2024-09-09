#include "Combat.h"
#include <fstream>
#include "SoundPlayer.h"
SoundPlayer s;
using namespace std;
#pragma once

Combat::Combat()
{
	//固定的属性相克表,二维的表格,横坐标是防御方的类型,纵坐标是攻击方的类型,表格中的值是攻击方对防御方的伤害倍率
	damageTable.resize(18, vector<float>(18));
	for (int i = 0; i < 18; i++)
	{
		for (int j = 0; j < 18; j++) damageTable[i][j] = 1.0;
	}
	vector<pair<int, int>> x2, xh, x0; //x2为2倍伤害,xh为0.5倍伤害,x0为0倍伤害
	x2 = { {0,1},{1,2},{1,13}, {1,17}, {2,5},{2,12} ,{2,14}, {3,4},{3,13},{4,10},{4,11},{4,14},{5,1},{5,4},{5,8},{5,10},{5,11},{6,2},{6,5},{6,9},{7,7},{7,17},{8,1},{8,4},{8,9},{9,4},{9,5},{9,10},{10,11},{10,12},{11,2},{11,3},{11,6},{11,9},{11,14},{12,4},{13,6},{13,7},{13,16},{14,1},{14,5},{14,8},{14,9},{15,14},{15,15},{15,17},{16,1},{16,6},{16,17},{17,3},{17,8} };
	xh = { {1,1},{1,6},{1,16},{2,1},{2,6},{2,11},{3,1},{3,3},{3,6},{3,11},{3,17},{4,3},{4,5},{5,0},{5,2},{5,3},{5,9},{6,1},{6,4},{6,11},{7,3},{7,6},{8,0},{8,2},{8,5},{8,6},{8,8},{8,11},{8,13},{8,14},{8,15},{8,17},{9,6},{9,8},{9,9},{9,11},{9,14},{9,17},{10,8},{10,9},{10,10},{10,14},{11,4},{11,10},{11,11},{11,12},{12,2},{12,8},{12,12},{13,1},{13,13},{14,14},{15,9},{15,10},{15,11},{15,12},{16,7},{16,16},{17,1},{17,6},{17,16} };
	x0 = { {0,7},{2,4},{4,12},{7,0},{7,1},{8,3},{16,13},{17,15} };
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
	//初始化野生的战斗
	myPokemons.clear();
    enemyPokemons.clear();
	s.PlayMusic(SoundPlayer::MUSIC_YeSheng);	//播放野生的战斗音乐
	this->pokemonLib = pokemonLib;
	//从pokemonLib中复制当前玩家拥有的所有的宝可梦
	for (int i = 0; i < pokemonLib->pokemonInGame.size(); i++) 
	{
		Pokemon* pokemon = new Pokemon(*pokemonLib->GetPokemonInGame(i + 1));
		myPokemons.push_back(pokemon);
	}
	//野战对方只有一只随机生成的宝可梦
	Pokemon* enemyPokemon = new Pokemon(id,level);
    enemyPokemons.push_back(enemyPokemon);
    pokemonNow = myPokemons[0];	//固定派出第一个宝可梦
    enemyNow = enemyPokemons[0];
	isTrainer = false;
	escapeFailedTimes = 0;
	combatLog.clearLog();
    beaten.clear();
	Text text;	//初始化战斗日志
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
	//初始化训练师的战斗
	//基本同InitWildCombat,只是从文件中读取训练师的宝可梦信息
	myPokemons.clear();
	enemyPokemons.clear();
    s.PlayMusic(SoundPlayer::MUSIC_DuiZhan);
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
	//初始化战斗日志
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
    //返回当前玩家拥有的所有存活宝可梦
	vector<Pokemon*> available;
	for (auto& pokemon : myPokemons)
	{
		if (pokemon->attribute.hp > 0) available.push_back(pokemon);
	}
    return available;
}

vector<Pokemon*> Combat::enemyAvailable()
{
    	//返回当前训练师拥有的所有存活宝可梦
	vector<Pokemon*> available;
	for (auto& pokemon : enemyPokemons)
	{
        if (pokemon->attribute.hp > 0) available.push_back(pokemon);
	}
    return available;
}

vector<Text> Combat::PokemonAvailableText()
{
    //返回当前玩家拥有的所有存活宝可梦的文本信息
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
	//更换宝可梦
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
	//显示当前对战双方宝可梦信息
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
	//显示当前宝可梦的技能信息
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
	//根据wiki的公式计算战斗经验
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
	//战斗结束,处理战斗结果,回传宝可梦状态,清空战斗状态
	//战斗日志显示获得经验
	combatLog.clearLog();
	combatLog.AddLog(Text("战斗结束\n"));
	if(lastCombatWin) combatLog.AddLog(Text("你赢了!\n"));
    	else combatLog.AddLog(Text("你输了!\n"));
 	for (int i = 0; i < beaten.size(); i++)
	{
		pair<Pokemon*, Pokemon*> battleResult = beaten[i];	//战胜方宝可梦,被战胜方宝可梦
		//查询战胜方的宝可梦是否是我方宝可梦
		for (auto pk : myPokemons)
		{
			if(pk == battleResult.first)
			combatLog.AddLog(battleResult.first->GetExperience(GetExperienceFromBattle(battleResult.second)));
		}
		battleResult.first->AddBasicValue(battleResult.second->basicValue);
	}
	//将战斗中宝可梦状态回传,包括血量,状态,技能PP,增加经验和基础点数,升级在主循环处理
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
	s.StopMusic();	//停止战斗音乐
	beaten.clear();
}
