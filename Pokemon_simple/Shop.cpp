#include "Shop.h"

Shop::Shop()
{
    //初始化商店,一次性读取所有可以购买的道具
    for (int i = 1; i <= PROPS_COUNT; i++)
    {
        Prop* prop = new Prop(i);
        if (prop->GetPrice() > 0)
            shop.AddProp(prop);
        else
            delete prop;
    }
}

vector<Text> Shop::GetPropsInShop()
{
    //获取商店中所有可以购买的道具的信息
    vector<Text> props;
    vector<Prop*> shopProps = shop.GetProps();
    for (int i = 0; i < shopProps.size(); i++)
    {
        string s;
        s += shopProps[i]->GetName();
        //扩充到20个字符
        while (s.length() < 14)
            s += " ";
        s += to_string(shopProps[i]->GetPrice());
        while (s.length() < 20)
            s += " ";
        s += shopProps[i]->GetDescription();
        props.push_back(Text(s));
    }
    return props;
}

int Shop::GetPriceOfProp(int index)
{
    return shop.GetPropFromIndex(index)->GetPrice();
}

Prop Shop::BuyProp(int index, int count)
{
    Prop prop = *shop.GetPropFromIndex(index);
    prop.SetNum(count);
    return prop; 
}
