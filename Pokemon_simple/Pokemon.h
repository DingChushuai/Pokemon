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
    //能力状态修正值
    /*
    能力变化初始为0，最高可提高至 +6，最低可降低至 -6。当替换宝可梦时，被替换下场的宝可梦能力变化复原为0。
    攻击、特攻、防御、特防和速度,命中率与闪避率的能力值变化, 每一等级的变化为(按百分比)
    -6   -5   -4  -3    -2    -1   0     1     2   3    4     5   6
    25%  28%  33%  40%  50%  66%  100%  150% 200% 250% 300% 350% 400%
    */
    const struct Buff {
        //id以1开始计数
        int attack;         //攻击
        int defense;        //防御
        int speed;          //速度
        int specialAttack;  //特攻
        int specialDefense; //特防
        int accuracy;       //命中率
        int evasion;        //闪避率
    };
    //异常状态
    enum PokemonStatu {
        None = 0, //无异常状态
        Poison, //中毒, 每回合结束时会损失1/8最大生命值,最多不超过15点
        Paralysis, //麻痹, 每回合25%使攻击失效, 且速度降低50%
        Burn, //灼伤, 每回合结束时会损失1/16最大生命值, 且物理攻击降低50%
        Sleep, //睡眠, 无法行动, 每回合有20%自动解除
        Freeze, //冰冻, 无法使用物理攻击和特殊攻击, 每回合有10%自动解除
        Frostbite   //冻伤, 每回合结束时会损失1/16最大生命值, 且特殊攻击降低50%, 冰属性宝可梦不会被冻伤
    };

    const struct ATTRIBUTE {
        //id以1开始计数
        int hp;     //血量
        int maxHp;  //最大血量
        int attack; //攻击
        int defense;//防御
        int speed;  //速度
        int specialAttack;  //特攻
        int specialDefense; //特防
    };
    int ID;
    string name;
    pair<Type, Type> type;  //Type的定义在Skill.h中
    int level;          //等级
    int experience;     //经验
    int experienceToNextLevel; //升级所需经验
    ATTRIBUTE attribute; //能力值
    PokemonStatu statu; //异常状态
    Buff buff;          //能力状态修正值
    vector<Skill> skills; //技能

    Pokemon(int ID, int level);     //根据ID和等级构造一个随机属性的宝可梦, 用于随机生成宝可梦
    Pokemon(const Pokemon& other);  //复制构造函数, 用于复制宝可梦到战斗中

    ~Pokemon();
    void Print(); //打印宝可梦信息
    void PrintDetail(); //打印宝可梦详细信息
    int GetSellPrice(); //获取出售价格
private:
    int evolutionLevel; //进化等级
    int evolutionID;    //进化后的ID
    int captureRate; //捕获率
    struct EthnicValue
    {
        int hp;     //血量
        int attack; //攻击
        int defense;//防御
        int specialAttack;  //特攻
        int specialDefense; //特防
        int speed;  //速度

    }ethnicValue; //种族值
    struct IndividualValue
    {
        int hp;     //血量
        int attack; //攻击
        int defense;//防御
        int specialAttack;  //特攻
        int specialDefense; //特防
        int speed;  //速度

    }individualValue; //个体值
    struct BasicValue
    {
        int hp;     //血量
        int attack; //攻击
        int defense;//防御
        int specialAttack;  //特攻
        int specialDefense; //特防
        int speed;  //速度

    }basicValue; //基础点数
    int growthRate; //成长速度
    int basicExperience; //基础经验

};

#endif // !POKEMON_H
