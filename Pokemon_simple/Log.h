#pragma once
#ifndef LOG_H
#define LOG_H

#include "Text.h"
#include <vector>

class Log
{
    //用于记录玩家的行为内容,如切换地图,宝可梦升级等
    //记录最后几条行为,并显示在屏幕上
    //使用彩色字体显示不同内容
public:
    Log(int maxLog = 10);
    ~Log();
    void AddLog(Text log);
    void ShowLog();
    void clearLog();
private:
    int maxLog;     //记录的最大条数,超过则删除最旧的,默认为10
    vector<Text> logList;
};

#endif // LOG_H
