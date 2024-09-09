#pragma once
#include "Backpack.h"
#include<fstream>
#include<vector>
#include<string>
Backpack::Backpack()
{
	//do nothing
}

Backpack::~Backpack()
{
	//do nothing
}

void Backpack::Load()
{
    Clear();
    ifstream ifs;
    ifs.open(BACKPACK_STATE_PATH, ios::in);
    string rea;
    vector<string>data;
    while (getline(ifs, rea))
    {  
        data = Split(rea, ',');
        AddProp(atoi(data[0].c_str()), atoi(data[1].c_str()));
    }
    ifs.close();
}

void Backpack::AddProp(Prop* prop)
{
    for (auto it : props)
    {
        if (it->GetID() == prop->GetID())
        {
            it->SetNum(it->GetNum() + prop->GetNum());
            delete prop;
            return;
        }
    }
    props.push_back(prop);
}

void Backpack::AddProp(int id, int num)
{
    Prop *a=new Prop(id);
    a->SetNum(num);
    props.push_back(a);
}

Prop* Backpack::GetProp_(int id)
{
    //返回id对应的道具
    for (auto prop : props) {
        if (prop->GetID() == id) {
            return prop;
        }
    }
	return nullptr;
}

Prop* Backpack::GetPropFromIndex(int index)
{
    if (index >= 0 && index <= props.size()) {
        return props[index-1];
    }
    return nullptr;
}

bool Backpack::ReduceProp(int id, int num)
{
    for (auto prop : props)
    {
        if (prop->GetID() == id)
        {
            int n;
            n = prop->GetNum();
            
            if (n - num > 0)
            {
                prop->SetNum(n - num);
                return true;
            }
            else if (n - num == 0)
            {
                RemoveProp_(prop);
                return true;
            }
            else
            {
                return false;
            }
        }
    }
    return false;
}

bool Backpack::ReduceProp(Prop* prop,int num)
{
    int n;
    n = prop->GetNum();
    if (n - num >0)
    {
        prop->SetNum(prop->GetNum() - num);
        return true;
    }
    if (n - num == 0)
    {
        RemoveProp_(prop);
        return true;
    }
    return false;
}

void Backpack::IncreaseProp(int id, int num)
{
    for (auto prop:props)
    {
        if (prop->GetID() == id)
        {
            int m;
            m = prop->GetNum();
            prop->SetNum(m + num);
            break;
        }
    }
}

void Backpack::IncreaseProp(Prop* prop,int num)
{  
    prop->SetNum(prop->GetNum() + num);
}

void Backpack::RemoveProp_(Prop* prop)
{
	props.erase(std::remove(props.begin(), props.end(), prop), props.end());
}

void Backpack::RemoveProp_(int id)
{
    for (auto prop : props) {
        if (prop->GetID() == id) 
        {
            RemoveProp_(prop);
            break;
        }
    }
}

vector<Prop*> Backpack::GetProps()
{
    return props;
}

vector<Prop*> Backpack::GetPropsCanUseInBattle()
{
    vector<Prop*> res;
    for (auto prop : props)
    {
        if (prop->IsCanUseInBattle())
        {
            res.push_back(prop);
        }
    }
    return res;
}

vector<Prop*> Backpack::GetPropsCanUseInField()
{
    vector<Prop*> res;
    {
        for (auto prop : props)
        {
            if (prop->IsCanUseInField())
            {
                res.push_back(prop);
            }
        }
    }
    return res;
}

vector<Text> Backpack::GetPropsInfo()
{
    vector<Text> infoTexts;
    vector<Prop*> backpackProps = props;
    for (int i = 0; i < backpackProps.size(); i++)
    {
        string s;
        s += backpackProps[i]->GetName();
        while (s.length() < 14)
            s += " ";
        s += to_string(backpackProps[i]->GetNum());
        while (s.length() < 20)
            s += " ";
        s += backpackProps[i]->GetDescription();
        infoTexts.push_back(Text(s));
    }
    return infoTexts;
}
vector<Text> Backpack::GetPropsSellPrice()
{
    vector<Text> sellPrices;
    for (int i = 0; i < props.size(); i++)
    {
        if (props[i]->GetSellPrice() > 0)
        {
            string s;
            s += props[i]->GetName();
            while (s.length() < 14)
                s += " ";
            s += to_string(props[i]->GetSellPrice());
            while (s.length() < 20)
                s += " ";
            s += props[i]->GetDescription();
            sellPrices.push_back(Text(s));
        }
    }
    return sellPrices;
}

vector<Text> Backpack::GetPropsBuyPrice()
{
    vector<Text> buyPrices;
    for (int i = 0; i < props.size(); i++)
    {
        if (props[i]->GetPrice() < 0) 
        {
            string s;
            s += props[i]->GetName();
            while (s.length() < 14)
                s += " ";
            s += to_string(props[i]->GetPrice());
            while (s.length() < 20)
                s += " ";
            s += props[i]->GetDescription();
            buyPrices.push_back(Text(s));
        }
    }
    return buyPrices;
}

void Backpack::Save()
{
    ofstream ofs;
    ofs.open(BACKPACK_STATE_PATH, ios::out);
    for (auto prop : props)
    {
        ofs << prop->GetID() << "," << prop->GetNum() << endl;
    }
    ofs.close();
    //将背包信息保存到BACKPACK_STATE_PATH中
}

void Backpack::Clear()
{
    props.clear();
}
