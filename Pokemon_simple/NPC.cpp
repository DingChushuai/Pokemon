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
