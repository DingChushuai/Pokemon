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
		cout << texts[i].first << endl;
	}
}


