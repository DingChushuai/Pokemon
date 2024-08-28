#include "Backpack.h"
#include<fstream>
#include<vector>
//#include<iostream>
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
    ifs.open("BACKPACK_STATE_PATH", ios::in);
    
        string rea;
        vector<string>data;
    
        while (getline(ifs, rea))
        {  
            data = Split(rea, ',');
            AddProp(atoi(data[0].c_str()), atoi(data[1].c_str()));
            
        }
            
         ifs.close();

	//从BACKPACK_STATE_PATH中读取背包信息
	//使用AddProp()添加道具
}

void Backpack::AddProp(Prop* prop)
{
    props.push_back(prop);//将prop添加到背包中
}

void Backpack::AddProp(int id, int num)
{
    Prop *a=new Prop(id);
    a->SetNum(num);
    props.push_back(a);
    //将id和num对应的道具添加到背包中
	//使用Prop构造函数
}

Prop* Backpack::GetProp(int id)
{
    //返回id对应的道具
    for (auto prop : props) {
        if (prop->GetID() == id) {
            return prop;
        }
    }
	return nullptr;
}

void Backpack::ReduceProp(int id, int num)
{
    for (auto prop : props)
    {
        if (prop->GetID() == id)
        {
            int n;
            n = prop->GetNum();
            
            if (n - num >= 0)
            {
                prop->SetNum(n - num);
            }
            if (n - num == 0)RemoveProp(prop);
        }
    }

}
//bool Backpack::check( )

void Backpack::ReduceProp(Prop* prop,int num)
{
    int n;
    n = prop->GetNum();
    if (n - num >=0)
    {
        prop->SetNum(prop->GetNum() - num);
    }
    if (n - num == 0)RemoveProp(prop);

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
        }
    }

}

void Backpack::IncreaseProp(Prop* prop,int num)
{  
    prop->SetNum(prop->GetNum() + num);

    

}

void Backpack::RemoveProp(Prop* prop)
{
    //将prop从背包中移除
	props.erase(std::remove(props.begin(), props.end(), prop), props.end());
}

void Backpack::RemoveProp(int id)
{
    //将id对应的道具从背包中移除
    for (auto prop : props) {
    if (prop->GetID() == id) {
        RemoveProp(prop);
        break;
    }
}

}

vector<Prop*> Backpack::GetProps()
{
    return props;
}

void Backpack::Save()
{
    ofstream ofs;
    string ouc;
    ofs.open("BACKPACK_STATE_PATH", ios::out);
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
