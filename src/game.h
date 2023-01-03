#pragma once 
#include "myMaths.h"
#include "player.h"
#include "mines.h"
#include "define.h"

typedef enum bulletType
{
    BT_PLAYER,
    BT_MINES
}bulletType;

typedef struct Bullet
{
    Float2 position;
    float angle;
    bool flag;
    AABB box;
    Polygon polygon;
    bulletType type;
    double time;
    int playerID;
} Bullet;

typedef struct Game
{
    Player player[2];

    Mine mines[512];

    SpawnMines spawnmines[128];
    int spawnMinesCount;

    Minelayer minelayer[64];
    int minelayerCount;


    int bulletCount;
    Bullet bullets[BULLET_CAPACITY];

    int enemiesAlive;

    double time;
    int level;
}Game;

void gameInit(Game* game);
void gameUpdateAndDraw(Game* game);
void entityColisionBorder(Float2* position);
Vector2 myVector2ToVector2Convert(Float2 myvector);
void drawPolygon(Polygon* polygon, minesSize size, Color color);
void drawHitBox(Polygon* polygon, minesSize size, Color color);
void freePolygon(Polygon* Polygon);
void killPlayer(Player* player);
void checkBulletPlayerColision(Game* game, Player* player);
void checkPlayerColision(Game* game, int playerCount);
void drawBullet(Bullet* bullet, Texture2D texture);
void bulletsUptadteAndDraw(Game* game, Texture2D texture);
void cleanBullet(Game* game);
void drawAABBBox(AABB box, Color color);

Polygon bulletPolygonInit();

void checkBulletsBulletsColision(Game* game);
void checkMineBulletsColision(Game* game);

void killPlayer(Player* player);

void cleanGame(Game* game);
void cleanMinesSpawn(Game* game);