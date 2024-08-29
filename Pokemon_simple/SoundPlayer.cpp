#include "SoundPlayer.h"

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

	mciSendString(wopen, NULL, 0, NULL);
	mciSendString(wplay, NULL, 0, NULL);
	return true;
}

bool SoundPlayer::PlayMusic(SoundID soundID)
{
	/*
	�����Ƿ�ɹ�����,��ֹ��������ʱ����false
	����soundID������Ӧ�ı�������
	��������Ӧ����ѭ�����ŵ�, ֱ������stopMusic����, ����ʹ��playMusic������������
	*/

	//��ʱ���
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

	mciSendString(wopen, NULL, 0, NULL);
	mciSendString(wplay, NULL, 0, NULL);

	return true;
}

bool SoundPlayer::StopMusic()
{
	/*
	�����Ƿ�ɹ�ֹͣ,�����ǰû�в��ű������ֻ��ֹ��������ʱ����false,,���򷵻�true
	ֹͣ��ǰ���ŵı�������,������musicNowΪMUSI_NONE
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
}
