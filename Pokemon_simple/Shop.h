#pragma once
#include "Backpack.h"
class Shop
{
private:
    Backpack shop;
public:
    Shop();
    vector<Text> GetPropsInShop();  //��ʾ�̵������Ʒ
    int GetPriceOfProp(int index); 
    Prop BuyProp(int index,int count);  //����һ����Ʒ����,���ڸ��������
};

