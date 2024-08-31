#include "Pokemon.h"
#pragma once

Pokemon::Pokemon(int ID, int level)
{
    //TODO:
    //构造函数
    //从 POKEMON_INFO_PATH 中读取ID对应的宝可梦信息
    //生成一个随机的等级为level的宝可梦
    //POKEMON_INFO_PATH中没有的信息设定:
    this->level = level;
    experience = 0;
    experienceToNextLevel = CalculateExperienceToNextLevel();
    statu = None;
    buff = {0};
    basicValue = { 0 };
    //个体值GetRandomIndividualValue();
    UpdateAttribute();  //完成种族值,个体值后,更新属性 
    //技能: 从所有可以学习的技能中随机选择4个
}

Pokemon::Pokemon(const Pokemon& other)
{
    //TODO:
    //拷贝构造函数
    //拷贝其他宝可梦的所有属性
    //注意: 不拷贝Buff
}

Pokemon::~Pokemon()
{
    //do nothing
}

vector<Text> Pokemon::GetDetail()
{
    //TODO:
    //返回宝可梦的详细信息, 几乎包括所有信息
    //以好看的彩色文本形式返回
    //不用返回evolutionLevel,evolutionID,captureRate,ethnicValue,growthRate,basicExperience
    return vector<Text>();
}

int Pokemon::GetSellPrice()
{
    //返回宝可梦的出售价格
    //出售价格公式: 
    //官网没有给出,此为自定义公式
    //出售价格 = (宝可梦等级 * 10) + (宝可梦个体值总和 * 2) + (宝可梦基础经验)
    int allEthnicValue = ethnicValue.hp + ethnicValue.attack + ethnicValue.defense + ethnicValue.speed + ethnicValue.specialAttack + ethnicValue.specialDefense;
    return level * 10 + allEthnicValue * 2 + basicExperience;
}

string Pokemon::GetTypeName(int typeID)
{
    string type = "";
    switch (typeID)
    {
    case 0: type = "一般"; break; 
    case 1: type = "格斗"; break; 
    case 2: type = "飞行"; break; 
    case 3: type = "毒"; break; 
    case 4: type = "地面"; break; 
    case 5: type = "岩石"; break;
    case 6: type = "虫"; break;
    case 7: type = "幽灵"; break;
    case 8: type = "钢"; break;
    case 9: type = "火"; break;
    case 10: type = "水"; break;
    case 11: type = "草"; break;
    case 12: type = "电"; break;
    case 13: type = "超能力"; break;
    case 14: type = "冰"; break;
    case 15: type = "龙"; break;
    case 16: type = "恶"; break;
    case 17: type = "妖精"; break;
    }
    return type;
}

string Pokemon::GetStatuName(int statuID)
{
    string statu = "";
    switch (statuID)
    {
        case None: statu = "正常"; break;
        case Poison: statu = "中毒"; break; 
        case Paralysis: statu = "麻痹"; break;
        case Burn: statu = "灼伤"; break;
        case Sleep: statu = "睡眠"; break;
        case Freeze: statu = "冰冻"; break;
        case Frostbite: statu = "冻伤"; break;
    }
    return statu;
}

bool Pokemon::CanLevelUp() 
{
    if(level >= 100) return false;
    return experience >= experienceToNextLevel; 
}

Text Pokemon::LevelUp()
{
    //TODO:
    //如果宝可梦可以升级, 则升级
    //如果可以学习新技能, 则学习新技能,并选择遗忘旧技能(使用Command类)
    //如果可以进化, 则进化
    //重新计算升级所需经验值
    //更新能力值
    // 回满血,消除状态
    //返回升级/进化信息

    return Text();
}

Text Pokemon::Evolve()
{
    //TODO:
    //如果宝可梦可以进化, 则进化
    //如果可以学习新技能, 则学习新技能,并选择遗忘旧技能(使用Command类)
    //随机生成一个进化后的宝可梦作为依据,
    //更改宝可梦的ID, 名称, 类型 等
    //注意: 更改种族值, 基础经验值,但不更改个体值和基础点数
    //更新能力值
    //返回进化信息
    return Text();
}

int Pokemon::GetBasicExperience()
{
    return basicExperience; 
}

Text Pokemon::GetExperience(int experience)
{
    this->experience += experience;
    Text text;
    text.Add("你的宝可梦");
    text.Add(name,GREEN);
    text.Add("获得了");
    text.Add(to_string(experience),YELLOW);
    text.Add("经验值!");
    return text;
}

int Pokemon::GetCaptureRate()
{
    return captureRate; 
}

void Pokemon::GetBasicValue(Value add)
{
    basicValue.hp+=add.hp;
    basicValue.attack+=add.attack; 
    basicValue.defense+=add.defense;
    basicValue.speed+=add.speed;
    basicValue.specialAttack+=add.specialAttack;
    basicValue.specialDefense+=add.specialDefense;
}

float Pokemon::GetBuffValue(int buffLevel)
{
    float A = 1.0f;
    switch (buffLevel)
    {
    case -6: A *= 0.25f; break;
    case -5: A *= 0.28f; break;
    case -4: A *= 0.33f; break;
    case -3: A *= 0.40f; break;
    case -2: A *= 0.50f; break;
    case -1: A *= 0.66f; break;
    case  0: A *= 1.00f; break;
    case  1: A *= 1.50f; break;
    case  2: A *= 2.00f; break;
    case  3: A *= 2.50f; break;
    case  4: A *= 3.00f; break;
    case  5: A *= 3.50f; break;
    case  6: A *= 4.00f; break;
    }
    return A;
}

void Pokemon::UpdateAttribute()
{
    ATTRIBUTE newAttribute = CalculateAttribute();
    attribute.maxHp = newAttribute.hp;
    attribute.attack = newAttribute.attack; 
    attribute.defense = newAttribute.defense; 
    attribute.speed = newAttribute.speed; 
    attribute.specialAttack = newAttribute.specialAttack; 
    attribute.specialDefense = newAttribute.specialDefense;
}

Pokemon::Value Pokemon::GetRandomIndividualValue()
{
    Value individualValue;
    individualValue.hp = rand() % 16; 
    individualValue.attack = rand() % 16; 
    individualValue.defense = rand() % 16; 
    individualValue.speed = rand() % 16; 
    individualValue.specialAttack = rand() % 16; 
    individualValue.specialDefense = rand() % 16;
    return individualValue; 
}

int Pokemon::ExperienceOfLevel(int level)
{
    switch (growthRate)
    {
    case 0:
        if (level <= 15) return 0.02 * pow(level, 3) * (level + 73) / 3;
        else if (level <= 36) return 0.02 * pow(level, 4) + 0.28 * pow(level, 3);
        else return 0.02 * pow(level, 3) + (level + 64) / 2;
    case 1:
        return 1.25 * pow(level, 3);
    case 2:
        return 1.2 * pow(level, 3) - 15 * pow(level, 2) - 140;
    case 3:
        return pow(level, 3);
    case 4:
        return 0.8 * pow(level, 3);
    case 5:
        if (level <= 50) return -0.02 * pow(level, 4) + 2 * pow(level, 3);
        else if (level <= 68) return -0.01 * pow(level, 4) + 1.5 * pow(level, 3);
        else if (level <= 98) return -0.002 * pow(level, 3) * (1911 - 10 * level) / 3;
        else return -0.01 * pow(level, 4) + 1.6 * pow(level, 3);
    }
}

int Pokemon::CalculateExperienceToNextLevel()
{
    return ExperienceOfLevel(level + 1) - ExperienceOfLevel(level);
}

Pokemon::ATTRIBUTE Pokemon::CalculateAttribute()
{
    ATTRIBUTE newAttribute;
    newAttribute.hp = (int)(ethnicValue.hp + individualValue.hp + sqrt(basicValue.hp)/8)*level/50 + 10 + level;
    newAttribute.attack = (int)(ethnicValue.attack + individualValue.attack + sqrt(basicValue.attack) / 8) * level / 50 + 5; 
    newAttribute.defense = (int)(ethnicValue.defense + individualValue.defense + sqrt(basicValue.defense) / 8) * level / 50 + 5; 
    newAttribute.speed = (int)(ethnicValue.speed + individualValue.speed + sqrt(basicValue.speed) / 8) * level / 50+ 5; 
    newAttribute.specialAttack = (int)(ethnicValue.specialAttack + individualValue.specialAttack + sqrt(basicValue.specialAttack) / 8) * level / 50 + 5; 
    newAttribute.specialDefense = (int)(ethnicValue.specialDefense + individualValue.specialDefense + sqrt(basicValue.specialDefense) / 8) * level / 50 + 5; 
    return newAttribute;
}

