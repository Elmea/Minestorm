#include "game.h"
#include "myMaths.h"
#include "mines.h"
#include "player.h"
#include <stdlib.h>
#include <raylib.h>

Polygon bulletPolygonInit()
{
    Float2* bulletVertices = calloc(1, 8*sizeof(Float2));
    bulletVertices[0] = (Float2){0.0f, 15.0f}; 
    bulletVertices[1] = (Float2){7.5f, 7.5f}; 
    bulletVertices[2] = (Float2){15.0f, 0.0f}; 
    bulletVertices[3] = (Float2){7.5f, -7.5f}; 
    bulletVertices[4] = (Float2){0.0f, -15.0f};
    bulletVertices[5] = (Float2){-7.5f, -7.5f};
    bulletVertices[6] = (Float2){-15.0f, 0.0f}; 
    bulletVertices[7] = (Float2){7.5f, 7.5f};
    myTriangle* bulletTriangle = calloc(1, 8*sizeof(myTriangle));
    bulletTriangle[0] = (myTriangle){{(Float2){0, 0}, (Float2)bulletVertices[0], (Float2)bulletVertices[1]}};
    bulletTriangle[1] = (myTriangle){{(Float2){0, 0}, (Float2)bulletVertices[1], (Float2)bulletVertices[2]}};
    bulletTriangle[2] = (myTriangle){{(Float2){0, 0}, (Float2)bulletVertices[2], (Float2)bulletVertices[3]}};
    bulletTriangle[3] = (myTriangle){{(Float2){0, 0}, (Float2)bulletVertices[3], (Float2)bulletVertices[4]}};
    bulletTriangle[4] = (myTriangle){{(Float2){0, 0}, (Float2)bulletVertices[4], (Float2)bulletVertices[5]}};
    bulletTriangle[5] = (myTriangle){{(Float2){0, 0}, (Float2)bulletVertices[5], (Float2)bulletVertices[6]}};
    bulletTriangle[6] = (myTriangle){{(Float2){0, 0}, (Float2)bulletVertices[6], (Float2)bulletVertices[7]}};
    bulletTriangle[7] = (myTriangle){{(Float2){0, 0}, (Float2)bulletVertices[7], (Float2)bulletVertices[0]}};

    Polygon bulletPolygon = {8, bulletVertices, {0, 0}, 8, bulletTriangle, (AABB){(Float2){0, 0}, 50.0f, 50.0f}};
    return bulletPolygon;
}

void entityColisionBorder(Float2* position)
{
    if (position->x < 50)
        position->x = 590;
    if (position->x > 590)
        position->x = 50;
    if (position->y > 730)
        position->y = 50;
    if (position->y < 40)
        position->y = 730;
}

Vector2 myVector2ToVector2Convert(Float2 myvector)
{
    Vector2 result;
    result.x = myvector.x;
    result.y = myvector.y;
    return result;
}

void drawPolygon(Polygon* polygon, minesSize size, Color color)
{
    for (int i = 0; i < polygon->vertexCount; i++)
    {
        DrawLine(polygon->center.x + polygon->vertex[i].x*size/4, polygon->center.y + polygon->vertex[i].y*size/4, polygon->center.x + polygon->vertex[(i+1)%polygon->vertexCount].x*size/4, polygon->center.y + polygon->vertex[(i+1)%polygon->vertexCount].y*size/4, color);
    }
}

void drawAABBBox(AABB box, Color color)
{
    DrawLine(box.pos.x, box.pos.y, box.pos.x + box.width, box.pos.y, color);
    DrawLine(box.pos.x, box.pos.y, box.pos.x, box.pos.y + box.height, color);

    DrawLine(box.pos.x, box.pos.y + box.height, box.pos.x + box.width, box.pos.y + box.height, color);
    DrawLine(box.pos.x + box.width, box.pos.y, box.pos.x + box.width, box.pos.y + box.height, color);
}

void drawHitBox(Polygon* polygon, minesSize size, Color color)
{
    drawAABBBox(polygon->colisionBoxAABB, color);

    for (int j = 0; j < polygon->triangleCount; j++)
    {
        for (int i = 0; i < 3; i++)
        {
            if (i == 2)
                DrawLine(polygon->center.x + polygon->triangle[j].vertex[i].x*size/4, polygon->center.y + polygon->triangle[j].vertex[i].y*size/4, polygon->center.x + polygon->triangle[j].vertex[0].x*size/4, polygon->center.y + polygon->triangle[j].vertex[0].y*size/4, color);
            else
                DrawLine(polygon->center.x + polygon->triangle[j].vertex[i].x*size/4, polygon->center.y + polygon->triangle[j].vertex[i].y*size/4, polygon->center.x + polygon->triangle[j].vertex[i+1].x*size/4, polygon->center.y + polygon->triangle[j].vertex[i+1].y*size/4, color);
        }
    }
}

void freePolygon(Polygon* Polygon)
{
    free(Polygon->vertex);
    free(Polygon->triangle);
}

// =================== [Colision check] ===================

void killPlayer(Player* player)
{
    player->isAlive = false;
    player->life--;
    player->timeLastDeath = GetTime();
}

void checkBulletPlayerColision(Game* game, Player* player)
{
    for (int i = 0; i < game->bulletCount; i++)
    {
        if (GetTime() - game->bullets[i].time > 0.5f)
        {
            if (isCollisionAABB(game->bullets[i].box, player->playerPolygon.colisionBoxAABB))
            {
                if (isColisionSAT(&player->playerPolygon, &game->bullets[i].polygon))
                {
                    killPlayer(player);
                    game->bullets[i].flag = false;
                }
            }
        }
    }
}

void checkMinePlayerColision(Game* game, Player* player)
{
    for (int i = 0; i < game->enemiesAlive; i++)
    {
        if (isPolygonColision(&player->playerPolygon, &game->mines[i].polygon))
        {
            game->mines[i].dead = true;
            killPlayer(player);
        }
    }
}

void checkPlayerColision(Game* game, int playerCount)
{
    if (playerCount == 2)
    {
        if (game->player[0].isAlive && game->player[1].isAlive)
        {
            if (isPolygonColision(&game->player[1].playerPolygon, &game->player[0].playerPolygon))
            {
                killPlayer(&game->player[0]);
                killPlayer(&game->player[1]);
            }
        }
    }
    for (int i = 0; i < playerCount; i++)
    {
        if (GetTime() - game->player[i].timeLastDeath > 2.0f)
        {
            checkBulletPlayerColision(game, &game->player[i]);
            checkMinePlayerColision(game, &game->player[i]);
        }
    }
}

void checkMineBulletsColision(Game* game)
{
    for (int i = 0; i < game->enemiesAlive; i++)
    {
        for  (int j = 0; j < game->bulletCount; j++)
        {
            if (game->bullets[j].type == BT_PLAYER)
            {
                if (isCollisionAABB(game->mines[i].polygon.colisionBoxAABB, game->bullets[j].box))
                {
                    if (isColisionSAT(&game->mines[i].polygon, &game->bullets[j].polygon))
                    {
                        game->bullets[j].flag = false;
                        game->mines[i].dead = true;
                        game->player[game->bullets[j].playerID].score += game->mines[j].scoreYield;
                    }
                }
            }
        }
    }
}

void checkBulletsBulletsColision(Game* game)
{
    for (int i = 0; i < game->bulletCount; i++)
    {
        for  (int j = 0; j < game->bulletCount; j++)
        {
            if (game->bullets[i].type == BT_MINES && game->bullets[j].type == BT_PLAYER)
            {
                if (isCollisionAABB(game->bullets[i].box, game->bullets[j].box))
                {
                    switch (game->bullets[i].type)
                    {
                    case BT_PLAYER:
                        game->player[game->bullets[i].playerID].score += 110;
                        game->bullets[i].flag = false;
                        game->bullets[j].flag = false;
                        break;
                    
                    default:
                        break;
                    }

                    switch (game->bullets[j].type)
                    {
                    case BT_PLAYER:
                        game->player[game->bullets[j].playerID].score += 110;
                        game->bullets[i].flag = false;
                        game->bullets[j].flag = false;
                        break;
                    
                    default:
                        break;
                    }
                }
            }
        }
    }
}

// =================== [Bullets] ===================

void drawBullet(Bullet* bullet, Texture2D texture)
{
    float frameWidth = texture.width/4;
    float frameHeight = texture.height/2;

    Rectangle frameRec = { 1.0f, 1.0f, (float)frameWidth, (float)frameHeight };

    int currentFrame = 3;
    int currentLine = 0;

    frameRec.x = currentFrame * frameWidth;
    frameRec.y = currentLine * frameHeight;

    Rectangle destRec = { bullet->position.x, bullet->position.y, frameWidth*0.22f, frameHeight*0.22f };
    Float2 center = { destRec.width/2, destRec.height/2};

    DrawTexturePro(texture, frameRec, destRec, myVector2ToVector2Convert(center), bullet->angle, WHITE);

}

void cleanBullet(Game* game)
{
    for (int i = 0; i < game->bulletCount; i++)
    {
        if (!game->bullets[i].flag || GetTime() - game->bullets[i].time > 2.0f)
        {
            game->bullets[i].position.y = -5;
            freePolygon(&game->bullets[i].polygon);
            game->bullets[i] = game->bullets[game->bulletCount - 1];
            game->bulletCount--;
        }
    }
}

void bulletsUptadteAndDraw(Game* game, Texture2D texture)
{
    for (int i = 0; i < game->bulletCount; i++)
    {
       game->bullets[i].position.x += cosf(degreesToRad(game->bullets[i].angle))*3; 
       game->bullets[i].position.y += sinf(degreesToRad(game->bullets[i].angle))*3; 

       game->bullets[i].box.pos.x = game->bullets[i].position.x - 5;
       game->bullets[i].box.pos.y = game->bullets[i].position.y - 5;

       game->bullets[i].polygon.center.x = game->bullets[i].position.x;
       game->bullets[i].polygon.center.y = game->bullets[i].position.y;

       drawBullet(&game->bullets[i], texture);
       entityColisionBorder(&game->bullets[i].position);

        if (GetTime() - game->bullets[i].time > 1.5f)
        {
            game->bullets[i].flag = false;
        }
    }
}

void cleanMinesSpawn(Game* game)
{
    for (int i = 0; i < game->spawnMinesCount; i++)
    {
        if (!game->spawnmines[i].show)
        {
            game->spawnmines[i] = game->spawnmines[game->spawnMinesCount - 1];
            game->spawnMinesCount--;
        }
    }
}

void cleanGame(Game* game)
{
    for (int i = 0; i < game->enemiesAlive; i++)
    {
        freePolygon(&game->mines[i].polygon);
    }
    game->enemiesAlive = 0;
    cleanMinesSpawn(game);
}