#pragma once
#ifndef BACKPACK_H
#define BACKPACK_H

#include "Prop.h"
#include "Text.h"

class Backpack
{
public: 
    Backpack();
    ~Backpack();
    void Load();
    void AddProp(Prop* prop);
    void AddProp(int id, int num);
    Prop* GetProp_(int id);
    Prop* GetPropFromIndex(int index);
    bool ReduceProp(int id, int num);
    bool ReduceProp(Prop* prop,int num);
    void IncreaseProp(int id, int num);
    void IncreaseProp(Prop* prop,int num);
    void RemoveProp_(Prop* prop);
    void RemoveProp_(int id);
    vector<Prop*> GetProps();
    vector<Text> GetPropsInfo();
    vector<Text> GetPropsSellPrice();
    vector<Text> GetPropsBuyPrice();
    void Save();
    void Clear();

private:
    vector<Prop*> props;
};

#endif // !BACKPACK_H
