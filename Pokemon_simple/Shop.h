#pragma once
#include "Backpack.h"
class Shop
{
private:
    Backpack backpack;
public:
    Shop();
    vector<Text> GetPropsInShop();
    int GetPriceOfProp(int index);
    Prop BuyProp(int index,int count);
    
};

