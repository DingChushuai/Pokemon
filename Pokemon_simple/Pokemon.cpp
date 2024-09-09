#include "Pokemon.h"
#pragma once
#include "Command.h"
#include "SoundPlayer.h"
#include<fstream>
#include<algorithm>
#include<random>
#include"tools.h"
Pokemon::Pokemon(int ID, int level)
{
    //�� POKEMON_INFO_PATH �ж�ȡID��Ӧ�ı�������Ϣ
    //����һ������ĵȼ�Ϊlevel�ı�����
    ifstream ifs;
    ifs.open(POKEMON_INFO_PATH, ios::in);
    string rea;
    vector<string> data;
    vector<string>ethnic;
    vector<string>fault;
    vector<int> skill;
    int l;
    while (getline(ifs, rea))
    {
        data = Split(rea, ',');
        int temp = stoi(data[0]);
        if (temp == ID)
            break;
        else
            continue;
    }
    this->ID = ID;
    name = data[1];
    type.first = (Type)stoi(data[2]);
    type.second = (Type)stoi(data[3]);
    growthRate = stoi(data[4]);
    captureRate = stoi(data[5]);
    basicExperience = stoi(data[6]);
    ethnic = Split(data[7], '/');
    ethnicValue.hp = stoi(ethnic[0]);
    ethnicValue.attack = stoi(ethnic[1]);
    ethnicValue.defense = stoi(ethnic[2]);
    ethnicValue.specialAttack = stoi(ethnic[3]);
    ethnicValue.specialDefense = stoi(ethnic[4]); 
    ethnicValue.speed = stoi(ethnic[5]); 
    fault = Split(data[8], '/');
    for (int i = 0; i < fault.size(); i+=2)
    {
        l = stoi(fault[i + 1]);
        if (level >= l) skill.push_back(stoi(fault[i]));
    }
    if (skill.size() < 4)
    {
        for (int i = 0; i < skill.size(); i++)
        {
            skills.push_back(Skill(skill[i]));
        }
    }
    else
    {
        random_device rd;
        mt19937 g(rd());
        shuffle(skill.begin(), skill.end(), g);
        vector<int>result(skill.begin(), skill.begin() + 4);
        for (int k = 0; k < result.size(); k++)
        {
            skills.push_back(Skill(result[k]));
        }

    }
    evolutionLevel = stoi(data[9]);
    evolutionID = stoi(data[10]);
    this->level = level;
    experience = 0;
    experienceToNextLevel = CalculateExperienceToNextLevel();
    individualValue = GetRandomIndividualValue();
    statu = None;
    buff = {0};
    basicValue = { 0 };
    UpdateAttribute();
    this->attribute.hp = this->attribute.maxHp;
}

Pokemon::Pokemon(const Pokemon& other)
{
    ID = other.ID;
    name = other.name;
    type = other.type;
    level = other.level;
    experience = other.experience;
    experienceToNextLevel = other.experienceToNextLevel;
    attribute = other.attribute;
    statu = other.statu; 
    skills = other.skills;
    evolutionLevel = other.evolutionLevel;
    evolutionID = other.evolutionID;
    captureRate = other.captureRate;
    ethnicValue = other.ethnicValue;
    individualValue = other.individualValue;
    basicValue = other.basicValue;
    growthRate = other.growthRate;
    basicExperience = other.basicExperience;
}

Pokemon::~Pokemon()
{
    //do nothing
}

vector<Text> Pokemon::GetDetail()
{
    vector<Text> info;
    info.push_back(Text("����������: " + name +"\n"));
    info.push_back(Text("�����εȼ�: " + to_string(level) + "  "));
    info.push_back(Text("�����ξ���: " + to_string(experience) + "/" + to_string(experienceToNextLevel) + "\n"));
    info.push_back(Text("������״̬: " + GetStatuName(statu) + "\n"));
    info.push_back(Text("����������: " + GetTypeName(type.first) + "  " + GetTypeName(type.second) + "\n"));
    info.push_back(Text("�����θ���ֵ: " + to_string(individualValue.hp) + "/" + to_string(individualValue .attack) + "/" + to_string(individualValue.defense) + "/" + to_string(individualValue.speed) + "/" + to_string(individualValue.specialAttack) + "/" + to_string(individualValue.specialDefense) + "\n"));
    info.push_back(Text("�����λ���ֵ: " + to_string(basicValue.hp) + "/" + to_string(basicValue.attack) + "/" + to_string(basicValue.defense) + "/" + to_string(basicValue.speed) + "/" + to_string(basicValue.specialAttack) + "/" + to_string(basicValue.specialDefense) + "\n")); 
    info.push_back(Text("����������ֵ: " + to_string(attribute.hp) + "/" + to_string(attribute.attack) + "/" + to_string(attribute.defense) + "/" + to_string(attribute.speed) + "/" + to_string(attribute.specialAttack) + "/" + to_string(attribute.specialDefense) + "\n"));   
    info.push_back(Text("�����μ���:\n"));
    for (int i = 0; i < skills.size(); i++)
    {
        info.push_back(Text(skills[i].skillName + "  "));
        info.push_back(Text("PP: " + to_string(skills[i].PP) + "/" + to_string(skills[i].maxPP) + "  "));
        info.push_back(Text("����: " + to_string(skills[i].power) + "  "));
        info.push_back(Text("����: " + to_string(skills[i].accuracy) + "  "));
        info.push_back(Text("����: " + GetTypeName(skills[i].type) + " \n"));
        info.push_back(Text("\t"+skills[i].skillDescription + "\n"));
    }
    return info;
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
    Text text; 
    while (CanLevelUp())
    {
        level++;
        if (level == evolutionLevel) text = Evolve();
        experience -= experienceToNextLevel;
        experienceToNextLevel = CalculateExperienceToNextLevel();
        UpdateAttribute();
        attribute.hp = attribute.maxHp;
        statu = None;
    }
    ifstream ifs; 
    ifs.open(POKEMON_INFO_PATH, ios::in); 
    string rea; 
    vector<string> data; 
    vector<string>fault; 
    vector<int> skill; 
    Command cmd;
    while (getline(ifs, rea)) 
    {
        data = Split(rea, ','); 
        int temp = stoi(data[0]); 
        if (temp == ID) 
            break;
    }
    fault = Split(data[8], '/');
    for (int i = 0; i < fault.size(); i += 2)
    {
        if (level== stoi(fault[i + 1])) 
        {
            ClearScreen();
            if (skills.size() < 4)
            {
                Skill s(stoi(fault[i])); 
                text.Add("��ı�����");
                text.Add(name, GREEN);
                text.Add("ѧ����");
                text.Add(s.skillName, YELLOW);
                text.Add("!");
                skills.push_back(s);
            }
            else
            {
                Skill s(stoi(fault[i]));
                Text("��ı�����ѧϰ���¼���:" + s.skillName+ "!ѡ��һ�������滻(ESCȡ���滻)\n").Print();
                Text(s.skillName + "  PP:" + to_string(s.PP) + "/" + to_string(s.maxPP) + "  ����:" + GetTypeName(s.type) + "  ����:" + to_string(s.power) + "  ����:" + to_string(s.accuracy)).Print();  
                Text("\n��������:"+s.skillDescription).Print();
                Text("\n��ı����ε�ǰ�����б�:\n").Print();
                vector<Text> infos;
                for (int i = 0; i < skills.size(); i++)
                {
                    string info = skills[i].skillName + "  PP:" + to_string(skills[i].PP) + "/" + to_string(skills[i].maxPP);
                    info += "  ����:" + GetTypeName(skills[i].type) + "  ����:" + to_string(skills[i].power) +  " ����:" + to_string(skills[i].accuracy); 
                    infos.push_back(Text(info));
                }
                int index = cmd.chooseFromList(infos);
                if (index != 0)
                {
                    
                    text.Add("��ı�����");
                    text.Add(name, GREEN);
                    text.Add("������");
                    text.Add(skills[index - 1].skillName, YELLOW);
                    text.Add("!");
                    skills[index - 1] = s;
                    text.Add("��ı�����");
                    text.Add(name, GREEN);
                    text.Add("ѧ����");
                    text.Add(s.skillName, YELLOW);
                    text.Add("!");
                }
            }
        }
    }
    text.Add("��ı�����");
    text.Add(name, GREEN);
    text.Add("����");
    text.Add(to_string(level), YELLOW);
    text.Add("����!");
    return text;
}

Text Pokemon::Evolve()
{
    Pokemon* sample =new Pokemon(evolutionID,level);
    string info = "��ı�����";
    info += name;
    info += "��������";
    info += sample->name;
    info += "!";
    ID = sample->ID;
    name = sample->name;
    type = sample->type;
    evolutionID = sample->evolutionID;
    evolutionLevel = sample->evolutionLevel;
    basicExperience = sample->basicExperience;
    growthRate = sample->growthRate;
    captureRate = sample->captureRate;
    ethnicValue = sample->ethnicValue;
    SoundPlayer s;
    s.Play_Sound(SoundPlayer::SOUND_JINHUA);
    return Text(info,GREEN);
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

void Pokemon::AddBasicValue(Value add)
{
    basicValue.hp+=add.hp;
    basicValue.attack+=add.attack; 
    basicValue.defense+=add.defense;
    basicValue.speed+=add.speed;
    basicValue.specialAttack+=add.specialAttack;
    basicValue.specialDefense+=add.specialDefense;
    UpdateAttribute();
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
        return 1.2 * pow(level, 3) - 15 * pow(level, 2) + 100*level- 140;
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

