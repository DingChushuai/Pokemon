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
	�����Ƿ�ɹ�����,��ֹ��������ʱ����false
	����soundID������Ӧ�ı�������
	��������Ӧ����ѭ�����ŵ�, ֱ������stopMusic����, ����ʹ��playMusic������������
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