#pragma once
#ifndef BACKPACK_H
#define BACKPACK_H

#include "Prop.h"
#include "Text.h"
//������: ��ɾ���ӵ�еĵ���
class Backpack
{
public: 
    Backpack();
    ~Backpack();
    void Load();    //���ش浵
    void AddProp(Prop* prop);   //��ӵ���
    void AddProp(int id, int num);  //����id��ӵ���
    Prop* GetProp_(int id);     //��ȡ����
    Prop* GetPropFromIndex(int index);  //��ȡ����
    bool ReduceProp(int id, int num = 1);   //���ٵ���,�����Ƿ�ɹ�,������ɾ��
    bool ReduceProp(Prop* prop,int num = 1);
    void IncreaseProp(int id, int num = 1); //���ӵ���
    void IncreaseProp(Prop* prop,int num = 1);
    void RemoveProp_(Prop* prop);   //ɾ������
    void RemoveProp_(int id);
    vector<Prop*> GetProps();
    vector<Prop*> GetPropsCanUseInBattle();
    vector<Prop*> GetPropsCanUseInField();
    vector<Text> GetPropsInfo();    //��ȡ������Ϣ
    vector<Text> GetPropsSellPrice();
    vector<Text> GetPropsBuyPrice();
    void Save();        //����浵
    void Clear();   //��ձ���

private:
    vector<Prop*> props;
};

#endif // !BACKPACK_H
