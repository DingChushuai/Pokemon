#pragma once
#ifndef LOG_H
#define LOG_H

#include "Text.h"
#include <vector>

class Log
{
    //���ڼ�¼��ҵ���Ϊ����,���л���ͼ,������������
    //��¼�������Ϊ,����ʾ����Ļ��
    //ʹ�ò�ɫ������ʾ��ͬ����
public:
    Log(int maxLog = 10);
    ~Log();
    void AddLog(Text log);
    void ShowLog();
    void clearLog();
private:
    int maxLog;     //��¼���������,������ɾ����ɵ�,Ĭ��Ϊ10
    vector<Text> logList;
};

#endif // LOG_H
