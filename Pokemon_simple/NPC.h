#pragma once
#ifndef NPC_H
#define NPC_H
#include <string>
#include <vector>

using namespace std;

struct State
{
    int ID;
    string stateTalk;   //状态完成后的对话
    string stateNotFinishTalk;  //状态未完成时的对话
    vector<int> stateAction;    //第一位为动作类型,后面为动作参数
    int stateNext;
};

class NPC
{
public:
    int ID;			//用于在NPC列表中定位
    string name;
    int mapID;
    int x, y;		//NPC在地图中的位置
    int state;		//用于标记NPC当前状态
    NPC(int id);    //根据ID初始化NPC
    NPC(string info);    //根据读取到的一行信息初始化NPC
    string GetTalk();
    string GetNotFinishTalk();
    State GetState();
    ~NPC() {};
private:
    vector<State> stateList;
};

#endif // NPC_H
