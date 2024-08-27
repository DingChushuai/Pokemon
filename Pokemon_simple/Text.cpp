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
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	for (int i = 0; i < texts.size(); i++)
	{
		string text = texts[i].first;
		Color textColor = texts[i].second.first;
		Color backColor = texts[i].second.second;

        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        WORD attributes = 0;

        // 设置文本颜色
        switch (textColor) {
        case RED:
            attributes |= FOREGROUND_RED;
            break;
        case GREEN:
            attributes |= FOREGROUND_GREEN;
            break;
        case BLUE:
            attributes |= FOREGROUND_BLUE;
            break;
        case YELLOW:
            attributes |= FOREGROUND_RED | FOREGROUND_GREEN;
            break;
        case CYAN:
            attributes |= FOREGROUND_GREEN | FOREGROUND_BLUE;
            break;
        case MAGENTA:
            attributes |= FOREGROUND_RED | FOREGROUND_BLUE;
            break;
        case GRAY:
            attributes |= FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
            break;
        case BLACK:
            break;
        case None:
        default:
            attributes |= FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
            break;
        }

        // 设置背景颜色
        switch (backColor) {
        case RED:
            attributes |= BACKGROUND_RED;
            break;
        case GREEN:
            attributes |= BACKGROUND_GREEN;
            break;
        case BLUE:
            attributes |= BACKGROUND_BLUE;
            break;
        case YELLOW:
            attributes |= BACKGROUND_RED | BACKGROUND_GREEN;
            break;
        case CYAN:
            attributes |= BACKGROUND_GREEN | BACKGROUND_BLUE;
            break;
        case MAGENTA:
            attributes |= BACKGROUND_RED | BACKGROUND_BLUE;
            break;
        case GRAY:
            attributes |= BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
            break;
        case BLACK:
            break;
        case None:
        default:
            break;
        }
        SetConsoleTextAttribute(hConsole, attributes);
        cout << text;
	}
}


