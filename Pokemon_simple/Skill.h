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
    FIGHTING, //格斗
    FLYING,   //飞行
    POISON,   //毒
    GROUND,   //地面
    ROCK,     //岩石
    BUG,      //虫
    GHOST,    //幽灵
    STEEL,    //钢
    FIRE,     //火
    WATER,    //水
    GRASS,    //草
    ELECTRIC, //电
    PSYCHIC,  //超能力
    ICE,      //冰
    DRAGON,   //龙
    DARK,     //恶
    FAIRY,    //妖精
};

class Skill
{
    const enum SkillType {
        PHYSICAL = 0,     //物理
        SPECIAL,        //特殊
        CHANGE,         //变化
    };
    //技能效果的类型
    //每个类型的参数如下
    const enum SkillEffect {
        ATTACK = 0,       //攻击(无参数)
        MUTI_ATTACK,      //多段攻击(攻击最小次数,攻击最大次数)
        ATTACK_AND_STATE, //攻击并有概率施加异常状态(异常状态1的ID,异常状态1概率,异常状态2的ID,异常状态2概率....)
        ATTACK_AND_BUFF, //攻击并给自己施加buff(buffID_1,改变buff的方式(1为增加,2为设置),改变或设置的值,...)
        ATTACK_AND_DEBUFF,//攻击并给对方施加debuff(参数同上)
        BUFF,            //给自己施加buff(参数同上)
        DEBUFF,          //给对方施加debuff(参数同上)
        STATE,           //施加异常状态(异常状态的ID,异常状态概率)
        HEAL_HP,              //回复(回复的方式(1按照威力回复,2按照百分比回复),回复百分比(如果是2))
        ATTACK_AND_HEAL,        //攻击并回复(回复值占攻击伤害的百分比,例如50表示回复伤害值的一半血量)
        SPECIAL_EFFECT,               //特殊效果(特殊效果函数ID(如果技能不属于以上所有类型,需要单独设计效果函数))
    };
public:
    Skill(int skillID);     //从技能表读取技能信息
    ~Skill() {};

    int skillID;            //编号
    string skillName;       //名称
    string skillDescription;//描述
    Type type;              //属性
    SkillType skillType;    //技能类型
    int power;              //威力
    int accuracy;           //命中
    int PP;                 //pp
    int maxPP;              //最大pp
    SkillEffect skillEffect; //技能效果
    vector<int> effectParam; //技能效果参数
    int mustHit;             //必定命中
    int priority;            //优先级
};

#endif // SKILL_H