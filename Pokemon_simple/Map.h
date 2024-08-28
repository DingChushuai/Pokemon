#pragma once
#ifndef MAP_H
#define MAP_H
#include "Text.h"

class Map
{
public:
    enum BlockType
    {
        EMPTY,      //�������ߵĵ�·
        WALL,       //�ϰ���
        GRASS,      //�ݵ�,��������,�����б�����
        EXIT,       //ͨ��������ͼ�ĳ���
        SHOP,       //�̵�
        HOSPITAL,   //ҽԺ,���Իظ�����
        POKEMON_CENTER, //����������,���Խ���������
    };
    const struct MapBlock
    {
        Color color;
        char symbol;
        BlockType type;
    };

    Map(int mapID);
    ~Map();
    int getMapID();
    int getMapWidth();
    int getMapHeight();
    MapBlock getMapBlock(int x, int y);
    BlockType getBlockType(int x, int y);
    vector<int> getExit(int x, int y);
    vector<Text> getTexts();
    vector<pair<int, int>> getWildPokemon();

private:
    int mapID;
    string mapName;
    int mapWidth;
    int mapHeight;
    vector<vector<MapBlock>> mapBlocks;
    vector<vector<int>> exits; //��¼��ͼ������Ϣ,ÿһ�����:����X����/����Y����/���ڵ�ͼID/���ڵ�ͼX����/���ڵ�ͼY����
    vector<Text> texts; //��¼��ͼ�ϵ�������Ϣ
    vector<pair<int, int>> wildPokemon; //��¼��ͼ�ϵ�Ұ����������Ϣ,ÿһ�����:������ID/�����γ��ֵĵȼ�
};

#endif
