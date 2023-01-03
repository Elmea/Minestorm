#pragma once 
#include <raylib.h>
#include <math.h>
#include "myMaths.h"

typedef struct Player
{
    int life;
    int score;
    Float2 position;
    float angle;
    float speedX;
    float speedY;

    bool isAlive;

    Polygon playerPolygon;
    double timeLastDeath;
    double timeLastTP;
}Player;

//Forward declaration
typedef struct Game Game;

void twoPlayerInit(Game* game);
void playerInit(Player* player);
void playerUpdateAndDraw(Game* game, int id, Player* player, KeyboardKey left, KeyboardKey right, KeyboardKey forward, KeyboardKey shoot, KeyboardKey tp1, KeyboardKey tp2, Color color);
void drawPlayerDirectionMark(Player* player);
void playersRespawn(Game* game, int playerCount, Player* playerToRespawAlone);