#pragma once
#ifndef SCENEDRAWER_H
#define SCENEDRAWER_H

#include "tools.h"
#include "Map.h"
#include "Log.h"
#include "PokemonLib.h"
#include "Combat.h"

class SceneDrawer
{
public:
    SceneDrawer(){};
    void draw(GameSence gs, int* money = 0, Map* map = nullptr, Log* log = nullptr, Combat* combat = nullptr);    //根据游戏状态绘制场景, 只绘制固定不变的部分, 会随着选择而变化的部分由Command类绘制
private:
    void drawMenu();    //只绘制gamebar
    void drawGame(int money, Map* map, Log* log);    //展示人物和地图基本信息和Log, 由于操作会改变地图信息, 所以由Command类绘制
    void drawSetting(); //只显示"设置", 因为设置的具体内容会随着选择而变化, 选中的选择项会高亮, 所以由Command类绘制
    void drawPokemonLib(); //只显示"宝可梦库", 因为宝可梦库的具体内容会随着选择而变化
    void drawPokemonInfo(Pokemon* pokemon); //显示"宝可梦信息"
    void drawBackpack(); //只显示"背包", 因为背包的具体内容会随着选择而变化
    void drawPokemonCenter(); //显示"宝可梦中心", 和携带的宝可梦信息
    void drawShop(int money); //只显示"商店"和钱的信息, 因为商店的具体内容会随着选择而变化
    void drawShooseBuyOrSell(); //只显示"选择购买或出售"
    void drawBuyItem(); //只显示"购买物品"
    void drawSellPokemon(); //只显示"出售宝可梦"
    void drawSellItem(); //只显示"出售物品"
    void drawCombat(Combat* combat); //显示"战斗", 和战斗信息
    void drawDebug(); //显示"调试"和调试的帮助函数
};

#endif // !SCENEDRAWER_H
