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
	// 将窄字符字符串转换为宽字符字符串
	size_t pathLength = path.length() + 1;
	wchar_t* widePath = new wchar_t[pathLength];
	errno_t err = MultiByteToWideChar(CP_UTF8, 0, path.c_str(), -1, widePath, (int)pathLength);
	if (err == 0) {
		delete[] widePath;
		return false; // 转换失败
	}
	// 播放音效
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
	if (forbidMusic)
		return false;
	if (musicNow ==soundID)
        return true;
	if (musicNow == MUSIC_NONE)
	{
		PlaySound(NULL, NULL, SND_ASYNC | SND_FILENAME);
	}
	musicNow = soundID;
    string path = MUSIC_PATH[soundID];
	size_t pathLength = path.length() + 1;
	wchar_t* widePath = new wchar_t[pathLength];
	errno_t err = MultiByteToWideChar(CP_UTF8, 0, path.c_str(), -1, widePath, (int)pathLength);
	if (err == 0) {
		delete[] widePath;
		return false;
	}
	bool success = PlaySound(widePath, NULL, SND_FILENAME | SND_LOOP | SND_ASYNC) != NULL;
	delete[] widePath;
	return success;
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

void SoundPlayer::AdjustMusic(GameSence gameSence)
{
	if (forbidMusic)
		return;
	SoundID BGM;
	switch (gameSence)
	{
	case START_MENU:
		//以下BGM具体参数待补充
		BGM = MUSIC_NONE;
		break;
	case GAME:
		BGM = MUSIC_NONE;
		break;
	case SETTING:
		BGM = MUSIC_NONE;
		break;
	case POKEMON_LIB:
		BGM = MUSIC_NONE;
		break;
	case POKEMON_INFO:
		BGM = MUSIC_NONE;
		break;
	case BACKPACK:
		BGM = MUSIC_NONE;
		break;
	case POKEMON_CENTER:
		BGM = MUSIC_NONE;
		break;
	case SHOP:case SHOOSE_BUY_OR_SELL:case BUY_ITEM:case SELL_POKEMON:case SELL_ITEM:
		BGM = MUSIC_NONE;
		break;
	case COMBAT:
		BGM = MUSIC_NONE;
		break;
	case DEBUG:
		BGM = MUSIC_NONE;
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
			BGM = MUSIC_NONE;
			break;
		case BUY_ITEM:
			BGM = MUSIC_NONE;
			break;
		case SELL_POKEMON:
			BGM = MUSIC_NONE;
			break;
		case SELL_ITEM:
			BGM = MUSIC_NONE;
			break;
		default:
			break;
		}
		Play_Sound(BGM);
	}
	return;
}
