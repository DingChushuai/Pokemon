#include "Prop.h"

Prop::Prop(int ID)
{
	//从PROP_INFO_PATH中按照ID读取信息

}

Prop::Prop(Prop& prop)
{
    //复制构造函数
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



