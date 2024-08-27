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
    vector<int> stateAction;    //��һλΪ�������ͣ�����Ϊ��������
    int stateNext;
};

class NPC
{
public:
    int ID;			//������NPC�б��ж�λ
    string name;
    int mapID;
    int x, y;		//NPC�ڵ�ͼ�е�λ��
    int state;		//���ڱ��NPC��ǰ״̬
    NPC(int id);    //����ID��ʼ��NPC
    NPC(string info);    //���ݶ�ȡ����һ����Ϣ��ʼ��NPC
    bool LoadInfo(int id);
    bool LoadInfo(string info);
    string GetTalk();
    string GetNotFinishTalk();
    ~NPC() {};
private:
    vector<State> stateList;
};

#endif // NPC_H
