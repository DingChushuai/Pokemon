#include "Prop.h"
#include "tools.h"
#include <fstream>
#pragma once

Prop::Prop(int ID)
{
	//从文件中读取
	//详细信息参考README.md
	ifstream file(PROP_INFO_PATH);
	string line;
	vector<string> data;
	while (getline(file, line)) {
		data = Split(line, ',');
		int temp = stoi(data[0]);
		if (temp == ID)
			break;
		else
			continue;
	}
	file.close();
	this->ID = ID;
	name = data[1];
	description = data[2];
	vector<int> temp;
	for (int i = 3; i <= 7; ++i) {
		temp.push_back(stoi(data[i]));
	}
	type = (PROP_TYPE)(temp[0]);
	price = temp[1];
	sellPrice = temp[2];
	canUseInBattle = temp[4];
    canUseInField = temp[3];
	vector<string>tempEffect = Split(data[8], '/');
	for (int i = 0; i < tempEffect.size(); ++i)
		effectPara.push_back(stoi(tempEffect[i]));
}

Prop::Prop(const Prop& prop)
{
	//复制构造
	ID = prop.ID;
	name = prop.name;
	description = prop.description;
	num = prop.num;
    type = prop.type;
	price = prop.price;
	sellPrice = prop.sellPrice;
	effectPara = prop.effectPara;
	canUseInBattle = prop.canUseInBattle;
	canUseInField = prop.canUseInField;
}

int Prop::GetID()
{
	return	ID;
}

void Prop::SetNum(int num)
{
	this->num = num;
}

int Prop::GetNum()
{
	return num;
}

bool Prop::IsCanUseInBattle()
{
	return canUseInBattle;
}

bool Prop::IsCanUseInField()
{
	return canUseInField;
}

Prop::PROP_TYPE Prop::GetType()
{
	return type;
}

string Prop::GetName()
{
	return name;
}

string Prop::GetDescription()
{
	return description;
}

int Prop::GetPrice()
{
	return price;
}

int Prop::GetSellPrice()
{
	return sellPrice;
}

vector<int> Prop::GetEffectPara()
{
	return effectPara;
}



