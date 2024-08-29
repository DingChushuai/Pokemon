#include "SoundPlayer.h"
#include <windows.h>
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
	const char* temp_path = path.c_str();
	int nLen = MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, temp_path, -1, NULL, 0);
	wchar_t* wpath = new wchar_t[nLen];
	MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, temp_path, -1, wpath, nLen);
	PlaySound(wpath, NULL, SND_FILENAME | SND_ASYNC);
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

	musicNow = soundID;
	string path = MUSIC_PATH[soundID];
	string temp_open = "open " + path;
	const char* open = temp_open.c_str();
	int nLen = MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, open, -1, NULL, 0);
	wchar_t* wopen = new wchar_t[nLen];
	MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, open, -1, wopen, nLen);
	string temp_play = "play " + path+ " repeat";
	const char* play = temp_play.c_str();
	nLen = MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, play, -1, NULL, 0);
	wchar_t* wplay = new wchar_t[nLen];
	MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, play, -1, wplay, nLen);
	string temp_stop = "stop " + path;
	const char* stop = temp_stop.c_str();
	nLen = MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, play, -1, NULL, 0);
	wchar_t* wstop = new wchar_t[nLen];
	MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, stop, -1, wstop, nLen);
	string temp_close = "close " + path;
	const char* close = temp_close.c_str();
	nLen = MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, close, -1, NULL, 0);
	wchar_t* wclose = new wchar_t[nLen];
	MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, close, -1, wclose, nLen);

	if (musicNow != MUSI_NONE) {
		mciSendString(wopen, NULL, 0, NULL);
		mciSendString(wplay, NULL, 0, NULL);
	}
	else {
		mciSendString(wstop, NULL, 0, NULL);
		mciSendString(wclose, NULL, 0, NULL);
	}

	return true;
}

bool SoundPlayer::StopMusic()
{
	/*
	返回是否成功停止,如果当前没有播放背景音乐或禁止播放音乐时返回false,,否则返回true
	停止当前播放的背景音乐,并更改musicNow为MUSI_NONE
	*/
	if (forbidMusic or musicNow == MUSI_NONE)
		return false;
	else {
		musicNow = MUSI_NONE;
		PlayMusic(musicNow);
		return true;
	}
}

void SoundPlayer::AdjustMusic(GameSence gameSence)
{
	if (forbidMusic)
		return;
	SoundID BGM;
	switch (gameSence)
	{
	case START_MENU:
		//以下BGM具体参数待补充
		BGM = MUSI_NONE;
		break;
	case GAME:
		BGM = MUSI_NONE;
		break;
	case SETTING:
		BGM = MUSI_NONE;
		break;
	case POKEMON_LIB:
		BGM = MUSI_NONE;
		break;
	case POKEMON_INFO:
		BGM = MUSI_NONE;
		break;
	case BACKPACK:
		BGM = MUSI_NONE;
		break;
	case POKEMON_CENTER:
		BGM = MUSI_NONE;
		break;
	case SHOP:case SHOOSE_BUY_OR_SELL:case BUY_ITEM:case SELL_POKEMON:case SELL_ITEM:
		BGM = MUSI_NONE;
		break;
	case COMBAT:
		BGM = MUSI_NONE;
		break;
	case DEBUG:
		BGM = MUSI_NONE;
		break;
	default:
		break;
	}
	StopMusic();
	PlayMusic(BGM);
	if (gameSence == SHOOSE_BUY_OR_SELL or gameSence== BUY_ITEM 
		or gameSence== SELL_POKEMON or gameSence== SELL_ITEM) {
		switch (gameSence)
		{
		case SHOOSE_BUY_OR_SELL:
			BGM = MUSI_NONE;
			break;
		case BUY_ITEM:
			BGM = MUSI_NONE;
			break;
		case SELL_POKEMON:
			BGM = MUSI_NONE;
			break;
		case SELL_ITEM:
			BGM = MUSI_NONE;
			break;
		default:
			break;
		}
		Play_Sound(BGM);
	}
	return;
}
