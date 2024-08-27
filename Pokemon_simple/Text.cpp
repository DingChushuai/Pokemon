#include "Text.h"
#include <iostream>
#include<windows.h>
using namespace std;

Text::Text()
{
	//do nothing
}

Text::Text(string str, Color textColor, Color backColor)
{
	Add(str, textColor, backColor);
}

Text::Text(const Text& other)
{
	//将other中的colorString深复制到当前对象中
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

	for(int i=0;i<texts.size();i++)
	{ 
		texts[i].second.first = textColor;
		texts[i].second.second = backColor;
	}

	//统一设置texts所有字符串的颜色
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
	//TODO: 遍历texts，打印出对应的color和str
	//此处为debug仅实现打印功能, 需要改写, 
	for (int i = 0; i < texts.size(); i++)
	{
		
		string a[2];
		int a1[2];
		a[0] = texts[i].second.first;
		a[1] = texts[i].second.second;
		for (int j = 0; j < 2; j++)
		{
			if (a[j] == "RED")a1[j] = 4;
			if (a[j] == "GREEN")a1[j] = 2;
			if (a[j] == "BLUE")a1[j] = 1;
			if (a[j] == "YELLOW")a1[j] = 6;
			if (a[j] == "CYAN")a1[j] = 9;
		}
		SetConsoleTextAttribute(a1[0],a1[1]);
		cout << texts[i].first << endl;
	}
}


