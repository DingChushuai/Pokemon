#include "Map.h"

Map::Map(int mapID)
{
	//在maps文件夹中寻找mapID对应的地图文件,并加载
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
}

vector<Text> Map::getTexts()
{
	return texts;
}

vector<pair<int, int>> Map::getWildPokemon()
{
	return wildPokemon;
}

