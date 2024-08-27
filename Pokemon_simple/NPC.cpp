#include "NPC.h"

NPC::NPC(int id)
{
	//在NPC_NIFO_PATH中查找id对应的NPC

}

NPC::NPC(string info)
{
}

bool NPC::LoadInfo(int id)
{
    //从NPC_STATE_PATH中读取NPC的位置和状态信息
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
