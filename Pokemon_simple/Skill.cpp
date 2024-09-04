#include "Skill.h"
#include <fstream>
#pragma once

Skill::Skill(int skillID)
{
    ifstream file(SKILL_INFO_PATH);

    string line;
    vector<string> data;
    while (getline(file, line)) {
        data = Split(line, ',');
        int temp = stoi(data[0]);
        if (temp == skillID)
            break;
        else
            continue;
    }
    file.close();
    
    this->skillID = skillID;
    skillName = data[1];
    skillDescription = data[2];
    vector<int> temp(8);
    for (int i = 3; i < 10; ++i) {
        temp.push_back(stoi(data[i]));
    }
    type = (Type)(temp[0]);
    skillType = (SkillType)(temp[1]);
    power = temp[2];
    accuracy = temp[3];
    maxPP = temp[4];
    PP = maxPP;
    mustHit = temp[5];
    priority = temp[6];
    skillEffect = (SkillEffect)(temp[7]);
    vector<string>tempEffect = Split(data[11], '/');
    for (int i = 0; i < tempEffect.size(); ++i)
        effectParam.push_back(stoi(tempEffect[i]));
}
string Skill::GetTypeName(int typeID)
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