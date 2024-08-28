#include "Command.h"
#include <conio.h>
#include "tools.h"

char Command::GetCommand(vector<char> possibleCommands)
{
    //�����û������Ҳ�����
    //����ʹ��getch()����
    //ֱ���û�������ַ���possibleCommands��
    //�����������
    //�����û�������ַ�
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
    //����ȷ�϶Ի���
    //messageΪ�Ի�������
    //ʹ��ChooseList��
    //�����û��Ƿ�ȷ��
    vector<Text> Menu;
    Menu.push_back(Text("1. ��"));
    Menu.push_back(Text("2. ��"));
    //ʾ������
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
}

Command::~Command()
{
}

int Command::chooseFromList(vector<Text> list, int showMax)
{
    ChooseList chooseList(list, showMax);
    vector<char> possibleCommands = { UP, LEFT, DOWN, RIGHT, YES, ESC };
    char command;
    do {
        chooseList.ShowList();
        command = GetCommand(possibleCommands);
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

ChooseList::ChooseList(vector<Text> list)
{
    if (list.size() == 0)
        throw "choose list is empty";
    this->list = list;
    chooseNow = 0;
    list[chooseNow].SetColor(None, GREEN);
    startLine = -1;
}

ChooseList::ChooseList(vector<Text> list, int showMax)
{
    if (list.size() == 0)
        throw "choose list is empty";
    this->list = list;
    chooseNow = 0;
    list[chooseNow].SetColor(None, GREEN);
    if (showMax > list.size())
        showMax = list.size();
    startLine = -1;
    this->showMax = showMax;
}

void ChooseList::SetSelect(int select)
{
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
    int n = list.size();
    if (startLine == -1)
    {
        pair<int, int> pos = GetPos();
        startLine = pos.second;
    }
    if (showMax >=n)
    {
        static bool first = true;
        if (first)
        {
            for (int i = 0; i < list.size(); i++)
            {
                list[i].Print();
            }
            first = false;
        }
        pair<int, int> pos = GetPos();
        if (chooseNow == 0)
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
        return;
    }

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
        Text("��                                 \n", Color::YELLOW).Print();
    }
    else if (chooseNow > n - 1 - showMax / 2)
    {
        showStart = n - showMax -1;
        showEnd = n-1;
        Text("��                                 \n", Color::YELLOW).Print();
        for (int i = showStart; i <= showEnd; i++)
        {
            list[i].Print();
        }
    }
    else
    {
        showStart = chooseNow - showMax / 2;
        showEnd = chooseNow + showMax / 2;
        Text("��                                 \n", Color::YELLOW).Print();
        for (int i = showStart; i <= showEnd; i++)
        {
            list[i].Print();
        }
        Text("��                                 \n", Color::YELLOW).Print();
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
