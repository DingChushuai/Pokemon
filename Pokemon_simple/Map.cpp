#include "Map.h"

Map::Map(int mapID)
{
	//��maps�ļ�����Ѱ��mapID��Ӧ�ĵ�ͼ�ļ�,������
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
	//������exits��Ѱ��(x,y)�ĳ�����Ϣ
}

vector<Text> Map::getTexts()
{
	return texts;
}

vector<pair<int, int>> Map::getWildPokemon()
{
	return wildPokemon;
}

