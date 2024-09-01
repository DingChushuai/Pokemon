#pragma once
#include "PokemonLib.h"
#include "Log.h"
class Combat
{
public:
    Combat() {};
    ~Combat() {};
    void InitWildCombat(int id, int level,PokemonLib* pokemonLib); 
    void InitTrainerCombat(int battleId, PokemonLib* pokemonLib);
    PokemonLib* pokemonLib;
    vector<Pokemon*> myPokemons;
    vector<Pokemon*> enemyPokemons; 
    Pokemon* pokemonNow;
    Pokemon* enemyNow;
    vector<Pokemon*> pokemonAvailable();
    vector<Pokemon*> enemyAvailable(); 
    vector<Text> PokemonAvailableText();
    Text ChangePokemon(Pokemon* pokemon);
    bool TryToEscape();
    vector<Text> ShowPokemonInfo(); //��ʾ���ҷ���������Ϣ
    vector<Text> ShowPokemonSkill();
    bool IsTrainerBattle();
    bool IsWildBattle();
    int GetExperienceFromBattle(Pokemon* beatenPokemon);
    void EndCombat();
    vector<vector<float>> damageTable;  //������˱�,���캯���г�ʼ��
    bool lastCombatWin; //��һ��ս���Ƿ�ʤ��
    Log combatLog;  //ս����־,ս����ɺ����
    bool isTrainer;
    int escapeFailedTimes; //����ʧ�ܴ��� 
    vector<pair<Pokemon*,Pokemon*>> beaten; //�ҷ�������սʤ�ĵз�������, ���ڼ���ս������


};

