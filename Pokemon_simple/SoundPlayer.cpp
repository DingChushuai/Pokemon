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
	return true;
}

bool SoundPlayer::PlayMusic(SoundID soundID)
{
	/*
	�����Ƿ�ɹ�����,��ֹ��������ʱ����false
	����soundID������Ӧ�ı�������
	��������Ӧ����ѭ�����ŵ�, ֱ������stopMusic����, ����ʹ��playMusic������������
	*/
    return true;
}

bool SoundPlayer::StopMusic()
{
	/*
	�����Ƿ�ɹ�ֹͣ,�����ǰû�в��ű������ֻ��ֹ��������ʱ����false,,���򷵻�true
	ֹͣ��ǰ���ŵı�������,������musicNowΪMUSI_NONE
	*/
	return true;
}

void SoundPlayer::AdjustMusic()
{
	//���������ĳ���, �����������ֵĲ���
}
