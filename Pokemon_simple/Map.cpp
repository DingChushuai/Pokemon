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
	
	vector<string> exitInfos = Split(line, ',');
	for (const auto& exitInfo : exitInfos)
	{
		vector<string> coordinates = Split(exitInfo, '/');
		if (coordinates.size() == 5)
		{
			vector<int> exit = {stoi(coordinates[0]),  stoi(coordinates[1]), stoi(coordinates[2]), stoi(coordinates[3]),  stoi(coordinates[4])};
			exits.push_back(exit);
		}
	}
	

	getline(file, line);

	
	vector<string> pokemonInfos = Split(line, ',');
	for (const auto& pokemonInfo : pokemonInfos)
	{
		vector<string> info = Split(pokemonInfo, '/');
		if (info.size() == 3)
		{
			vector<int> wildPokemonInfo = {stoi(info[0]),stoi(info[1]), stoi(info[2])    
			};
			wildPokemon.push_back(wildPokemonInfo);
		}
	}


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
	for (const auto& exit : exits)
	{ 
		if (exit[0] == x && exit[1] == y)
		{
			return { exit[2], exit[3], exit[4] };
		}
	}
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

