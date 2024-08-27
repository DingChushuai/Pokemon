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
    ChooseList(vector<Text> list, int showMax);
    int chooseNow = 0;
    int chooseMax = 0;
    int showMax = -1;
    void SetSelect(int select);
    void ShowList();
    void SelectUp();
    void SelectDown();
private:
    vector<Text> list;
    int startLine = -1;
};

class Command
{
private:
    char GetCommand(vector<char> possibleCommands); //�����û�����,ֱ�����¿�����Ч�İ���Ϊֹ
    bool DoubleConfirmation(Text message = Text("��ȷ��Ҫ��ô����?\n", RED)); //����ȷ��
public:
    Command();
    ~Command();
    int chooseFromList(vector<Text> list, int showMax = -1);
};

