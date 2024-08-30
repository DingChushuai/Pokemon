#pragma once
#ifndef POKEMON_H
#define POKEMON_H


#include <string>
#include <vector>
#include "Skill.h"
using namespace std;

class Pokemon
{
public:
    //����״̬����ֵ
    /*
    �����仯��ʼΪ0����߿������ +6����Ϳɽ����� -6�����滻������ʱ�����滻�³��ı����������仯��ԭΪ0��
    �������ع����������ط����ٶ�,�������������ʵ�����ֵ�仯, ÿһ�ȼ��ı仯Ϊ(���ٷֱ�)
    -6   -5   -4  -3    -2    -1   0     1     2   3    4     5   6
    25%  28%  33%  40%  50%  66%  100%  150% 200% 250% 300% 350% 400%
    */
    const struct Buff {
        //id��1��ʼ����
        int attack;         //����
        int defense;        //����
        int speed;          //�ٶ�
        int specialAttack;  //�ع�
        int specialDefense; //�ط�
        int accuracy;       //������
        int evasion;        //������
    };
    //�쳣״̬
    enum PokemonStatu {
        None = 0, //���쳣״̬
        Poison, //�ж�, ÿ�غϽ���ʱ����ʧ1/8�������ֵ,��಻����15��
        Paralysis, //���, ÿ�غ�25%ʹ����ʧЧ, ���ٶȽ���50%
        Burn, //����, ÿ�غϽ���ʱ����ʧ1/16�������ֵ, ������������50%
        Sleep, //˯��, �޷��ж�, ÿ�غ���20%�Զ����
        Freeze, //����, �޷�ʹ�������������⹥��, ÿ�غ���10%�Զ����
        Frostbite   //����, ÿ�غϽ���ʱ����ʧ1/16�������ֵ, �����⹥������50%, �����Ա����β��ᱻ����
    };

    const struct ATTRIBUTE {
        //id��1��ʼ����
        int hp;     //Ѫ��
        int maxHp;  //���Ѫ��
        int attack; //����
        int defense;//����
        int speed;  //�ٶ�
        int specialAttack;  //�ع�
        int specialDefense; //�ط�
    };
    int ID;
    string name;
    pair<Type, Type> type;  //Type�Ķ�����Skill.h��
    int level;          //�ȼ�
    int experience;     //����
    int experienceToNextLevel; //�������辭��
    ATTRIBUTE attribute; //����ֵ
    PokemonStatu statu; //�쳣״̬
    Buff buff;          //����״̬����ֵ
    vector<Skill> skills; //����

    Pokemon(int ID, int level);     //����ID�͵ȼ�����һ��������Եı�����, ����������ɱ�����
    Pokemon(const Pokemon& other);  //���ƹ��캯��, ���ڸ��Ʊ����ε�ս����

    ~Pokemon();
    void PrintDetail(); //��ӡ��������ϸ��Ϣ
    int GetSellPrice(); //��ȡ���ۼ۸�
private:
    int evolutionLevel; //�����ȼ�
    int evolutionID;    //�������ID
    int captureRate; //������
    struct EthnicValue
    {
        int hp;     //Ѫ��
        int attack; //����
        int defense;//����
        int specialAttack;  //�ع�
        int specialDefense; //�ط�
        int speed;  //�ٶ�

    }ethnicValue; //����ֵ
    struct IndividualValue
    {
        int hp;     //Ѫ��
        int attack; //����
        int defense;//����
        int specialAttack;  //�ع�
        int specialDefense; //�ط�
        int speed;  //�ٶ�

    }individualValue; //����ֵ
    struct BasicValue
    {
        int hp;     //Ѫ��
        int attack; //����
        int defense;//����
        int specialAttack;  //�ع�
        int specialDefense; //�ط�
        int speed;  //�ٶ�

    }basicValue; //��������
    int growthRate; //�ɳ��ٶ�
    int basicExperience; //��������
};

#endif // !POKEMON_H
