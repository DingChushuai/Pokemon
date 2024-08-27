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
    ifstream ifs;
    ifs.open("BACKPACK_STATE_PATH", ios::in);

        string rea;
        vector<string> data;
        while (getline(ifs, rea))
        {  
            data = Split(rea, ',');

        }
            
         ifs.close();

	//��BACKPACK_STATE_PATH�ж�ȡ������Ϣ
	//ʹ��AddProp()��ӵ���
}

void Backpack::AddProp(Prop* prop)
{
    props.push_back(prop);//��prop��ӵ�������
}

void Backpack::AddProp(int id, int num)
{
    Prop(id);
    //��id��num��Ӧ�ĵ�����ӵ�������
	//ʹ��Prop���캯��
}

Prop* Backpack::GetProp(int id)
{
    //����id��Ӧ�ĵ���
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
            prop->SetNum(n-num);
        }
    }

}

void Backpack::ReduceProp(Prop* prop)
{



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

void Backpack::IncreaseProp(Prop* prop)
{
    props.add(std::remove(props.begin(), props.end(), prop), props.end());

    

}

void Backpack::RemoveProp(Prop* prop)
{
    //��prop�ӱ������Ƴ�
	props.erase(std::remove(props.begin(), props.end(), prop), props.end());
}

void Backpack::RemoveProp(int id)
{
    //��id��Ӧ�ĵ��ߴӱ������Ƴ�
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
    //��������Ϣ���浽BACKPACK_STATE_PATH��
}

void Backpack::Clear()
{
    props.clear();
}
