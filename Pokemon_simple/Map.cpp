#include "Map.h"
#pragma once
#include <fstream>
#include <iostream>
using namespace std;

Map::Map(int mapID)
{
	//在maps文件夹中寻找mapID对应的地图文件,并加载
    this->mapID = mapID;
	ifstream file("map_" + to_string(mapID) + ".txt");
	if (!file.is_open())
    {
        cout << "Error: map file not found" << endl;
        return;
    }
    string line;
	getline(file, line);
	mapName = line;
    getline(file, line);
	vector<string> pos = Split(line, ',');
    mapWidth = stoi(pos[0]);
    mapHeight = stoi(pos[1]);
    mapBlocks.resize(mapWidth, vector<MapBlock>(mapHeight));
	getline(file, line);
	vector<string> infos = Split(line, ',');
	for (int i = 0; i < infos.size(); i++)
	{
		vector<string> info = Split(infos[i], '/');
		Text text;
		text.Add(info[0], (Color)atoi(info[1].c_str()));
		text.Add(info[2] + "\t");
		texts.push_back(text);
	}
	getline(file, line);
	//出口信息
	getline(file, line);
	//野生宝可梦信息
	for (int i = 0; i < mapHeight; i++) 
	{
		getline(file, line); 
		for (int j = 0; j < mapWidth; j++) 
		{
			mapBlocks[j][i].symbol = line[j]; 
		}
	}
	for (int i = 0; i < mapHeight; i++) 
	{ 
		getline(file, line); 
		for (int j = 0; j < mapWidth; j++) 
		{
			mapBlocks[j][i].color= (Color)atoi(line.substr(j, 1).c_str());
		}
	}
	for (int i = 0; i < mapHeight; i++)
	{
        getline(file, line);
		for (int j = 0; j < mapWidth; j++)
		{
			mapBlocks[j][i].type = (BlockType)atoi(line.substr(j, 1).c_str());
		}
	}
}

Map::~Map()
{
}

int Map::getMapID()
{
	return mapID;
}

int Map::getMapWidth()
{
	return mapWidth;
}

int Map::getMapHeight()
{
	return mapHeight;
}

Map::MapBlock Map::getMapBlock(int x, int y)
{
	return mapBlocks[x][y];
}

Map::BlockType Map::getBlockType(int x, int y)
{
	return mapBlocks[x][y].type;
}

vector<int> Map::getExit(int x, int y)
{
	//在所有exits中寻找(x,y)的出口信息
    return exits[0];
}

vector<Text> Map::getTexts()
{
	return texts;
}

vector<pair<int, int>> Map::getWildPokemon()
{
	return wildPokemon;
}

