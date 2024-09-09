#include "NPC.h"
#pragma once
#include<fstream>
#include"tools.h"
NPC::NPC(int id)
{
	//从文件中读取信息
	//文件格式详见README.md
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
	mapID = stoi(data[2]);
	x = stoi(data[3]);
	y = stoi(data[4]);
	state = 0;
	vector<string> stateList = Split(data[5], '/');
	//处理npc的状态
	for (int i = 0; i < stateList.size(); i++)
	{
		vector<string> stateInfo = Split(stateList[i], '|');
		vector<string> stateActionStr = Split(stateInfo[3], '\\');
		vector<int> stateAction;
		for (int j = 0; j < stateActionStr.size(); j++) stateAction.push_back(stoi(stateActionStr[j]));
		State state = { stoi(stateInfo[0]), stateInfo[1], stateInfo[2], stateAction, stoi(stateInfo[4]) };
		this->stateList.push_back(state);
	}
}

NPC::NPC(string info)
{
	//从存档中读取信息
	vector<string>data;
	data = Split(info, ',');
	int id0;
	id0 = stoi(data[0]);
	NPC* a = new NPC(id0);
	a->state = stoi(data[1]);
	a->mapID = stoi(data[2]);
	a->x = stoi(data[3]);
	a->y = stoi(data[4]);
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
	return State();
}
