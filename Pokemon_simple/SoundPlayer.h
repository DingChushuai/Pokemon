#pragma once
#ifndef _SOUNDPLAYER_H_
#define _SOUNDPLAYER_H_

#include "tools.h"

class SoundPlayer
{
public:
    const enum SoundID
    {
        MUSIC_NONE = 0,  //Ԥ�����0��ʾ������
        MUSIC_ZhenXinZhen,      //������bgm
        MUSIC_ChangPanShi,      //������bgm
        MUSIC_ShenHuiShi,       //�����bgm
        MUSIC_HuaTianShi,       //������bgm
        MUSIC_CaiHongShi,       //�ʺ���bgm
        MUSIC_HongLianDao,      //������bgm
        MUSIC_ZiYuanZhen,        //��Է��bgm
        MUSIC_HuangJinShi,       //�ƽ���bgm
        MUSIC_QianHongShi,       //ǳ����bgm
        MUSIC_YeWai,            //Ұ��bgm
        MUSIC_DuiZhan,          //��սbgm
        MUSIC_YeSheng,          //��սҰ��������bgm
        MUSIC_Win,              //ʤ��bgm
        MUSIC_Lose,             //ʧ��bgm
        SOUND_HIT_1,            //������Ч
        SOUND_HIT_2,            //������Ч
        SOUND_HIT_3,            //������Ч
        SOUND_CHOOSE,           //ѡ����Ч
        SOUND_HEAL,             //�ظ���Ч
        SOUND_JINHUA,           //������Ч
    };
    const char* MUSIC_PATH[20] = {
        "",
        "music/ZhenXinZhen.wav",      //������bgm
        "music/ChangPanShi.wav",      //������bgm
        "music/ShenHuiShi.wav",       //�����bgm
        "music/HuaTianShi.wav",       //������bgm
        "music/CaiHongShi.wav",       //�ʺ���bgm
        "music/HongLianDao.wav",      //������bgm
        "music/ZiYuanZhen.wav"        //��Է��bgm
        "music/HuangJinShi.wav"       //�ƽ���bgm
        "music/QianHongShi.wav"       //ǳ����bgm
        "music/YeWai.wav",            //Ұ��bgm
        "music/DuiZhan.wav",          //��սbgm
        "music/YeSheng.wav",          //��սҰ��������bgm
        "music/Win.wav",              //ʤ��bgm
        "music/Lose.wav",             //ʧ��bgm
        "music/hit_1,mp3",            //������Ч
        "music/hit_2.wav",            //������Ч
        "music/hit_3.wav",            //������Ч
        "music/choose.wav",           //ѡ����Ч
        "music/heal.wav",             //�ظ���Ч
        "music/JinHua.wav",           //������Ч 
    };
    bool forbidMusic;    //�Ƿ��ֹ��������
    SoundPlayer(): musicNow(MUSIC_NONE),forbidMusic(false){}
    ~SoundPlayer();
    bool Play_Sound(SoundID soundID);       //������Ч(��ֹ�ض�����»���)
    bool PlayMusic(SoundID soundID);        //��������
    bool StopMusic();                       //ֹͣ���ŵ�ǰ����
    void AdjustMusic(GameSence gameSence);    //������Ϸ״̬��������
private:
    SoundID musicNow;   //��ǰ���ŵ�����
};

#endif // !_SOUNDPLAYER_H_
