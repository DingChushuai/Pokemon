#pragma once
#include "PokemonLib.h"
#include "Text.h"
class Combat
{
public:
    Combat() {};
    ~Combat() {};
    void InitWildCombat(int id, int level,PokemonLib& pokemonLib); 
    void InitTrainerCombat(int battleId, PokemonLib& pokemonLib);
    vector<Pokemon*> myPokemons;
    vector<Pokemon*> enemyPokemons; 
    Pokemon* pokemonNow;
    Pokemon* enemyNow;
    vector<Pokemon*> pokemonAvailable();
    vector<Pokemon*> enemyAvailable(); 
    vector<Text> PokemonAvailableText();
    Text ChangePokemon(Pokemon* pokemon);
    bool TryToEscape();
    vector<Text> ShowPokemonInfo();
    bool IsTrainerBattle();
    bool IsWildBattle();
    void EndCombat();
    vector<vector<float>> damageTable;  //������˱�,���캯���г�ʼ��
    bool lastCombatWin; //��һ��ս���Ƿ�ʤ��
private:
    bool isTrainer;
    vector<pair<Pokemon*,Pokemon*>> beaten; //�ҷ�������սʤ�ĵз�������, ���ڼ���ս������


};

