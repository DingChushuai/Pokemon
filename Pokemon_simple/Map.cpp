#include "Map.h"
#pragma once
#include <fstream>
#include <iostream>
using namespace std;

Map::Map(int mapID)
{
	//��maps�ļ�����Ѱ��mapID��Ӧ�ĵ�ͼ�ļ�,������
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

	//TODO: ��������Ϣ����exits

	getline(file, line);

	//TODO: ��Ұ����������Ϣ����wildPokemon

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
	//do nothing
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
	//TODO:
	//������exits��Ѱ��(x,y)�ĳ�����Ϣ,�����س�����Ϣ
	//tips:exits[i]ǰ����Ϊx,y, ������Ϊ��ͼID,��������
    return vector<int>();
}

vector<Text> Map::getTexts()
{
	return texts;
}

vector<vector<int>> Map::getWildPokemon()
{
	return wildPokemon;
}

