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
	�����Ƿ�ɹ�����,��ֹ��������ʱ����false
	����soundID������Ӧ����Ч
	��Ч����һ�μ���, ���Ա�������Ч���
	��Ч�Ĳ��Ų���Ӱ�챳�����ֵĲ���
	*/
	if (forbidMusic)
		return false;
	string path = MUSIC_PATH[soundID];
	// ��խ�ַ��ַ���ת��Ϊ���ַ��ַ���
	size_t pathLength = path.length() + 1;
	wchar_t* widePath = new wchar_t[pathLength];
	errno_t err = MultiByteToWideChar(CP_UTF8, 0, path.c_str(), -1, widePath, (int)pathLength);
	if (err == 0) {
		delete[] widePath;
		return false; // ת��ʧ��
	}
	// ������Ч
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
	�����Ƿ�ɹ�����,��ֹ��������ʱ����false
	����soundID������Ӧ�ı�������
	��������Ӧ����ѭ�����ŵ�, ֱ������stopMusic����, ����ʹ��playMusic������������
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
	�����Ƿ�ɹ�ֹͣ,�����ǰû�в��ű������ֻ��ֹ��������ʱ����false,,���򷵻�true
	ֹͣ��ǰ���ŵı�������,������musicNowΪMUSI_NONE
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
		//����BGM�������������
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
