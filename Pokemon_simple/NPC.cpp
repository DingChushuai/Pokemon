#include "NPC.h"
#pragma once

NPC::NPC(int id)
{
	//TODO:
	//��NPC_NIFO_PATH�в���id��Ӧ��NPC
	//����npc�ĸ�����Ϣ���뵽��Ա������
	//��ϸ��ο�README.md
	//���Բο�Prop���map��Ĺ��캯����д��
}

NPC::NPC(string info)
{
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
