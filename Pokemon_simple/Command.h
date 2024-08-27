#include <iostream>
#include <string>
#include <vector>
#include "Log.h"
#include "tools.h"
using namespace std;

const char UP = 'w';
const char DOWN = 's';
const char LEFT = 'a';
const char RIGHT = 'd';
const char YES = ' ';
const char ESC = 27;
const char OPEN_BACKPACK = 'e';
const char POKEMON_LIST = 'f';
const char COMMAND = '/';
const char WORLD_MAP = 'm';

class ChooseList
{
public:
    ChooseList(vector<Text> list);
    ~ChooseList();
    int chooseNow = 0;
    int chooseMax = 0;
    int coverLines = 0; //覆盖行数, 用于显示时覆盖之前的选项
    void SetSelect(int select);
    void ShowList(int max = -1);
    void SelectUp();
    void SelectDown();
private:
    vector<Text> list;
    int startLine = 0;
};

class Command
{
private:
    char GetCommand(vector<char> possibleCommands); //接收用户输入,直到按下可能生效的按键为止
    bool DoubleConfirmation(Text message = Text("你确定要这么做吗?\n", RED)); //二次确认
public:
    Command();
    ~Command();
    int chooseMenu();
};

