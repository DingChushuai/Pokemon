#include "Prop.h"
#include "tools.h"
#include <fstream>

Prop::Prop(int ID)
{
	//从PROP_INFO_PATH中按照ID读取信息
	ifstream file("Prop_Info.csv");
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
	vector<int> temp(4);
	for (int i = 3; i < 6; ++i) {
		temp.push_back(stoi(data[i]));
	}
	type = (PROP_TYPE)(temp[0]);
	num = temp[1];
	price = temp[2];
	sellPrice = temp[3];
	vector<string>tempEffect = Split(data[7], '/');
	for (int i = 0; i < tempEffect.size(); ++i)
		effectPara.push_back(stoi(tempEffect[i]));
}

Prop::Prop(const Prop& prop)
{
	ID = prop.ID;
	name = prop.name;
	description = prop.description;
	num = prop.num;
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



