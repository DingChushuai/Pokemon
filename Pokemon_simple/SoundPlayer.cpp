#include "SoundPlayer.h"
#include <Windows.h>

#include <mmsystem.h>

#pragma comment(lib, "winmm.lib")

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
	if (forbidMusic)
		return false;
	string path = MUSIC_PATH[soundID];
	size_t pathLength = path.length() + 1;
	wchar_t* widePath = new wchar_t[pathLength];
	errno_t err = MultiByteToWideChar(CP_UTF8, 0, path.c_str(), -1, widePath, (int)pathLength);
	if (err == 0) {
		delete[] widePath;
		return false;
	}
	BOOL success = PlaySound(widePath, NULL, SND_FILENAME | SND_ASYNC);
	if (!success) {
		delete[] widePath;
		return false;
	}
	delete[] widePath;
	return true;
}

bool SoundPlayer::PlayMusic(SoundID soundID)
{
	/*
	返回是否成功播放,禁止播放音乐时返回false
	根据soundID播放相应的背景音乐
	背景音乐应当是循环播放的, 直到调用stopMusic函数, 或者使用playMusic播放其他音乐
	*/
	if (forbidMusic || soundID == MUSIC_NONE)
	{
		mciSendString(L"stop bgm", NULL, 0, 0);
		mciSendString(L"close bgm", NULL, 0, 0);
		musicNow = MUSIC_NONE;
		return false;
	}
	if (musicNow ==soundID)
        return true;
	mciSendString(L"stop bgm", NULL, 0, 0);
	mciSendString(L"close bgm", NULL, 0, 0);
	if (soundID == MUSIC_NONE)
	{
		return false;
	}
	string path = MUSIC_PATH[soundID];
	wstring widePath(path.begin(), path.end());
	wstring command;
	command += L"open ";
	command += widePath;
	command += L" type wave alias bgm";
	command = L"open " + widePath + L" type mpegvideo alias bgm"; 
	MCIERROR mcErr = mciSendString(command.c_str(), NULL, 0, 0);
	if (mcErr != 0) {
		return false;
	}
	mciSendString(L"play bgm repeat", NULL, 0, 0);
	musicNow = soundID;
	return true;
}

bool SoundPlayer::StopMusic()
{
	/*
	返回是否成功停止,如果当前没有播放背景音乐或禁止播放音乐时返回false,,否则返回true
	停止当前播放的背景音乐,并更改musicNow为MUSI_NONE
	*/
	if (forbidMusic or musicNow == MUSIC_NONE)
		return false;
	else {
		musicNow = MUSIC_NONE;
		PlayMusic(musicNow);
		return true;
	}
}