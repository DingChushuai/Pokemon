#pragma once
#include "Backpack.h"
class Shop
{
private:
    Backpack shop;
public:
    Shop();
    vector<Text> GetPropsInShop();  //显示商店里的商品
    int GetPriceOfProp(int index); 
    Prop BuyProp(int index,int count);  //返回一个商品样本,用于给背包添加
};

