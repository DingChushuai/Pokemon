#include "NPC.h"
#pragma once
#include<fstream>
#include"tools.h"
NPC::NPC(int id)
{
	ifstream ifs;
	ifs.open(NPC_INFO_PATH, ios::in);
	string rea;
	vector<string>data;
	vector<string>locate;
	while (getline(ifs, rea))
	{
		data = Split(rea, ',');
		int temp = stoi(data[0]);
		if (temp == id)
			break;
		else
			continue;
	}
	ifs.close();
	this->ID = id;
	name = data[1];
	locate = Split(data[2], '/');
	mapID = stoi(locate[0]);
	x = stoi(locate[1]);
	y = stoi(locate[2]);
	state = stoi(data[3]);
	//TODO:
	//在NPC_NIFO_PATH中查找id对应的NPC
	//并将npc的各项信息存入到成员变量中
	//详细请参考README.md
	//可以参考Prop类和map类的构造函数的写法
}

NPC::NPC(string info)
{
	
	vector<string>data;
	data = Split(info, ',');
	int id0;
	id0 = stoi(data[0]);
	NPC* a = new NPC(id0);
	a->state = stoi(data[1]);
	a->mapID = stoi(data[2]);
	a->x = stoi(data[3]);
	a->y = stoi(data[4]);

		
	//TODO:
	//此函数用于读取NPC_State.csv中的一行信息,并生成NPC对象
	//详细请参考README.md
	//一行信息只包含id,位置,状态
	//使用NPC(int id)创建NPC对象,然后更改其状态和位置
}

string NPC::GetTalk()
{
	return this->GetState().stateTalk;
}

string NPC::GetNotFinishTalk()
{
	return this->GetState().stateNotFinishTalk;
}

State NPC::GetState()
{
	for (int i = 0; i < this->stateList.size(); i++)
	{
		if (this->stateList[i].ID == this->state)
		{
            return this->stateList[i];
		}
	}
	return State();//返回一个空的State
}
