#pragma once
#ifndef _SOUNDPLAYER_H_
#define _SOUNDPLAYER_H_

class Game;

class SoundPlayer
{
//TODO����������Ҫ���ݸ�������Դ�ļ����в���
//��Ϸ��Ч������ ö����
    const enum SoundID
    {
        MUSI_NONE = 0,  //Ԥ�����0��ʾ������
        MUSIC_MAIN = 1,
    };
    //����·��
    const char* MUSIC_PATH[2] = {
        "",
        "./resource/music/main.mp3",
    };
private:
    Game* _game;
    SoundID musicNow;   //��ǰ���ŵ�����
public:
    bool forbidMusic;    //�Ƿ��ֹ��������
    SoundPlayer(Game* game): _game(game),musicNow(MUSI_NONE),forbidMusic(false){}
    ~SoundPlayer();

    bool Play_Sound(SoundID soundID);    //������Ч(��ֹ�ض�����»���)
    bool PlayMusic(SoundID soundID);    //��������
    bool StopMusic();    //ֹͣ���ŵ�ǰ����
    void AdjustMusic();    //������Ϸ״̬��������
};

#endif // !_SOUNDPLAYER_H_
