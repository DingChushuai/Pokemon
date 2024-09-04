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