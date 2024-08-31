#include "Pokemon.h"
#pragma once

Pokemon::Pokemon(int ID, int level)
{
    //TODO:
    //���캯��
    //�� POKEMON_INFO_PATH �ж�ȡID��Ӧ�ı�������Ϣ
    //����һ������ĵȼ�Ϊlevel�ı�����
    //POKEMON_INFO_PATH��û�е���Ϣ�趨:
    this->level = level;
    experience = 0;
    experienceToNextLevel = CalculateExperienceToNextLevel();
    statu = None;
    buff = {0};
    basicValue = { 0 };
    //����ֵGetRandomIndividualValue();
    UpdateAttribute();  //�������ֵ,����ֵ��,�������� 
    //����: �����п���ѧϰ�ļ��������ѡ��4��
}

Pokemon::Pokemon(const Pokemon& other)
{
    //TODO:
    //�������캯��
    //�������������ε���������
    //ע��: ������Buff
}

Pokemon::~Pokemon()
{
    //do nothing
}

vector<Text> Pokemon::GetDetail()
{
    //TODO:
    //���ر����ε���ϸ��Ϣ, ��������������Ϣ
    //�Ժÿ��Ĳ�ɫ�ı���ʽ����
    //���÷���evolutionLevel,evolutionID,captureRate,ethnicValue,growthRate,basicExperience
    return vector<Text>();
}

int Pokemon::GetSellPrice()
{
    //���ر����εĳ��ۼ۸�
    //���ۼ۸�ʽ: 
    //����û�и���,��Ϊ�Զ��幫ʽ
    //���ۼ۸� = (�����εȼ� * 10) + (�����θ���ֵ�ܺ� * 2) + (�����λ�������)
    int allEthnicValue = ethnicValue.hp + ethnicValue.attack + ethnicValue.defense + ethnicValue.speed + ethnicValue.specialAttack + ethnicValue.specialDefense;
    return level * 10 + allEthnicValue * 2 + basicExperience;
}

string Pokemon::GetTypeName(int typeID)
{
    string type = "";
    switch (typeID)
    {
    case 0: type = "һ��"; break; 
    case 1: type = "��"; break; 
    case 2: type = "����"; break; 
    case 3: type = "��"; break; 
    case 4: type = "����"; break; 
    case 5: type = "��ʯ"; break;
    case 6: type = "��"; break;
    case 7: type = "����"; break;
    case 8: type = "��"; break;
    case 9: type = "��"; break;
    case 10: type = "ˮ"; break;
    case 11: type = "��"; break;
    case 12: type = "��"; break;
    case 13: type = "������"; break;
    case 14: type = "��"; break;
    case 15: type = "��"; break;
    case 16: type = "��"; break;
    case 17: type = "����"; break;
    }
    return type;
}

string Pokemon::GetStatuName(int statuID)
{
    string statu = "";
    switch (statuID)
    {
        case None: statu = "����"; break;
        case Poison: statu = "�ж�"; break; 
        case Paralysis: statu = "���"; break;
        case Burn: statu = "����"; break;
        case Sleep: statu = "˯��"; break;
        case Freeze: statu = "����"; break;
        case Frostbite: statu = "����"; break;
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
    //��������ο�������, ������
    //�������ѧϰ�¼���, ��ѧϰ�¼���,��ѡ�������ɼ���(ʹ��Command��)
    //������Խ���, �����
    //���¼����������辭��ֵ
    //��������ֵ
    // ����Ѫ,����״̬
    //��������/������Ϣ

    return Text();
}

Text Pokemon::Evolve()
{
    //TODO:
    //��������ο��Խ���, �����
    //�������ѧϰ�¼���, ��ѧϰ�¼���,��ѡ�������ɼ���(ʹ��Command��)
    //�������һ��������ı�������Ϊ����,
    //���ı����ε�ID, ����, ���� ��
    //ע��: ��������ֵ, ��������ֵ,�������ĸ���ֵ�ͻ�������
    //��������ֵ
    //���ؽ�����Ϣ
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
    text.Add("��ı�����");
    text.Add(name,GREEN);
    text.Add("�����");
    text.Add(to_string(experience),YELLOW);
    text.Add("����ֵ!");
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

