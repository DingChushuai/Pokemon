#pragma once
#ifndef SKILL_H
#define SKILL_H
#include <string>
#include <vector>
#include "tools.h"
#include "Text.h"

class Pokemon;

using namespace std;

enum Type {
    NONE = -1,
    NORMAL = 0,
    FIGHTING, //��
    FLYING,   //����
    POISON,   //��
    GROUND,   //����
    ROCK,     //��ʯ
    BUG,      //��
    GHOST,    //����
    STEEL,    //��
    FIRE,     //��
    WATER,    //ˮ
    GRASS,    //��
    ELECTRIC, //��
    PSYCHIC,  //������
    ICE,      //��
    DRAGON,   //��
    DARK,     //��
    FAIRY,    //����
};

class Skill
{
    const enum SkillType {
        PHYSICAL = 0,     //����
        SPECIAL,        //����
        CHANGE,         //�仯
    };
    //����Ч��������
    //ÿ�����͵Ĳ�������
    const enum SkillEffect {
        ATTACK = 0,       //����(�޲���)
        MUTI_ATTACK,      //��ι���(������С����,����������)
        ATTACK_AND_STATE, //�������и���ʩ���쳣״̬(�쳣״̬1��ID,�쳣״̬1����,�쳣״̬2��ID,�쳣״̬2����....)
        ATTACK_AND_BUFF, //���������Լ�ʩ��buff(buffID_1,�ı�buff�ķ�ʽ(1Ϊ����,2Ϊ����),�ı�����õ�ֵ,...)
        ATTACK_AND_DEBUFF,//���������Է�ʩ��debuff(����ͬ��)
        BUFF,            //���Լ�ʩ��buff(����ͬ��)
        DEBUFF,          //���Է�ʩ��debuff(����ͬ��)
        STATE,           //ʩ���쳣״̬(�쳣״̬��ID,�쳣״̬����)
        HEAL_HP,              //�ظ�(�ظ��ķ�ʽ(1���������ظ�,2���հٷֱȻظ�),�ظ��ٷֱ�(�����2))
        ATTACK_AND_HEAL,        //�������ظ�(�ظ�ֵռ�����˺��İٷֱ�,����50��ʾ�ظ��˺�ֵ��һ��Ѫ��)
        SPECIAL_EFFECT,               //����Ч��(����Ч������ID(������ܲ�����������������,��Ҫ�������Ч������))
    };
public:
    Skill(int skillID);     //�Ӽ��ܱ��ȡ������Ϣ
    ~Skill() {};

    int skillID;            //���
    string skillName;       //����
    string skillDescription;//����
    Type type;              //����
    SkillType skillType;    //��������
    int power;              //����
    int accuracy;           //����
    int PP;                 //pp
    int maxPP;              //���pp
    SkillEffect skillEffect; //����Ч��
    vector<int> effectParam; //����Ч������
    int mustHit;             //�ض�����
    int priority;            //���ȼ�
};

#endif // SKILL_H