#pragma once

#include <time.h> 
#include <raylib.h>

#include "myMaths.h"

typedef enum minesType
{
    MT_FLOATING,// Normal
    MT_MAGNETIC, // Follow player
    MT_FIREBALL, // Shoot a fireball in player diection when shooted
    MT_MAGNETIC_FIREBALL, // Fireball + Magnetic
}minesType;

typedef enum minesSize
{
    MS_UNDEFINE,
    MS_SMALL,
    MS_MEDIUM,
    MS_BIG,

}minesSize;

typedef enum minesSpeed
{
    MD_FAST = 2,
    MD_MEDIUM = 3,
    MD_SLOW = 5,
}minesSpeed;

typedef struct Mine
{   
    minesType type;
    minesSize size;
    minesSpeed speed;
    int scoreYield;
    Float2 position;
    float angle;
    Polygon polygon;
    bool dead;
}Mine;

typedef struct SpawnMines
{
    Float2 position;
    float angle;
    bool show;
}SpawnMines;


typedef struct ENEMY_BULLET // fire ball shoted by MT_FIREBALL or MT_MAGNETIC_FIREBALL
{
    Float2 position;
    float angle;
    int scoreYield;
    Polygon polygon;
    bool init;
    bool dead;
}Enemy_bullet;


typedef struct Minelayer//mother tree appearing on one side of the screen to add new spawn points when all the others are gone
{
    minesSize size;
    int scoreYield;
    bool dead;
    Polygon polygon;
    Float2 position;
    float angle;
}Minelayer;

// Forward declaration
typedef struct Game Game;

void drawMineTexture(Mine* mines, int size, Color color);
void createMinesSpawnPoint(Game* game, int nbMines);
void spawnMine(Game* game, int minetype, int size, int nbMines);
void mineUpdateAndDraw(Game* game);

void initCurrentEnemy(Game* game);
void incrementCurrentEnemy(Game* game, int nbEnemy);
void initEnemyBullet(Game* game, Mine* mine);
void spawnEnemy_bullet(Game* game/*, Mine* mines*/, Texture2D texture);

void minelayer(Game* game, Texture2D texture);
void createRandomMine(Game* game, int nbMine);

void chekDeathMines(Game* game);

void drawMinesSpawn(Game* game, Texture2D mineTexture, int nbspawnMine);