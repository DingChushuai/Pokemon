#pragma once
#ifndef NPC_H
#define NPC_H
#include <string>
#include <vector>

using namespace std;

struct State
{
    int ID;
    string stateTalk;
    string stateNotFinishTalk;
    vector<int> stateAction;    //第一位为动作类型，后面为动作参数
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
    bool LoadInfo(int id);
    bool LoadInfo(string info);
    string GetTalk();
    string GetNotFinishTalk();
    ~NPC() {};
private:
    vector<State> stateList;
};

#endif // NPC_H
