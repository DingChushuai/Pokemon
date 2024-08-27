#pragma once
#ifndef PROP_H
#define PROP_H

#include <vector>
#include <string>
#include "tools.h"
using namespace std;

class Prop
{
    //道具的类型,以及参数
    const enum PROP_TYPE
    {
        NORMAL = 0,         //剧情道具,无效果
        EREASE_STATUS,  //消除自身状态(PokemonStatu(0表示可以消除任何状态))
        CHANGE_POKEMON_ATTRBUTE,  //改变宝可梦属性(ATTRIBUTE,改变值,...)  //在野外使用为永久改变,在战斗中使用为临时改变
        CHANGE_SKILL_ATTRIBUTE,  //改变技能属性(改变条件,条件参数,技能属性,改变值,技能属性,改变值...)     //在野外使用为永久改变,在战斗中使用为临时改变
        /*
        * 改变条件,条件参数:
        * 0.无条件(参数无效)
        * 1.技能类型(SkillType)
        * 2.技能属性(Type)
        技能属性id:
        1.power;              //威力
        2.accuracy;           //命中
        3.PP;                 //pp
        4.maxPP;              //最大pp
        */
        BUFF,   //改变能力状态修正值(能力状态修正值,改变值,...)  //在战斗中临时改变
        HEAL,  //回复体力(濒死时是否可用,回复方式(0按百分比,1按具体值),百分比/具体值)
        GET_SKILL,   //使宝可梦获得技能(技能ID), 生效前需要判断是否合理
        CAPTURE,    //精灵球类型(捕获率加成,对特定的Type属性的宝可梦,特定捕获率加成)
    };
public:
    Prop(int ID);
    Prop(Prop& prop);
    int GetID();
    void SetNum(int num);
    int GetNum();
    bool IsCanUseInBattle();
    bool IsCanUseInField();
    PROP_TYPE GetType();
    string GetName();
    string GetDescription();
    int GetPrice();
    int GetSellPrice();
    vector<int> GetEffectPara();
private:
    int ID;
    PROP_TYPE type;
    string name;
    string description;
    int num;
    int price;
    int sellPrice;              //出售价格为0的道具不能出售
    vector<int> effectPara;     //效果参数
    int canUseInBattle;      //是否可以在战斗中使用
    int canUseInField;       //是否可以在野外使用
};

#endif // !PROP_H
