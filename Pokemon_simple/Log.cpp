#include "Log.h"
#pragma once

Log::Log(int maxLog)
{
	this->maxLog = maxLog;
}

Log::~Log()
{
	clearLog();
}

void Log::AddLog(Text log)
{
	if (logList.size() >= maxLog) logList.erase(logList.begin());
	logList.push_back(log);
}

void Log::ShowLog()
{
	if (!logList.empty())
	{
		for (int i = 0; i < logList.size(); i++)
		{
			logList[i].Print();
			Text("\n").Print();
		}
	}
}

void Log::clearLog()
{
	logList.clear();
}
