#pragma once
#ifndef MAP_H
#define MAP_H
#include "Text.h"

class Map
{
public:
    enum BlockType
    {
        EMPTY,      //可以行走的道路
        WALL,       //障碍物
        GRASS,      //草地,可以行走,可能有宝可梦
        EXIT,       //通往其他地图的出口
        SHOP,       //商店
        HOSPITAL,   //医院,可以回复体力
        POKEMON_CENTER, //宝可梦中心,可以交换宝可梦
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
    vector<int> getExit(int x, int y);  //返回出口信息(出口地图ID/出口地图X坐标/出口地图Y坐标),如果没有出口则返回空向量
    vector<Text> getTexts();            //返回地图上的文字信息
    vector<vector<int>> getWildPokemon();   //返回地图上的野生宝可梦信息(宝可梦ID/宝可梦出现的等级/宝可梦出现的概率)
    string getMapName();

private:
    int mapID;
    string mapName;
    int mapWidth;
    int mapHeight;
    vector<vector<MapBlock>> mapBlocks;
    vector<vector<int>> exits; //记录地图出口信息,每一项包括:出口X坐标/出口Y坐标/出口地图ID/出口地图X坐标/出口地图Y坐标
    vector<Text> texts; //记录地图上的文字信息
    vector<vector<int>> wildPokemon; //记录地图上的野生宝可梦信息,每一项包括:宝可梦ID/宝可梦出现的等级/宝可梦出现的概率
};

#endif
