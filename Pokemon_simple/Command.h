#include <iostream>
#include <string>
#include <vector>
#include "Log.h"
#include "tools.h"
#include "Map.h"
#include "SoundPlayer.h"
using namespace std;

//���ܵĲ���
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
    //��ʾһ���б�,�����û�ѡ��,�����û�ѡ������
    //���showMaxΪ-1,����ʾ����ѡ��
    //���showMax��Ϊ-1,�������ʾshowMax��ѡ��,����ѡ����Զ�����
    //ʹ�ò�ɫ�ı�,ѡ�е�ѡ��������ʾ
    //����û�����ESC��,�򷵻�0
    //�ƶ����ʹ�ÿ��Ծֲ�ˢ��
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
    char GetCommand(vector<char> possibleCommands); //�����û�����,ֱ�����¿�����Ч�İ���Ϊֹ
    bool DoubleConfirmation(Text message = Text("��ȷ��Ҫ��ô����?\n", RED)); //����ȷ��
    Command();
    ~Command();
    void Pause();   //��ͣ,�ȴ��û����������
    int chooseFromList(vector<Text> list, int showMax = -1);    //���б���ѡ��һ��ѡ��
    void PrintfList(vector<Text> list); //��ӡ�б�
    int ChooseCount(int max);   //ѡ��һ������
};

