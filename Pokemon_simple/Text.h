#pragma once
#ifndef TEXT_H
#define TEXT_H

#include <string>
#include <vector>
#include "Tools.h"
using namespace std;

class Text
{
    //每个Text对象在使用时建议只存放一行的文字
    //Color枚举类型定义在Tools.h中
public:
    Text();
    Text(string str, Color textColor = None, Color backColor = None);
    Text(const Text& other);

    void Add(string str, Color textColor = None, Color backColor = None);
    void SetColor(Color textColor = None, Color backColor = None);
    vector<pair<string, pair<Color, Color>>> GetTexts();
    void Clear();
    void Print();

private:
    vector<pair<string, pair<Color, Color>>> texts;
};

#endif // !TEXT_H
