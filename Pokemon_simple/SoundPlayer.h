#pragma once
#ifndef _SOUNDPLAYER_H_
#define _SOUNDPLAYER_H_

#include "tools.h"

class SoundPlayer
{
public:
    const enum SoundID
    {
        MUSIC_NONE = 0,  //预留编号0表示无音乐
        MUSIC_ZhenXinZhen,      //真新镇bgm
        MUSIC_ChangPanShi,      //常盘市bgm
        MUSIC_ShenHuiShi,       //深灰市bgm
        MUSIC_HuaTianShi,       //花田市bgm
        MUSIC_CaiHongShi,       //彩虹市bgm
        MUSIC_HongLianDao,      //红莲岛bgm
        MUSIC_ZiYuanZhen,        //紫苑镇bgm
        MUSIC_HuangJinShi,       //黄金市bgm
        MUSIC_QianHongShi,       //浅红市bgm
        MUSIC_YeWai,            //野外bgm
        MUSIC_DuiZhan,          //对战bgm
        MUSIC_YeSheng,          //对战野生宝可梦bgm
        MUSIC_Win,              //胜利bgm
        MUSIC_Lose,             //失败bgm
        SOUND_HIT_1,            //击中音效
        SOUND_HIT_2,            //击中音效
        SOUND_HIT_3,            //击中音效
        SOUND_CHOOSE,           //选择音效
        SOUND_HEAL,             //回复音效
        SOUND_JINHUA,           //进化音效
    };
    const char* MUSIC_PATH[20] = {
        "",
        "music/ZhenXinZhen.wav",      //真新镇bgm
        "music/ChangPanShi.wav",      //常盘市bgm
        "music/ShenHuiShi.wav",       //深灰市bgm
        "music/HuaTianShi.wav",       //花田市bgm
        "music/CaiHongShi.wav",       //彩虹市bgm
        "music/HongLianDao.wav",      //红莲岛bgm
        "music/ZiYuanZhen.wav"        //紫苑镇bgm
        "music/HuangJinShi.wav"       //黄金市bgm
        "music/QianHongShi.wav"       //浅红市bgm
        "music/YeWai.wav",            //野外bgm
        "music/DuiZhan.wav",          //对战bgm
        "music/YeSheng.wav",          //对战野生宝可梦bgm
        "music/Win.wav",              //胜利bgm
        "music/Lose.wav",             //失败bgm
        "music/hit_1,mp3",            //击中音效
        "music/hit_2.wav",            //击中音效
        "music/hit_3.wav",            //击中音效
        "music/choose.wav",           //选择音效
        "music/heal.wav",             //回复音效
        "music/JinHua.wav",           //进化音效 
    };
    bool forbidMusic;    //是否禁止播放音乐
    SoundPlayer(): musicNow(MUSIC_NONE),forbidMusic(false){}
    ~SoundPlayer();
    bool Play_Sound(SoundID soundID);       //播放音效(防止重定义加下划线)
    bool PlayMusic(SoundID soundID);        //播放音乐
    bool StopMusic();                       //停止播放当前音乐
    void AdjustMusic(GameSence gameSence);    //根据游戏状态调整音乐
private:
    SoundID musicNow;   //当前播放的音乐
};

#endif // !_SOUNDPLAYER_H_
