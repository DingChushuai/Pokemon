#include "Skill.h"
#include <fstream>

Skill::Skill(int skillID)
{
    ifstream file("Skill_Info.csv");

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
        temp[i - 3] = stoi(data[i]);
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
