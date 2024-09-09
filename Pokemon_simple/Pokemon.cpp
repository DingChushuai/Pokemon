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
    //从 POKEMON_INFO_PATH 中读取ID对应的宝可梦信息
    //生成一个随机的等级为level的宝可梦
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
    info.push_back(Text("宝可梦名称: " + name +"\n"));
    info.push_back(Text("宝可梦等级: " + to_string(level) + "  "));
    info.push_back(Text("宝可梦经验: " + to_string(experience) + "/" + to_string(experienceToNextLevel) + "\n"));
    info.push_back(Text("宝可梦状态: " + GetStatuName(statu) + "\n"));
    info.push_back(Text("宝可梦类型: " + GetTypeName(type.first) + "  " + GetTypeName(type.second) + "\n"));
    info.push_back(Text("宝可梦个体值: " + to_string(individualValue.hp) + "/" + to_string(individualValue .attack) + "/" + to_string(individualValue.defense) + "/" + to_string(individualValue.speed) + "/" + to_string(individualValue.specialAttack) + "/" + to_string(individualValue.specialDefense) + "\n"));
    info.push_back(Text("宝可梦基础值: " + to_string(basicValue.hp) + "/" + to_string(basicValue.attack) + "/" + to_string(basicValue.defense) + "/" + to_string(basicValue.speed) + "/" + to_string(basicValue.specialAttack) + "/" + to_string(basicValue.specialDefense) + "\n")); 
    info.push_back(Text("宝可梦属性值: " + to_string(attribute.hp) + "/" + to_string(attribute.attack) + "/" + to_string(attribute.defense) + "/" + to_string(attribute.speed) + "/" + to_string(attribute.specialAttack) + "/" + to_string(attribute.specialDefense) + "\n"));   
    info.push_back(Text("宝可梦技能:\n"));
    for (int i = 0; i < skills.size(); i++)
    {
        info.push_back(Text(skills[i].skillName + "  "));
        info.push_back(Text("PP: " + to_string(skills[i].PP) + "/" + to_string(skills[i].maxPP) + "  "));
        info.push_back(Text("威力: " + to_string(skills[i].power) + "  "));
        info.push_back(Text("命中: " + to_string(skills[i].accuracy) + "  "));
        info.push_back(Text("类型: " + GetTypeName(skills[i].type) + " \n"));
        info.push_back(Text("\t"+skills[i].skillDescription + "\n"));
    }
    return info;
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
                text.Add("你的宝可梦");
                text.Add(name, GREEN);
                text.Add("学会了");
                text.Add(s.skillName, YELLOW);
                text.Add("!");
                skills.push_back(s);
            }
            else
            {
                Skill s(stoi(fault[i]));
                Text("你的宝可梦学习了新技能:" + s.skillName+ "!选择一个技能替换(ESC取消替换)\n").Print();
                Text(s.skillName + "  PP:" + to_string(s.PP) + "/" + to_string(s.maxPP) + "  类型:" + GetTypeName(s.type) + "  威力:" + to_string(s.power) + "  命中:" + to_string(s.accuracy)).Print();  
                Text("\n技能描述:"+s.skillDescription).Print();
                Text("\n你的宝可梦当前技能列表:\n").Print();
                vector<Text> infos;
                for (int i = 0; i < skills.size(); i++)
                {
                    string info = skills[i].skillName + "  PP:" + to_string(skills[i].PP) + "/" + to_string(skills[i].maxPP);
                    info += "  类型:" + GetTypeName(skills[i].type) + "  威力:" + to_string(skills[i].power) +  " 命中:" + to_string(skills[i].accuracy); 
                    infos.push_back(Text(info));
                }
                int index = cmd.chooseFromList(infos);
                if (index != 0)
                {
                    
                    text.Add("你的宝可梦");
                    text.Add(name, GREEN);
                    text.Add("忘记了");
                    text.Add(skills[index - 1].skillName, YELLOW);
                    text.Add("!");
                    skills[index - 1] = s;
                    text.Add("你的宝可梦");
                    text.Add(name, GREEN);
                    text.Add("学会了");
                    text.Add(s.skillName, YELLOW);
                    text.Add("!");
                }
            }
        }
    }
    text.Add("你的宝可梦");
    text.Add(name, GREEN);
    text.Add("升到");
    text.Add(to_string(level), YELLOW);
    text.Add("级了!");
    return text;
}

Text Pokemon::Evolve()
{
    Pokemon* sample =new Pokemon(evolutionID,level);
    string info = "你的宝可梦";
    info += name;
    info += "进化成了";
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

