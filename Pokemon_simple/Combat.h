#pragma once
#include "PokemonLib.h"
#include "Log.h"
class Combat
{
public:
    Combat();
    ~Combat() {};
    void InitWildCombat(int id, int level,PokemonLib* pokemonLib);  //��ʼ��Ұ��������ս��
    void InitTrainerCombat(int battleId, PokemonLib* pokemonLib);   //��ʼ��ѵ����ս��
    PokemonLib* pokemonLib; //����Game�еı����ο�
    vector<Pokemon*> myPokemons;    //�ҷ�������,�ɱ����βֿ⸴����ʱ������
    vector<Pokemon*> enemyPokemons;     //�з�������
    Pokemon* pokemonNow; //��ǰս���ı�����
    Pokemon* enemyNow;  //��ǰս���ĵз�������
    vector<Pokemon*> pokemonAvailable();    //���ص�ǰ���õı�����
    vector<Pokemon*> enemyAvailable();  //���ص�ǰ���õĵз�������
    vector<Text> PokemonAvailableText();    //���ص�ǰ���õı����ε��ı�
    Text ChangePokemon(Pokemon* pokemon);   //����������
    bool TryToEscape();     //��������
    vector<Text> ShowPokemonInfo(); //��ʾ���ҷ���������Ϣ
    vector<Text> ShowPokemonSkill();    //��ʾ��ǰ�����μ���
    bool IsTrainerBattle();
    bool IsWildBattle();
    int GetExperienceFromBattle(Pokemon* beatenPokemon);    //����ս������
    void EndCombat();   //ս������,���ս������,�ش�ս�����
    vector<vector<float>> damageTable;  //������˱�,���캯���г�ʼ��
    bool lastCombatWin; //��һ��ս���Ƿ�ʤ��
    Log combatLog;  //ս����־,ս����ɺ����
    bool isTrainer; //�Ƿ���ѵ����ս��
    int escapeFailedTimes; //����ʧ�ܴ��� 
    vector<pair<Pokemon*,Pokemon*>> beaten; //�ҷ�������սʤ�ĵз�������, ���ڼ���ս������


};

