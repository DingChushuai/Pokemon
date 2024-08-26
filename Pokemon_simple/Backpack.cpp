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
	//��BACKPACK_STATE_PATH�ж�ȡ������Ϣ
	//ʹ��AddProp()��ӵ���
}

void Backpack::AddProp(Prop* prop)
{
    //��prop��ӵ�������
}

void Backpack::AddProp(int id, int num)
{
    //��id��num��Ӧ�ĵ�����ӵ�������
	//ʹ��Prop���캯��
}

Prop* Backpack::GetProp(int id)
{
    //����id��Ӧ�ĵ���
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
    //��prop�ӱ������Ƴ�
	props.erase(std::remove(props.begin(), props.end(), prop), props.end());
}

void Backpack::RemoveProp(int id)
{
    //��id��Ӧ�ĵ��ߴӱ������Ƴ�
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
    //��������Ϣ���浽BACKPACK_STATE_PATH��
}

void Backpack::Clear()
{
    props.clear();
}
