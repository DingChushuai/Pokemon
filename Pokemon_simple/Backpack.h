#pragma once
#ifndef BACKPACK_H
#define BACKPACK_H

#include "Prop.h"
#include "Text.h"
//背包类: 增删查改拥有的道具
class Backpack
{
public: 
    Backpack();
    ~Backpack();
    void Load();    //加载存档
    void AddProp(Prop* prop);   //添加道具
    void AddProp(int id, int num);  //按照id添加道具
    Prop* GetProp_(int id);     //获取道具
    Prop* GetPropFromIndex(int index);  //获取道具
    bool ReduceProp(int id, int num = 1);   //减少道具,返回是否成功,归零则删除
    bool ReduceProp(Prop* prop,int num = 1);
    void IncreaseProp(int id, int num = 1); //增加道具
    void IncreaseProp(Prop* prop,int num = 1);
    void RemoveProp_(Prop* prop);   //删除道具
    void RemoveProp_(int id);
    vector<Prop*> GetProps();
    vector<Prop*> GetPropsCanUseInBattle();
    vector<Prop*> GetPropsCanUseInField();
    vector<Text> GetPropsInfo();    //获取道具信息
    vector<Text> GetPropsSellPrice();
    vector<Text> GetPropsBuyPrice();
    void Save();        //保存存档
    void Clear();   //清空背包

private:
    vector<Prop*> props;
};

#endif // !BACKPACK_H
