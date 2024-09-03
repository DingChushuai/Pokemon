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
	//��NPC_NIFO_PATH�в���id��Ӧ��NPC
	//����npc�ĸ�����Ϣ���뵽��Ա������
	//��ϸ��ο�README.md
	//���Բο�Prop���map��Ĺ��캯����д��
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
