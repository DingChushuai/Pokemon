#include "SoundPlayer.h"

SoundPlayer::~SoundPlayer()
{
	StopMusic();
}

bool SoundPlayer::Play_Sound(SoundID soundID)
{
	/*
	返回是否成功播放,禁止播放音乐时返回false
	根据soundID播放相应的音效
	音效播放一次即可, 可以被其他音效打断
	音效的播放不会影响背景音乐的播放
	*/
	
	return true;
}

bool SoundPlayer::PlayMusic(SoundID soundID)
{
	/*
	返回是否成功播放,禁止播放音乐时返回false
	根据soundID播放相应的背景音乐
	背景音乐应当是循环播放的, 直到调用stopMusic函数, 或者使用playMusic播放其他音乐
	*/

	//临时设计
	if (forbidMusic)
		return false;

	string path = MUSIC_PATH[soundID];
	string temp_open = "open " + path;
	const char* open = temp_open.c_str();
	int nLen = MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, open, -1, NULL, 0);
	wchar_t* wopen = new wchar_t[nLen];
	MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, open, -1, wopen, nLen);
	string temp_play = "play " + path;
	const char* play = temp_play.c_str();
	nLen = MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, play, -1, NULL, 0);
	wchar_t* wplay = new wchar_t[nLen];
	MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, play, -1, wplay, nLen);
	//string stop = "stop " + path;

	mciSendString(wopen, NULL, 0, NULL);
	mciSendString(wplay, NULL, 0, NULL);

	Sleep(10000);

	//mciSendString((wchar_t*)(stop.c_str()), NULL, 0, NULL);
	return true;
}

bool SoundPlayer::StopMusic()
{
	/*
	返回是否成功停止,如果当前没有播放背景音乐或禁止播放音乐时返回false,,否则返回true
	停止当前播放的背景音乐,并更改musicNow为MUSI_NONE
	*/
	return true;
}

void SoundPlayer::AdjustMusic(GameSence gameSence)
{
}
