#include <iostream>
#include <string>
#include <vector>
#include "Log.h"
#include "tools.h"
#include "Map.h"
#include "SoundPlayer.h"
using namespace std;

//可能的操作
const char UP = 'w';
const char DOWN = 's';
const char LEFT = 'a';
const char RIGHT = 'd';
const char YES = ' ';
const char ESC = 27;
const char OPEN_BACKPACK = 'e';
const char POKEMON_LIST = 'f';
const char COMMAND = '/';
const char OPEN_WORLD_MAP = 'm';

class ChooseList
{
    //显示一个列表,并让用户选择,返回用户选择的序号
    //如果showMax为-1,则显示所有选项
    //如果showMax不为-1,则最多显示showMax个选项,并且选项会自动滚动
    //使用彩色文本,选中的选项会高亮显示
    //如果用户按下ESC键,则返回0
    //移动光标使得可以局部刷新
public:
    ChooseList(vector<Text> list);
    ChooseList(vector<Text> list, int showMax);
    int chooseNow = 0;
    int showMax = -1;
    void SetSelect(int select);
    void ShowList();
    void SelectUp();
    void SelectDown();
    int maxstrlen = 0;
private:
    vector<Text> list;
    int startLine = -1;
    bool firstShow = true;
};

class Command
{
public:
    char GetCommand(vector<char> possibleCommands); //接收用户输入,直到按下可能生效的按键为止
    bool DoubleConfirmation(Text message = Text("你确定要这么做吗?\n", RED)); //二次确认
    Command();
    ~Command();
    void Pause();   //暂停,等待用户按下任意键
    int chooseFromList(vector<Text> list, int showMax = -1);    //从列表中选择一个选项
    void PrintfList(vector<Text> list); //打印列表
    int ChooseCount(int max);   //选择一个数字
};

