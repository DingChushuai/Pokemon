#include "Backpack.h"

Backpack::Backpack()
{
	//do nothing
}

Backpack::~Backpack()
{
	//do nothing
}

void Backpack::Load()
{
	//从BACKPACK_STATE_PATH中读取背包信息
	//使用AddProp()添加道具
}

void Backpack::AddProp(Prop* prop)
{
    //将prop添加到背包中
}

void Backpack::AddProp(int id, int num)
{
    //将id和num对应的道具添加到背包中
	//使用Prop构造函数
}

Prop* Backpack::GetProp(int id)
{
    //返回id对应的道具
    for (auto prop : props) {
        if (prop->GetID() == id) {
            return prop;
        }
    }
	return nullptr;
}

void Backpack::ReduceProp(int id, int num)
{
}

void Backpack::ReduceProp(Prop* prop)
{
}

void Backpack::IncreaseProp(int id, int num)
{
}

void Backpack::IncreaseProp(Prop* prop)
{
}

void Backpack::RemoveProp(Prop* prop)
{
    //将prop从背包中移除
	props.erase(std::remove(props.begin(), props.end(), prop), props.end());
}

void Backpack::RemoveProp(int id)
{
    //将id对应的道具从背包中移除
    for (auto prop : props) {
    if (prop->GetID() == id) {
        RemoveProp(prop);
        break;
    }
}

}

vector<Prop*> Backpack::GetProps()
{
    return props;
}

void Backpack::Save()
{
    //将背包信息保存到BACKPACK_STATE_PATH中
}

void Backpack::Clear()
{
    props.clear();
}
