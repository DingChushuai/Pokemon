#include "Command.h"
#include <conio.h>

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
    //示例代码
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

int Command::chooseMenu()
{
    //这是一个示例函数，用于选择菜单, 其他函数类似于此函数
    vector<Text> Menu;
    Menu.push_back(Text("1. 开始新游戏"));
    Menu.push_back(Text("2. 加载游戏"));
    Menu.push_back(Text("3. 退出游戏"));
    ChooseList MenuList(Menu);
    vector<char> possibleCommands = { UP, LEFT, DOWN, RIGHT, YES, ESC };
    char command;
    do {
        MenuList.ShowList();
        command = GetCommand(possibleCommands);
        cout << command << endl;
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
            if (MenuList.chooseNow == 2)
            {
                if (DoubleConfirmation(Text("你确定要退出游戏吗?\n")))
                    return 2;
                else
                    break;
            }
            return MenuList.chooseNow + 1;
        case ESC:
            if (DoubleConfirmation(Text("你确定要退出游戏吗?\n")))
                return 2;
            else
                break;
        }
    } while (true);
}

ChooseList::ChooseList(vector<Text> list)
{
    if (list.size() == 0)
        throw "choose list is empty";
    this->list = list;
    chooseNow = 0;
    chooseMax = list.size() - 1;
    list[chooseNow].SetColor(None, GREEN);
}

ChooseList::~ChooseList()
{

}

void ChooseList::SetSelect(int select)
{
    if (select < 0 || select > chooseMax)
        throw "choose list index out of range";
    if (select == chooseNow)
        return;
    list[chooseNow].SetColor(None, None);
    chooseNow = select;
    list[chooseNow].SetColor(None, GREEN);
}

void ChooseList::ShowList(int max)
{
    //覆盖显示最后一次显示的内容
    //移动光标到前vector.size()行

    int n = list.size();
    //移动光标到前vector.size()行
    if (max == -1 || max >= list.size())
        for (int i = 0; i < list.size(); i++)
        {
            list[i].Print();
        }
    else
    {
        int showStart, showEnd;
        if (chooseNow < max / 2)
        {
            showStart = 0;
            showEnd = max;
        }
        else
        {
            showStart = chooseNow - max / 2;
            showEnd = chooseNow + max / 2;
        }
        for (int i = showStart; i < showEnd; i++)
        {
            list[i].Print();
        }
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
    if (chooseNow == chooseMax)
        return;
    SetSelect(chooseNow + 1);
}
