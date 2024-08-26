#pragma once
#ifndef _SOUNDPLAYER_H_
#define _SOUNDPLAYER_H_

class Game;

class SoundPlayer
{
//TODO以下内容需要根据给出的资源文件进行补充
//游戏音效和音乐 枚举类
    const enum SoundID
    {
        MUSI_NONE = 0,  //预留编号0表示无音乐
        MUSIC_MAIN = 1,
    };
    //音乐路径
    const char* MUSIC_PATH[2] = {
        "",
        "./resource/music/main.mp3",
    };
private:
    Game* _game;
    SoundID musicNow;   //当前播放的音乐
public:
    bool forbidMusic;    //是否禁止播放音乐
    SoundPlayer(Game* game): _game(game),musicNow(MUSI_NONE),forbidMusic(false){}
    ~SoundPlayer();

    bool Play_Sound(SoundID soundID);    //播放音效(防止重定义加下划线)
    bool PlayMusic(SoundID soundID);    //播放音乐
    bool StopMusic();    //停止播放当前音乐
    void AdjustMusic();    //根据游戏状态调整音乐
};

#endif // !_SOUNDPLAYER_H_
