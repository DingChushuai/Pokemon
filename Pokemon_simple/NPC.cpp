#include "NPC.h"

NPC::NPC(int id)
{
	//��NPC_NIFO_PATH�в���id��Ӧ��NPC

}

NPC::NPC(string info)
{
}

bool NPC::LoadInfo(int id)
{
    //��NPC_STATE_PATH�ж�ȡNPC��λ�ú�״̬��Ϣ
	return false;
}

bool NPC::LoadInfo(string info)
{
	return false;
}

string NPC::GetTalk()
{
	return string();
}

string NPC::GetNotFinishTalk()
{
	return string();
}

bool NPC::TryChangeState(Game* game)
{
	/*
	stateAction:
				0:����Ϊ, �Ի���ɺ�ֱ����ת����һ��״̬
				1:�ƶ���ָ��λ��(MapID,PositionX,PositionY)
				2:����ս��(BattleID, λ��Battle.csv), ս��ʤ����Ϊ״̬���
				3.�������NPC״̬(NPC_ID,State_ID), ���NPC_ID��NPC����State_ID״̬, ��״̬���
				4.�������Ƿ�ӵ��ָ����Ʒ(PropID), ���ӵ��, ��״̬���
				5.�ύ��Ʒ(PropID,PropCount), �����ӵ�е�PropID��Ʒ,����ΪProp���ύ��NPC, Ȼ��״̬���
				6.�������Ƿ�ӵ��ָ��������(PokemonID), ���ӵ��, ��״̬���
				7.��ĳ��������(PokemonID)�������, Ȼ��״̬���
				8.��ĳ������(PropID,PropCount)�������
	*/
	return false;
}
