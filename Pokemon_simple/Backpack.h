#pragma once
#ifndef BACKPACK_H
#define BACKPACK_H

#include "Prop.h"

class Backpack
{
public: 
    Backpack();
    ~Backpack();
    void Load();
    void AddProp(Prop* prop);
    void AddProp(int id, int num);
    Prop* GetProp(int id);
    void ReduceProp(int id, int num);
    void ReduceProp(Prop* prop);
    void IncreaseProp(int id, int num);
    void IncreaseProp(Prop* prop);
    void RemoveProp(Prop* prop);
    void RemoveProp(int id);
    vector<Prop*> GetProps();
    void Save();
    void Clear();

private:
    vector<Prop*> props;
};

#endif // !BACKPACK_H
