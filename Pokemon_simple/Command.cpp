#include "Command.h"
#include <conio.h>
#include "tools.h"
#pragma once

char Command::GetCommand(vector<char> possibleCommands)
{
    //接收用户输入且不回显
    //可以使用getch()函数
    //直到用户输入的字符在possibleCommands中
    //否则继续接收
    //返回用户输入的字符
    char input;
    while (true)
    {
        input = _getch();
        if (find(possibleCommands.begin(), possibleCommands.end(), input) != possibleCommands.end())
            break;
    }
    return input;
}

bool Command::DoubleConfirmation(Text message)
{
    //弹出确认对话框
    //message为对话框内容
    //使用ChooseList类
    //返回用户是否确认
    vector<Text> Menu;
    Menu.push_back(Text("1. 是"));
    Menu.push_back(Text("2. 否"));
    vector<char> possibleCommands = { UP, LEFT, DOWN, RIGHT, YES, ESC };
    ChooseList MenuList(Menu);
    char command;
    do {
        MenuList.ShowList();
        command = GetCommand(possibleCommands);
        switch (command)
        {
        case UP:
        case LEFT:
            MenuList.SelectUp();
            break;
        case DOWN:
        case RIGHT:
            MenuList.SelectDown();
            break;
        case YES:
            return !MenuList.chooseNow;
        case ESC:
            return false;
        }
    } while (true);

    return false;
}

Command::Command()
{
    //do nothing
}

Command::~Command()
{
    //do nothing
}

void Command::Pause()
{
    _getch();   //等待用户按键
}

int Command::chooseFromList(vector<Text> list, int showMax)
{
    ChooseList chooseList(list, showMax);   //创建选择列表
    SoundPlayer s; 
    vector<char> possibleCommands = { UP, LEFT, DOWN, RIGHT, YES, ESC };
    char command;
    do {
        chooseList.ShowList();
        command = GetCommand(possibleCommands);     //获取用户输入
        s.Play_Sound(SoundPlayer::SOUND_CHOOSE);    //播放选择音效
        switch (command)
        {
        case UP:
        case LEFT:
            chooseList.SelectUp();
            break;
        case DOWN:
        case RIGHT:
            chooseList.SelectDown();
            break;
        case YES:
            return chooseList.chooseNow + 1;
        case ESC:
            return 0;
        }
    } while (true);
}

void Command::PrintfList(vector<Text> list)
{
    for (int i = 0; i < list.size(); i++)
    {
        list[i].Print();
    }
}

int Command::ChooseCount(int max)
{
    //选择数量
    //max为最大数量,在外部计算
    //返回用户选择的数量
    //可以通过按'/'输入具体数量
    //如果用户按'ESC'则返回0
    //'/'输入的数量必须大于0且小于等于max,否则重新输入,直到输入正确
    int count = 1;
    Text message("请选择数量：");
    message.Print();
    pair<int, int> pos = GetPos();
    while (true)
    {
        string str = to_string(count);
        string str2 = to_string(max);
        GotoXY(pos.first, pos.second);
        Text(str).Print();
        Text(" / ").Print();
        Text(str2).Print();
        Text("    ").Print();
        char command = GetCommand({ UP, LEFT, DOWN, RIGHT, YES, ESC ,'/'});
        switch (command)
        {
        case UP:
        case LEFT:
            if (count > 1)
                count--;
            break;
        case DOWN:
        case RIGHT:
            if (count < max)
                count++;
            break;
        case YES:
            return count;
        case ESC:
            return 0;
        case '/':
            Text("\n请输入具体数量").Print();
            int n;
            do
            {
                if (cin.fail())
                {
                    cin.clear();
                    cin.ignore(1024, '\n');
                }
                cin >> n;
            }while (n <= 0 || n > max);
            return n;
        }
    }
}
using namespace std;
ChooseList::ChooseList(vector<Text> list)
{
    //初始化选择列表,将所有字符串长度补齐,以便整齐显示
    //初始化选择并高亮第一个选择
    maxstrlen = 0;
    vector<Text> listNew = list;
    for (int i = 0; i < list.size(); i++)
    {
        int len = list[i].GetTexts()[0].first.size();
        if (len > maxstrlen) maxstrlen = len;
    }
    for (int i = 0; i < list.size(); i++)
    {
        Text t = list[i];
        vector<pair<string, pair<Color, Color>>> texts = t.GetTexts();
        for (int j = 0; j < texts.size(); j++)
        {
            //将字符串长度补齐
            for (int k = texts[j].first.size(); k < maxstrlen; k++)
                texts[j].first += " ";
            texts[j].first += "\n";
        }
        Text tNew(texts);
        listNew.push_back(tNew);
    }
    this->list = listNew;
    startLine = -1;
}

ChooseList::ChooseList(vector<Text> list, int showMax)
{
    //同上
    maxstrlen = 0;
    vector<Text> listNew;
    for (int i = 0; i < list.size(); i++)
    {
        int len = list[i].GetTexts()[0].first.size();
        if (len > maxstrlen) maxstrlen = len;
    }
    for (int i = 0; i < list.size(); i++)
    {
        Text t = list[i];
        vector<pair<string, pair<Color, Color>>> texts = t.GetTexts();
        for (int j = 0; j < texts.size(); j++)
        {
            //将字符串长度补齐
            for (int k = texts[j].first.size(); k < maxstrlen; k++)
                texts[j].first += " ";
            texts[j].first += "\n";
        }
        Text tNew(texts);
        listNew.push_back(tNew);
    }
    this->list = listNew;
    startLine = -1;
    if (showMax > list.size())
        showMax = list.size();
    this->showMax = showMax;
}

void ChooseList::SetSelect(int select)
{
    //更改选择
    if (select < 0 || select >=list.size())
        throw "choose list index out of range";
    if (select == chooseNow)
        return;
    list[chooseNow].SetColor(None, None);
    chooseNow = select;
    list[chooseNow].SetColor(None, GREEN);
}

void ChooseList::ShowList()
{
    //显示选择列表
    //如果showMax小于list.size(),则只显示showMax个,并且可以上下滚动
    // 如果showMax大于等于list.size(),则显示全部
    int n = list.size();
    if (startLine == -1)
    {
        //初始化第一次选择
        chooseNow = 0;
        list[chooseNow].SetColor(None, GREEN);
        pair<int, int> pos = GetPos();
        startLine = pos.second;
    }
    if (showMax >=n)
    {
        //显示全部
        if (firstShow)
        {
            for (int i = 0; i < list.size(); i++)
            {
                list[i].Print();
            }
            firstShow = false;
        }
        pair<int, int> pos = GetPos();
        //处理特殊情况
        if (list.size() == 1)
        {
            GotoXY(0, startLine);
            list[chooseNow].Print();
        }
        else if (chooseNow == 0)
        {
            GotoXY(0,startLine);
            list[chooseNow].Print();
            GotoXY(0, startLine + 1);
            list[chooseNow + 1].Print();
        }
        else if (chooseNow == list.size()-1)
        {
            GotoXY(0,startLine + list.size() - 2);
            list[chooseNow - 1].Print();
            GotoXY(0, startLine + list.size() - 1);
            list[chooseNow].Print();
        }
        else
        {
            GotoXY(0,startLine + chooseNow - 1);
            list[chooseNow - 1].Print();
            GotoXY(0, startLine + chooseNow);
            list[chooseNow].Print();
            GotoXY(0, startLine + chooseNow + 1);
            list[chooseNow + 1].Print();
        }
        GotoXY(pos.first, pos.second);
        return;
    }
    //滚动显示逻辑
    GotoXY(0, startLine);
    int showStart, showEnd;
    if (chooseNow < showMax / 2)
    {
        showStart = 0;
        showEnd = showMax;
        for (int i = showStart; i <= showEnd; i++)
        {
            list[i].Print();
        }
        Text("▼", Color::YELLOW).Print();   //显示箭头,表示可以向下滚动
        string str = "";
        for (int i = 0; i < maxstrlen; i++)
            str += " ";
        str += "\n";
        Text(str).Print();
    }
    else if (chooseNow > n - 1 - showMax / 2)
    {
        showStart = n - showMax -1;
        showEnd = n-1;
        Text("▲", Color::YELLOW).Print();
        string str = "";
        for (int i = 0; i < maxstrlen; i++)
            str += " ";
        str += "\n";
        Text(str).Print();
        for (int i = showStart; i <= showEnd; i++)
        {
            list[i].Print();
        }
    }
    else
    {
        showStart = chooseNow - showMax / 2;
        showEnd = chooseNow + showMax / 2;
        Text("▲", Color::YELLOW).Print();
        string str = "";
        for (int i = 0; i < maxstrlen; i++)
            str += " ";
        str += "\n";
        Text(str).Print();
        for (int i = showStart; i <= showEnd; i++)
        {
            list[i].Print();
        }
        Text("▼", Color::YELLOW).Print();
        str = "";
        for (int i = 0; i < maxstrlen; i++)
            str += " ";
        str += "\n";
        Text(str).Print();
    }

}

void ChooseList::SelectUp()
{
    if (chooseNow == 0)
        return;
    SetSelect(chooseNow - 1);
}

void ChooseList::SelectDown()
{
    if (chooseNow == list.size() - 1)
        return;
    SetSelect(chooseNow + 1);
}
