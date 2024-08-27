#include "Prop.h"
#include "tools.h"
#include <fstream>

Prop::Prop(int ID)
{
	//从PROP_INFO_PATH中按照ID读取信息
    ifstream file("Prop_Info.csv");

    string line;
    vector<string>data;
    while (getline(file, line)) {
        data = Split(line, ',');
        if (ID == stoi(data[0]))
            break;
        else
            continue;
    }
    file.close();

    this->ID = ID;
    name = data[1];
    description = data[2];
    type = (PROP_TYPE)(stoi(data[3]));
    price = stoi(data[4]);
    sellPrice = stoi(data[5]);
    canUseInField = stoi(data[6]);
    canUseInBattle = stoi(data[7]);
    vector<string>temp = Split(data[8], '/');
    for (auto i : temp)
        effectPara.push_back(stoi(i));
}

Prop::Prop(Prop& prop)
{
    //复制构造函数
    this->ID = prop.ID;
    this->name = prop.name;
    this->description = prop.description;
    this->type = prop.type;
    this->price = prop.price;
    this->sellPrice = prop.sellPrice;
    this->canUseInField = prop.canUseInField;
    this->canUseInBattle = prop.canUseInBattle;
    this->effectPara = prop.effectPara;
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



