#pragma once

#include "SoundPlayer.h"
#include "Log.h"
#include "NPC.h"
#include "Map.h"
#include "Combat.h"
#include "Command.h"
#include "PokemonLib.h"
#include "Backpack.h"
#include "Shop.h"

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
    vector<GameSence> gameSenceStack;
    vector<NPC*> npcs;
    vector<Map*> maps;
    Map* currentMap;
    Combat combat;
    PokemonLib pokemonLib;
    Pokemon* pokemonNow;
    Backpack backpack;
    Shop shop;

private:
    void Init();
    void Load();
    void Save();
    void DrawTitle();
    void DrawWorldMap();
    void ActOnMap();
    void UseProp(Prop* prop);
    void UseSkill(Skill* skill, Pokemon* user, Pokemon* target); 
    void ChangeMusic();
    bool ChangeNPCState(NPC* npc);  //尝试改变NPC状态，如果成功返回true
    void StartCombat();
};

