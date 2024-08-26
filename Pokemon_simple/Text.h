#pragma once
#ifndef TEXT_H
#define TEXT_H

#include <string>
#include <vector>
#include "Tools.h"
using namespace std;

class Text
{
    //ÿ��Text������ʹ��ʱ����ֻ���һ�е�����
    //Colorö�����Ͷ�����Tools.h��
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
