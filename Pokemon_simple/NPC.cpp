#include "NPC.h"
#pragma once
#include<fstream>
#include"tools.h"
NPC::NPC(int id)
{
	ifstream ifs;
	ifs.open("NPC_NIFO_PATH", ios::in);
	string rea;
	vector<string>data;
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
	state = stoi(data[5]);
	//TODO:
	//��NPC_NIFO_PATH�в���id��Ӧ��NPC
	//����npc�ĸ�����Ϣ���뵽��Ա������
	//��ϸ��ο�README.md
	//���Բο�Prop���map��Ĺ��캯����д��
}

NPC::NPC(string info)
{
	
	vector<string>data;
	data = Split(info, ',');
	int id0, x0, y0, state0;
	id0 = stoi(data[0]);
	x0 = stoi(data[1]);
	y0 = stoi(data[2]);
	state0 = stoi(data[3]);
	NPC* a = new NPC(id0);
	a->x= x0;
	a->y = y0;
	a->state = state0;
		
	//TODO:
	//�˺������ڶ�ȡNPC_State.csv�е�һ����Ϣ,������NPC����
	//��ϸ��ο�README.md
	//һ����Ϣֻ����id,λ��,״̬
	//ʹ��NPC(int id)����NPC����,Ȼ�������״̬��λ��
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
	return State();//����һ���յ�State
}
