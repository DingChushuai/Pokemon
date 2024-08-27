#pragma once

#include "SoundPlayer.h"
#include "Log.h"
#include "SceneDrawer.h"
#include "NPC.h"
#include "Map.h"
#include "Combat.h"
#include "Command.h"

class Game
{
public:
    Game(); 
    ~Game() {};
    void Run();
    int playerX, playerY;
    int money;
    bool inCombat;
    GameSence gameSence;
    SoundPlayer soundPlayer;
    Log log;
    Command command;
    SceneDrawer sceneDrawer;
    vector<GameSence> gameSenceStack;
    vector<NPC> npcs;
    vector<Map> maps;
    Map* currentMap;
    Combat combat;

private:
    void Init();
    void Load();
    void Save();
    int ActOnMap();
};

