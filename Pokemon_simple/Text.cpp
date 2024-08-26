#include "Text.h"
#include <iostream>
using namespace std;

Text::Text()
{
	//do nothing
}

Text::Text(string str, Color textColor, Color backColor)
{
	Add(str, textColor, backColor);
}

Text::Text(Text& other)
{
	//��other�е�colorString��Ƶ���ǰ������
	for (int i = 0; i < other.texts.size(); i++)
	{
		texts.push_back(make_pair(other.texts[i].first, other.texts[i].second));
	}
}

void Text::Add(string str, Color textColor, Color backColor)
{
	texts.push_back(make_pair(str, make_pair(textColor, backColor)));
}

void Text::SetColor(Color textColor, Color backColor)
{
	//ͳһ����texts�����ַ�������ɫ
}

vector<pair<string, pair<Color, Color>>> Text::GetTexts()
{
	return texts;
}

void Text::Clear()
{
	texts.clear();
}

void Text::Print()
{
	//TODO: ����texts����ӡ����Ӧ��color��str
	//�˴�Ϊdebug��ʵ�ִ�ӡ����, ��Ҫ��д, 
	for (int i = 0; i < texts.size(); i++)
	{
		cout << texts[i].first << endl;
	}
}


