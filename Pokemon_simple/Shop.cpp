#include "Shop.h"

Shop::Shop()
{
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
    vector<Text> props;
    vector<Prop*> shopProps = shop.GetProps();
    for (int i = 0; i < shopProps.size(); i++)
    {
        string s;
        s += shopProps[i]->GetName();
        //À©³äµ½20¸ö×Ö·û
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
