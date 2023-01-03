#include <raylib.h>
#include <math.h>
#include "mines.h"
#include "myMaths.h"
#include <stdlib.h>
#include "define.h"
#include "game.h"

Polygon mineLayerInit()
{
    Float2* mineLayerVertices = calloc(1, 11*sizeof(Float2));
    mineLayerVertices[0] = (Float2){-127.0f, 32.0f};
    mineLayerVertices[1] = (Float2){-107.0f, -16.0f};
    mineLayerVertices[2] = (Float2){-34.0f, -16.0f};
    mineLayerVertices[3] = (Float2){0.0f, -43.0f};
    mineLayerVertices[4] = (Float2){33.0f, -16.0f};
    mineLayerVertices[5] = (Float2){106.0f, -16.0f};
    mineLayerVertices[6] = (Float2){126.0f, 32.0f};
    mineLayerVertices[7] = (Float2){108.0f, 11.0f};
    mineLayerVertices[8] = (Float2){69.0f, 11.0f};
    mineLayerVertices[9] = (Float2){-64.0f, 11.0f};
    mineLayerVertices[10] = (Float2){-107.0f, 11.0f};
    myTriangle* mineLayerTriangle = calloc(1, 7*sizeof(myTriangle));
    mineLayerTriangle[0] = (myTriangle){{(Float2)mineLayerVertices[0], (Float2)mineLayerVertices[1], (Float2)mineLayerVertices[10]}};
    mineLayerTriangle[1] = (myTriangle){{(Float2)mineLayerVertices[10], (Float2)mineLayerVertices[1], (Float2)mineLayerVertices[9]}};
    mineLayerTriangle[2] = (myTriangle){{(Float2)mineLayerVertices[1], (Float2)mineLayerVertices[2], (Float2)mineLayerVertices[9]}};
    mineLayerTriangle[3] = (myTriangle){{(Float2)mineLayerVertices[9], (Float2)mineLayerVertices[3], (Float2)mineLayerVertices[8]}};
    mineLayerTriangle[4] = (myTriangle){{(Float2)mineLayerVertices[8], (Float2)mineLayerVertices[5], (Float2)mineLayerVertices[4]}};
    mineLayerTriangle[5] = (myTriangle){{(Float2)mineLayerVertices[8], (Float2)mineLayerVertices[5], (Float2)mineLayerVertices[7]}};
    mineLayerTriangle[6] = (myTriangle){{(Float2)mineLayerVertices[5], (Float2)mineLayerVertices[6], (Float2)mineLayerVertices[7]}};
    Polygon mineLayerPolygon = {11, mineLayerVertices, {0,0}, 7, mineLayerTriangle, (AABB){(Float2){0, 0}, 257, 80}};
    return mineLayerPolygon;
}

void mineLayerTriangleRecalculus(Polygon* mineLayerPolygon)
{
    mineLayerPolygon->triangle[0] = (myTriangle){{(Float2)mineLayerPolygon->vertex[0], (Float2)mineLayerPolygon->vertex[1], (Float2)mineLayerPolygon->vertex[10]}};
    mineLayerPolygon->triangle[1] = (myTriangle){{(Float2)mineLayerPolygon->vertex[10], (Float2)mineLayerPolygon->vertex[1], (Float2)mineLayerPolygon->vertex[9]}};
    mineLayerPolygon->triangle[2] = (myTriangle){{(Float2)mineLayerPolygon->vertex[1], (Float2)mineLayerPolygon->vertex[2], (Float2)mineLayerPolygon->vertex[9]}};
    mineLayerPolygon->triangle[3] = (myTriangle){{(Float2)mineLayerPolygon->vertex[9], (Float2)mineLayerPolygon->vertex[3], (Float2)mineLayerPolygon->vertex[8]}};
    mineLayerPolygon->triangle[4] = (myTriangle){{(Float2)mineLayerPolygon->vertex[8], (Float2)mineLayerPolygon->vertex[5], (Float2)mineLayerPolygon->vertex[4]}};
    mineLayerPolygon->triangle[5] = (myTriangle){{(Float2)mineLayerPolygon->vertex[8], (Float2)mineLayerPolygon->vertex[5], (Float2)mineLayerPolygon->vertex[7]}};
    mineLayerPolygon->triangle[6] = (myTriangle){{(Float2)mineLayerPolygon->vertex[5], (Float2)mineLayerPolygon->vertex[6], (Float2)mineLayerPolygon->vertex[7]}};  
}

Polygon floatingMineInit()
{
    Float2* floatingMineVertices = calloc(1, 6*sizeof(Float2));
    floatingMineVertices[0] = (Float2){0.0f, -72.0f}; 
    floatingMineVertices[1] = (Float2){18.0f, -14.0f}; 
    floatingMineVertices[2] = (Float2){58.0f, 33.0f}; 
    floatingMineVertices[3] = (Float2){0.0f, 23.0f}; 
    floatingMineVertices[4] = (Float2){-55.0f, 36.0f}; 
    floatingMineVertices[5] = (Float2){-18.0f, -13.0f};
    myTriangle* floatingMineTriangle = calloc(1, 4*sizeof(myTriangle));
    floatingMineTriangle[0] = (myTriangle){{(Float2)floatingMineVertices[0], (Float2)floatingMineVertices[1], (Float2)floatingMineVertices[5]}};
    floatingMineTriangle[1] = (myTriangle){{(Float2)floatingMineVertices[1], (Float2)floatingMineVertices[2], (Float2)floatingMineVertices[3]}};
    floatingMineTriangle[2] = (myTriangle){{(Float2)floatingMineVertices[3], (Float2)floatingMineVertices[4], (Float2)floatingMineVertices[5]}};
    floatingMineTriangle[3] = (myTriangle){{(Float2)floatingMineVertices[1], (Float2)floatingMineVertices[3], (Float2)floatingMineVertices[5]}};
    Polygon floatingMinePolygon = {6, floatingMineVertices, {0,0}, 4, floatingMineTriangle, (AABB){(Float2){0, 0}, 80, 80}};
    return floatingMinePolygon;
}

void floatingTriangleRecalculus(Polygon* floatingMine)
{
    floatingMine->triangle[0] = (myTriangle){{(Float2)floatingMine->vertex[0], (Float2)floatingMine->vertex[1], (Float2)floatingMine->vertex[5]}};
    floatingMine->triangle[1] = (myTriangle){{(Float2)floatingMine->vertex[1], (Float2)floatingMine->vertex[2], (Float2)floatingMine->vertex[3]}};
    floatingMine->triangle[2] = (myTriangle){{(Float2)floatingMine->vertex[3], (Float2)floatingMine->vertex[4], (Float2)floatingMine->vertex[5]}};
    floatingMine->triangle[3] = (myTriangle){{(Float2)floatingMine->vertex[1], (Float2)floatingMine->vertex[3], (Float2)floatingMine->vertex[5]}};
}

Polygon magneticMineInit()
{
    Float2* magneticMineVertices = calloc(1, 8*sizeof(Float2));
    magneticMineVertices[0] = (Float2){-46.0f, -47.0f}; 
    magneticMineVertices[1] = (Float2){0.0f, -26.0f}; 
    magneticMineVertices[2] = (Float2){46.0f, -47.0f}; 
    magneticMineVertices[3] = (Float2){26.0f, 0.0f}; 
    magneticMineVertices[4] = (Float2){46.0f, 48.0f}; 
    magneticMineVertices[5] = (Float2){0.0f, 27.0f}; 
    magneticMineVertices[6] = (Float2){-46.0f, 48.0f}; 
    magneticMineVertices[7] = (Float2){-25.0f, 0.0f};
    myTriangle* magneticMineTriangle = calloc(1, 6*sizeof(myTriangle));
    magneticMineTriangle[0] = (myTriangle){{(Float2)magneticMineVertices[0], (Float2)magneticMineVertices[1], (Float2)magneticMineVertices[7]}};
    magneticMineTriangle[1] = (myTriangle){{(Float2)magneticMineVertices[1], (Float2)magneticMineVertices[2], (Float2)magneticMineVertices[3]}};
    magneticMineTriangle[2] = (myTriangle){{(Float2)magneticMineVertices[3], (Float2)magneticMineVertices[4], (Float2)magneticMineVertices[5]}};
    magneticMineTriangle[3] = (myTriangle){{(Float2)magneticMineVertices[5], (Float2)magneticMineVertices[6], (Float2)magneticMineVertices[7]}};
    magneticMineTriangle[4] = (myTriangle){{(Float2)magneticMineVertices[1], (Float2)magneticMineVertices[5], (Float2)magneticMineVertices[7]}};
    magneticMineTriangle[5] = (myTriangle){{(Float2)magneticMineVertices[1], (Float2)magneticMineVertices[3], (Float2)magneticMineVertices[5]}};
    Polygon magneticMinePolygon = {8, magneticMineVertices, {0,0}, 6, magneticMineTriangle, (AABB){(Float2){0, 0}, 80, 80}};
    return magneticMinePolygon;
}

void magneticTriangleRecalculus(Polygon* magneticMine)
{
    magneticMine->triangle[0] = (myTriangle){{(Float2)magneticMine->vertex[0], (Float2)magneticMine->vertex[1], (Float2)magneticMine->vertex[7]}};
    magneticMine->triangle[1] = (myTriangle){{(Float2)magneticMine->vertex[1], (Float2)magneticMine->vertex[2], (Float2)magneticMine->vertex[3]}};
    magneticMine->triangle[2] = (myTriangle){{(Float2)magneticMine->vertex[3], (Float2)magneticMine->vertex[4], (Float2)magneticMine->vertex[5]}};
    magneticMine->triangle[3] = (myTriangle){{(Float2)magneticMine->vertex[5], (Float2)magneticMine->vertex[6], (Float2)magneticMine->vertex[7]}};
    magneticMine->triangle[4] = (myTriangle){{(Float2)magneticMine->vertex[1], (Float2)magneticMine->vertex[5], (Float2)magneticMine->vertex[7]}};
    magneticMine->triangle[5] = (myTriangle){{(Float2)magneticMine->vertex[1], (Float2)magneticMine->vertex[3], (Float2)magneticMine->vertex[5]}};
}

Polygon magneticFireballInit()
{
    Float2* magneticFireballVertices = calloc(1, 12*sizeof(Float2));
    magneticFireballVertices[0] = (Float2){-44.0f, -75.0f}; 
    magneticFireballVertices[1] = (Float2){-32.0f, -45.0f}; 
    magneticFireballVertices[2] = (Float2){43.0f, -45.0f}; 
    magneticFireballVertices[3] = (Float2){73.0f, -45.0f}; 
    magneticFireballVertices[4] = (Float2){43.0f, -31.0f}; 
    magneticFireballVertices[5] = (Float2){43.0f, 46.0f}; 
    magneticFireballVertices[6] = (Float2){43.0f, 78.0f}; 
    magneticFireballVertices[7] = (Float2){29.0f, 46.0f}; 
    magneticFireballVertices[8] = (Float2){-44.0f, 46.0f}; 
    magneticFireballVertices[9] = (Float2){-73.0f, 46.0f}; 
    magneticFireballVertices[10] = (Float2){-44.0f, 34.0f}; 
    magneticFireballVertices[11] = (Float2){-44.0f, -45.0f};
    myTriangle* magneticFireballTriangle = calloc(1, 7*sizeof(myTriangle));
    magneticFireballTriangle[0] = (myTriangle){{(Float2)magneticFireballVertices[0], (Float2)magneticFireballVertices[1], (Float2)magneticFireballVertices[11]}};
    magneticFireballTriangle[1] = (myTriangle){{(Float2)magneticFireballVertices[1], (Float2)magneticFireballVertices[2], (Float2)magneticFireballVertices[5]}};
    magneticFireballTriangle[2] = (myTriangle){{(Float2)magneticFireballVertices[2], (Float2)magneticFireballVertices[3], (Float2)magneticFireballVertices[4]}};
    magneticFireballTriangle[3] = (myTriangle){{(Float2)magneticFireballVertices[5], (Float2)magneticFireballVertices[6], (Float2)magneticFireballVertices[7]}};
    magneticFireballTriangle[4] = (myTriangle){{(Float2)magneticFireballVertices[7], (Float2)magneticFireballVertices[8], (Float2)magneticFireballVertices[11]}};
    magneticFireballTriangle[5] = (myTriangle){{(Float2)magneticFireballVertices[8], (Float2)magneticFireballVertices[9], (Float2)magneticFireballVertices[10]}};
    magneticFireballTriangle[6] = (myTriangle){{(Float2)magneticFireballVertices[1], (Float2)magneticFireballVertices[5], (Float2)magneticFireballVertices[11]}};
    Polygon magneticFireballPolygon = {12, magneticFireballVertices, {0,0}, 7, magneticFireballTriangle, (AABB){(Float2){0, 0}, 100, 100}};
    return magneticFireballPolygon;
}

void magneticFireballTriangleRecalculus(Polygon* magneticFireball)
{
    magneticFireball->triangle[0] = (myTriangle){{(Float2)magneticFireball->vertex[0], (Float2)magneticFireball->vertex[1], (Float2)magneticFireball->vertex[11]}};
    magneticFireball->triangle[1] = (myTriangle){{(Float2)magneticFireball->vertex[1], (Float2)magneticFireball->vertex[2], (Float2)magneticFireball->vertex[5]}};
    magneticFireball->triangle[2] = (myTriangle){{(Float2)magneticFireball->vertex[2], (Float2)magneticFireball->vertex[3], (Float2)magneticFireball->vertex[4]}};
    magneticFireball->triangle[3] = (myTriangle){{(Float2)magneticFireball->vertex[5], (Float2)magneticFireball->vertex[6], (Float2)magneticFireball->vertex[7]}};
    magneticFireball->triangle[4] = (myTriangle){{(Float2)magneticFireball->vertex[7], (Float2)magneticFireball->vertex[8], (Float2)magneticFireball->vertex[11]}};
    magneticFireball->triangle[5] = (myTriangle){{(Float2)magneticFireball->vertex[8], (Float2)magneticFireball->vertex[9], (Float2)magneticFireball->vertex[10]}};
    magneticFireball->triangle[6] = (myTriangle){{(Float2)magneticFireball->vertex[1], (Float2)magneticFireball->vertex[5], (Float2)magneticFireball->vertex[11]}};
}

Polygon fireballMineInit()
{
    Float2* fireballMineVertices = calloc(1, 8*sizeof(Float2));
    fireballMineVertices[0] = (Float2){-50.0f, -50.0f};
    fireballMineVertices[1] = (Float2){0.0f, -40.0f};
    fireballMineVertices[2] = (Float2){50.0f, -50.0f};
    fireballMineVertices[3] = (Float2){40.0f, 0.0f};
    fireballMineVertices[4] = (Float2){50.0f, 50.0f};
    fireballMineVertices[5] = (Float2){0.0f, 40.0f};
    fireballMineVertices[6] = (Float2){-50.0f, 50.0f};
    fireballMineVertices[7] = (Float2){-40.0f, 0.0f};
    myTriangle* fireballMineTriangle = calloc(1, 6*sizeof(myTriangle));
    fireballMineTriangle[0] = (myTriangle){{(Float2)fireballMineVertices[0], (Float2)fireballMineVertices[1], (Float2)fireballMineVertices[7]}};
    fireballMineTriangle[1] = (myTriangle){{(Float2)fireballMineVertices[1], (Float2)fireballMineVertices[2], (Float2)fireballMineVertices[3]}};
    fireballMineTriangle[2] = (myTriangle){{(Float2)fireballMineVertices[3], (Float2)fireballMineVertices[4], (Float2)fireballMineVertices[5]}};
    fireballMineTriangle[3] = (myTriangle){{(Float2)fireballMineVertices[5], (Float2)fireballMineVertices[6], (Float2)fireballMineVertices[7]}};
    fireballMineTriangle[4] = (myTriangle){{(Float2)fireballMineVertices[7], (Float2)fireballMineVertices[1], (Float2)fireballMineVertices[5]}};
    fireballMineTriangle[5] = (myTriangle){{(Float2)fireballMineVertices[1], (Float2)fireballMineVertices[3], (Float2)fireballMineVertices[5]}};
    Polygon fireballMine = {8, fireballMineVertices, {0,0}, 6, fireballMineTriangle, (AABB){(Float2){0, 0}, 105, 105}};
    return fireballMine;
}

void fireballTriangleRecalculus(Polygon* fireball)
{
    fireball->triangle[0] = (myTriangle){{(Float2)fireball->vertex[0], (Float2)fireball->vertex[1], (Float2)fireball->vertex[7]}};
    fireball->triangle[1] = (myTriangle){{(Float2)fireball->vertex[1], (Float2)fireball->vertex[2], (Float2)fireball->vertex[3]}};
    fireball->triangle[2] = (myTriangle){{(Float2)fireball->vertex[3], (Float2)fireball->vertex[4], (Float2)fireball->vertex[5]}};
    fireball->triangle[3] = (myTriangle){{(Float2)fireball->vertex[5], (Float2)fireball->vertex[6], (Float2)fireball->vertex[7]}};
    fireball->triangle[4] = (myTriangle){{(Float2)fireball->vertex[7], (Float2)fireball->vertex[1], (Float2)fireball->vertex[5]}};
    fireball->triangle[5] = (myTriangle){{(Float2)fireball->vertex[1], (Float2)fireball->vertex[3], (Float2)fireball->vertex[5]}};
}

void triangleRecalculusByType(Mine* mine)
{
    if (mine->dead == true)
    {
        switch (mine->type)
        {
        case MT_FLOATING:
            floatingTriangleRecalculus(&mine->polygon);
            break;

        case MT_MAGNETIC:
            magneticTriangleRecalculus(&mine->polygon);
            break;

        case MT_FIREBALL:
            fireballTriangleRecalculus(&mine->polygon);
            break;

        case MT_MAGNETIC_FIREBALL:
            magneticFireballTriangleRecalculus(&mine->polygon);
            break;
        
        default:
            break;
        }
    }
}

//---------------------------------CREATION ET AFFICHAGE DES SPAWN DE MINE---------------------------------//

void applyScoreMine(Mine* mine)
{
    if(mine->type == MT_FLOATING)
    {
        if(mine->size == MS_BIG)
        {
            mine->scoreYield = 100;
        }
        else if (mine->size == MS_MEDIUM)
        {
            mine->scoreYield = 135;
        }
        else if (mine->size == MS_SMALL)
        {
            mine->scoreYield = 200;
        }
        
    }
    else if(mine->type == MT_FIREBALL)
    {
        if(mine->size == MS_BIG)
        {
            mine->scoreYield = 325;
        }
        else if (mine->size == MS_MEDIUM)
        {
            mine->scoreYield = 360;
        }
        else if (mine->size == MS_SMALL)
        {
            mine->scoreYield = 425;
        }
        
    }
    else if(mine->type == MT_MAGNETIC)
    {
        if(mine->size == MS_BIG)
        {
            mine->scoreYield = 500;
        }
        else if (mine->size == MS_MEDIUM)
        {
            mine->scoreYield = 535;
        }
        else if (mine->size == MS_SMALL)
        {
            mine->scoreYield = 600;
        }
        
    }
    else if(mine->type == MT_MAGNETIC)
    {
        if(mine->size == MS_BIG)
        {
            mine->scoreYield = 750;
        }
        else if (mine->size == MS_MEDIUM)
        {
            mine->scoreYield = 585;
        }
        else if (mine->size == MS_SMALL)
        {
            mine->scoreYield = 850;
        }
        
    }
}

void createMinesSpawnPoint(Game* game, int nbSpawnMines)//cree aletoirement les point de spawn des mines sur les bord de la map.
{

    for(int i = 0; i < nbSpawnMines; i++)//genere les coordonnee du spawn des mines
    {
        int count = 0;
        while (count != 2)
        {
            count = 0;
            int posx = rand() %590;
            game->mines[i + game->spawnMinesCount].angle = rand() %360;
            game->spawnmines[i + game->spawnMinesCount].angle = game->mines[i].angle;
            game->spawnmines[i + game->spawnMinesCount].show = true;
            if(posx > 60)
            {
                game->spawnmines[i + game->spawnMinesCount].position.x = posx;
                game->mines[i + game->spawnMinesCount].position.x = posx;
                count +=1;
            }

            int posy = rand() %730;
            if(posy > 70)
            {
                game->spawnmines[i + game->spawnMinesCount].position.y = posy;
                game->mines[i + game->spawnMinesCount].position.y = posy;
                count +=1;
            }
        }
    }
    game->spawnMinesCount += nbSpawnMines;
}

void drawSpawnMineTexture(SpawnMines* spawnmine, Texture2D texture, Color color)
{
    float frameWidth = texture.width/4;
    float frameHeight = texture.height/2;

    Rectangle frameRec = { 1.0f, 1.0f, (float)frameWidth, (float)frameHeight };

    int currentFrame = 1;
    int currentLine = 0;

    frameRec.x = currentFrame * frameWidth;
    frameRec.y = currentLine * frameHeight;

    Rectangle destRec = { spawnmine->position.x, spawnmine->position.y, frameWidth*0.12f, frameHeight*0.12f };
    Float2 center = { destRec.width/2, destRec.height/2};
    
    DrawTexturePro(texture, frameRec, destRec, myVector2ToVector2Convert(center), spawnmine->angle, color);
    
}

void drawMinesSpawn(Game* game, Texture2D mineTexture, int nbspawnMine)//fait spawn les spawnmines sur la map 
{
    for(int i = 0; i<nbspawnMine; i++)
    {
        if (game->spawnmines[i].show == true)
        {
            drawSpawnMineTexture(&game->spawnmines[i], mineTexture, WHITE);     
        }  
    }
}
//---------------------------------------------------------------------------------------------------------//


//---------------------------------SPAWN DES MINES---------------------------------//

void drawMineTexture(Mine* mines, int size, Color color)// size big = 3 moyen = 2 little = 1
{
    mines->polygon.center.x = mines->position.x;
    mines->polygon.center.y = mines->position.y;

    mines->size = size;

    drawPolygon(&mines->polygon, size, color);
}

void spawnMine(Game* game, int minetype, int size, int nbMines)// size big = 3 moyen = 2 little = 1; minetype MT_FLOATING = 1, MT_MAGNETIC = 2, MT_MAGNETIC_FIREBALL = 3 ,MT_FIREBALL = 4,
{
    for (int j = 0; j < nbMines; j++)
    {
        game->mines[j + game->enemiesAlive].size = size;
        if (game->mines[j + game->enemiesAlive].size == MS_SMALL)
        {
            game->mines[j + game->enemiesAlive].speed = MD_FAST;
        }
        else if (game->mines[j + game->enemiesAlive].size == MS_MEDIUM)
        {
            game->mines[j + game->enemiesAlive].speed = MD_MEDIUM;
        }
        else if (game->mines[j + game->enemiesAlive].size == MS_BIG)
        {
            game->mines[j + game->enemiesAlive].speed = MD_SLOW;
        }

        if (minetype == MT_FLOATING)
        {
            game->mines[j + game->enemiesAlive].polygon = floatingMineInit();
        }
        else if (minetype == MT_MAGNETIC)
        {
            game->mines[j + game->enemiesAlive].polygon = magneticMineInit();
        }
        else if (minetype == MT_MAGNETIC_FIREBALL)
        {
            game->mines[j + game->enemiesAlive].polygon = magneticFireballInit();
        }
        else if (minetype == MT_FIREBALL)
        {
            game->mines[j + game->enemiesAlive].polygon = fireballMineInit();
        }

        game->mines[j + game->enemiesAlive].type = minetype;
        for (int i = 0; i < game->spawnMinesCount; i++) 
        {
            if (game->spawnmines[i].show == true) 
            {
                game->mines[j + game->enemiesAlive].position = game->spawnmines[i].position;
                game->spawnmines[i].show = false;
                break;
            }
        }
            
        applyScoreMine(&game->mines[j + game->enemiesAlive]);

        game->enemiesAlive++;
    }
    
}

void moveBasicMine(Game* game, int numMine)
{
    game->mines[numMine].position.x += cosf(game->mines[numMine].angle)/(game->mines[numMine].speed);
    game->mines[numMine].position.y += sinf(game->mines[numMine].angle)/(game->mines[numMine].speed);
    entityColisionBorder(&game->mines[numMine].position);
}

int distplayer(Mine* mine, Player* player1, Player* player2)
{
    float distX1 = mine->position.x - player1->position.x;
    float distY1 = mine->position.y - player1->position.y;

    float distX2 = mine->position.x - player2->position.x;
    float distY2 = mine->position.y - player2->position.y;

    float dist1 = distX1 + distY1;
    float dist2 = distX2 + distY2;

    if(dist1 < dist2)
        return 0;
    else 
        return 1;
}

void moveMagneticMine(Game* game, int numMine)
{
    int player = distplayer(&game->mines[numMine], &game->player[0], &game->player[1]);

    float adjacent = game->player[player].position.x - game->mines[numMine].position.x;
    float opose = game->player[player].position.y - game->mines[numMine].position.y;
    float hyp = sqrtf(adjacent*adjacent + opose*opose);
    
    game->mines[numMine].angle = asinf(opose/hyp);

    int speed = game->mines[numMine].speed;

    if (cos(game->mines[numMine].angle) > 0)
    {
        game->mines[numMine].position.y += sinf(game->mines[numMine].angle)/speed;
    }
    
    else
    {
        game->mines[numMine].position.y -= sinf(game->mines[numMine].angle)/speed;  
    }

    game->mines[numMine].angle = acosf(adjacent/hyp);

    if (sin(game->mines[numMine].angle) > 0)
    {
        game->mines[numMine].position.x += cosf(game->mines[numMine].angle)/speed;
    }
    else
    {
        game->mines[numMine].position.x -= cosf(game->mines[numMine].angle)/speed; 
    }

    entityColisionBorder(&game->mines[numMine].position);
    
}

void mineUpdateAndDraw(Game* game)
{
    for(int i = 0; i<game->enemiesAlive; i++)
    {
        if (game->mines[i].type == MT_MAGNETIC || game->mines[i].type == MT_MAGNETIC_FIREBALL)
        {
            moveMagneticMine(game, i);
        }
        else
        {
            moveBasicMine(game, i);
        }

        triangleRecalculusByType(&game->mines[i]);

        drawMineTexture(&game->mines[i], game->mines[i].size, RED);

        game->mines[i].polygon.colisionBoxAABB.pos.x = game->mines[i].position.x - 40;
        game->mines[i].polygon.colisionBoxAABB.pos.y = game->mines[i].position.y - 50;
    }
}

//--------------------------------------------------------------------------------//

//----------------------------------BULLET MINES----------------------------------//

float getPlayerAngle(Game* game, Mine* mine)
{
    Float2 vector = (Float2){game->player[distplayer(mine, &game->player[0], &game->player[1])].position.x - mine->position.x, game->player[distplayer(mine, &game->player[0], &game->player[1])].position.y - mine->position.y};
    float dot = dotProduct(&vector, &(Float2){1, 0});

    float angle = acosf(dot/(sqrtf(vector.x*vector.x + vector.y*vector.y)));

    if (game->player[distplayer(mine, &game->player[0], &game->player[1])].position.y < mine->position.y) return - radToDregrees(angle);

    return radToDregrees(angle);
}

void MineShoot(Game* game, Mine* mine)
{
    if (game->bulletCount < BULLET_CAPACITY)
    {
        game->bullets[game->bulletCount].position = mine->position;
        game->bullets[game->bulletCount].angle = getPlayerAngle(game, mine);
        game->bullets[game->bulletCount].flag = true;
        game->bullets[game->bulletCount].box = (AABB){(Float2){0, 0}, 13, 13};
        game->bullets[game->bulletCount].polygon = bulletPolygonInit();
        game->bullets[game->bulletCount].type = BT_MINES;
        game->bullets[game->bulletCount].time = GetTime();
        game->bulletCount++;
    }
}


//---------------------------------------------------------------------//

void createRandomMine(Game* game, int nbMine)
{
    for(int i = 0; i< nbMine; i++)
    {
        int mineType = rand() %4;
        spawnMine(game, mineType, MS_BIG, 1);
    }
}

//------------------------------MINELAYER------------------------------//

bool colisionSpawnMines(int distX, int distY)
{
    int count = 0;

    if (distX < 10 && distX > -10)
        count += 1;

    if (distY < 10 && distY > -10)
        count += 1;

    if (count == 2)
        return true;
    else
        return false;
}

void DrawMinelayer(Minelayer* minelayer)
{

    minelayer->polygon = mineLayerInit();
    minelayer->scoreYield = 1000;

    minelayer->polygon.center.x = minelayer->position.x;
    minelayer->polygon.center.y = minelayer->position.y;

    drawPolygon(&minelayer->polygon, MS_SMALL, RED);
}

void moveMinelayer(Game* game, Float2 position)
{
    float adjacent = position.x - game->minelayer[game->minelayerCount].position.x;
    float opose = position.y - game->minelayer[game->minelayerCount].position.y;
    float hyp = sqrtf(adjacent*adjacent + opose*opose);
    
    game->minelayer[game->minelayerCount].angle = asinf(opose/hyp);

    int speed = 1;

    if (cos(game->minelayer[game->minelayerCount].angle) > 0)
        game->minelayer[game->minelayerCount].position.y += sinf(game->minelayer[game->minelayerCount].angle)/speed;
    
    else
        game->minelayer[game->minelayerCount].position.y -= sinf(game->minelayer[game->minelayerCount].angle)/speed;

    game->minelayer[game->minelayerCount].angle = acosf(adjacent/hyp);

    if (sin(game->minelayer[game->minelayerCount].angle) > 0)
        game->minelayer[game->minelayerCount].position.x += cosf(game->minelayer[game->minelayerCount].angle)/speed;
    else
        game->minelayer[game->minelayerCount].position.x -= cosf(game->minelayer[game->minelayerCount].angle)/speed; 
    entityColisionBorder(&game->minelayer->position);
    DrawMinelayer(&game->minelayer[game->minelayerCount]);
}

void minelayer(Game* game, Texture2D texture)
{
    if (game->minelayer[game->minelayerCount].dead != true)
    {
        int distX = game->minelayer[game->minelayerCount].position.x - game->spawnmines[game->spawnMinesCount-1].position.x;
        int distY = game->minelayer[game->minelayerCount].position.y - game->spawnmines[game->spawnMinesCount-1].position.y;

        bool test = colisionSpawnMines(distX, distY);
        if (test)
        {
            createRandomMine(game, 1);
            game->spawnmines[game->spawnMinesCount-1].show = true;
            createMinesSpawnPoint(game, 1);
        }
        game->spawnmines[game->spawnMinesCount-1].show = false;

        drawMinesSpawn(game, texture, game->spawnMinesCount);
        moveMinelayer(game, game->spawnmines[game->spawnMinesCount-1].position);
    }
    
}


//---------------------------------------------------------------------//
void deathMine(Game* game, Mine* mine)// quand une mine meurt deux autre spawn
{
    if(mine->size == MS_BIG) spawnMine(game, mine->type, MS_MEDIUM, 2);

    else if (mine->size == MS_MEDIUM) spawnMine(game, mine->type, MS_SMALL, 2);
}

void chekDeathMines(Game* game)
{
    for(int i=0; i < game->enemiesAlive; i++)
    {
        if(game->mines[i].dead == true)
        {
            if(game->mines[i].type == MT_FIREBALL || game->mines[i].type == MT_MAGNETIC_FIREBALL)
            {
                MineShoot(game, &game->mines[i]);
            }
            deathMine(game, &game->mines[i]);
            freePolygon(&game->mines[i].polygon);
            for(int j=i; j < game->enemiesAlive; j++)
            {
                game->mines[j] = game->mines[j+1];
            }
            game->enemiesAlive--;
        }
    }
}

