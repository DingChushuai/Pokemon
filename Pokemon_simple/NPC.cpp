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

bool NPC::TryChangeState(Game* game)
{
	/*
	stateAction:
				0:无行为, 对话完成后直接跳转到下一个状态
				1:移动到指定位置(MapID,PositionX,PositionY)
				2:触发战斗(BattleID, 位于Battle.csv), 战斗胜利视为状态完成
				3.检查其他NPC状态(NPC_ID,State_ID), 如果NPC_ID的NPC处于State_ID状态, 则状态完成
				4.检查玩家是否拥有指定物品(PropID), 如果拥有, 则状态完成
				5.提交物品(PropID,PropCount), 将玩家拥有的PropID物品,数量为Prop个提交给NPC, 然后状态完成
				6.检查玩家是否拥有指定宝可梦(PokemonID), 如果拥有, 则状态完成
				7.将某个宝可梦(PokemonID)交给玩家, 然后状态完成
				8.将某个道具(PropID,PropCount)交给玩家
	*/
	return false;
}
