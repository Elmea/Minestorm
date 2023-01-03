#include <raylib.h>
#include <math.h>
#include "player.h"
#include "myMaths.h"
#include "game.h"
#include <stdlib.h>

Polygon playerPolygonInit()
{
    Float2* playerVertices = calloc(1, 8*sizeof(Float2));
    playerVertices[0] = (Float2){62.0f, 0.0f}; 
    playerVertices[1] = (Float2){23.0f, 18.0f}; 
    playerVertices[2] = (Float2){-76.0f, 31.0f}; 
    playerVertices[3] = (Float2){-48.0f, 5.0f}; 
    playerVertices[4] = (Float2){-86.0f, 0.0f};
    playerVertices[5] = (Float2){-48.0f, -5.0f};
    playerVertices[6] = (Float2){-76.0f, -30.0f}; 
    playerVertices[7] = (Float2){29.0f, -17.0f};
    myTriangle* playerTriangle = calloc(1, 4*sizeof(myTriangle));
    playerTriangle[0] = (myTriangle){{(Float2)playerVertices[0], (Float2)playerVertices[1], (Float2)playerVertices[7]}};
    playerTriangle[1] = (myTriangle){{(Float2)playerVertices[1], (Float2)playerVertices[4], (Float2)playerVertices[7]}};
    playerTriangle[2] = (myTriangle){{(Float2)playerVertices[1], (Float2)playerVertices[2], (Float2)playerVertices[3]}};
    playerTriangle[3] = (myTriangle){{(Float2)playerVertices[5], (Float2)playerVertices[6], (Float2)playerVertices[7]}};
    Polygon playerPolygon = {8, playerVertices, {0, 0}, 4, playerTriangle, (AABB){(Float2){0, 0}, 50.0f, 50.0f}};
    return playerPolygon;
}

void playerTriangleRecalculus(Polygon* polygon)
{
    polygon->triangle[0] = (myTriangle){{(Float2)polygon->vertex[0], (Float2)polygon->vertex[1], (Float2)polygon->vertex[7]}};
    polygon->triangle[1] = (myTriangle){{(Float2)polygon->vertex[1], (Float2)polygon->vertex[4], (Float2)polygon->vertex[7]}};
    polygon->triangle[2] = (myTriangle){{(Float2)polygon->vertex[1], (Float2)polygon->vertex[2], (Float2)polygon->vertex[3]}};
    polygon->triangle[3] = (myTriangle){{(Float2)polygon->vertex[5], (Float2)polygon->vertex[6], (Float2)polygon->vertex[7]}};
}

void drawPlayerDirectionMark(Player* player)
{
    Float2 mark;
    mark.x = player->position.x + player->speedX*8;
    mark.y = player->position.y + player->speedY*8;

    DrawLine(player->position.x, player->position.y, mark.x, mark.y, PURPLE);
}

void playerInit(Player* player)
{
    player->life = 3;
    player->isAlive = true;
    player->playerPolygon = playerPolygonInit();

    player->position.x = SCREEN_WIDTH / 2.f;
    player->position.y = SCREEN_HEIGHT / 2.f;
    player->timeLastDeath = GetTime();
    player->timeLastTP = GetTime();
}

void twoPlayerInit(Game* game)
{
    playerInit(&game->player[0]);
    playerInit(&game->player[1]);

    game->player[0].position.x = 200;
    game->player[0].position.y = SCREEN_HEIGHT / 2.f;

    game->player[1].position.x = 400;
    game->player[1].position.y = SCREEN_HEIGHT / 2.f;
}

void playersRespawn(Game* game, int playerCount, Player* playerToRespawAlone)
{
    if (playerCount == 2)
    {
        game->player[0].position.x = 200;
        game->player[0].position.y = SCREEN_HEIGHT / 2.f;
        game->player[0].isAlive = true;
        game->player[0].timeLastDeath = GetTime();

        game->player[1].position.x = 450;
        game->player[1].position.y = SCREEN_HEIGHT / 2.f;
        game->player[1].isAlive = true;
        game->player[1].timeLastDeath = GetTime();
    }
    else if (playerCount == 1)
    {
        playerToRespawAlone->position.x = SCREEN_WIDTH / 2.f;
        playerToRespawAlone->position.y = SCREEN_HEIGHT / 2.f;
        playerToRespawAlone->isAlive = true;
    }
}

void speedCalculus(Player* player)
{
    player->speedX += cosf(degreesToRad(player->angle))/8;
    player->speedY += sinf(degreesToRad(player->angle))/8;

    if (player->speedX > 300)
        player->speedX = 300;

    if (player->speedY > 300)
        player->speedY = 300;

    if (player->speedX < -300)
        player->speedX = -300;

    if (player->speedY < -300)
        player->speedY = -300;
}

void speedSlowDown(Player* player)
{
    if (player->speedX > 0)
        player->speedX -= 0.06f; 

    if (player->speedY > 0)
        player->speedY -= 0.06f;
    
    if (player->speedX < 0)
        player->speedX += 0.06f; 

    if (player->speedY < 0)
        player->speedY += 0.06f;

    if (player->speedX > -0.5 && player->speedX < 0.5)
        player->speedX = 0; 

    if (player->speedY > -0.5 && player->speedY < 0.5)
        player->speedY = 0; 
}

void makePlayerPointRotation(Player* player)
{
    freePolygon(&player->playerPolygon);
    Polygon tmp = playerPolygonInit();

    for (int i=0; i < player->playerPolygon.vertexCount; i++)
    {
        planRotation(&tmp.vertex[i], player->angle);
    }
    player->playerPolygon = tmp;
}

void drawPlayerTexture(Player* player, Color color)
{
    drawPolygon(&player->playerPolygon, MS_SMALL, color);
}

void playerTeleportation(Player* player)
{
    if (GetTime() - player->timeLastTP > 3.0f)
    {
        player->position.x = rand() % 590;
        player->position.y = rand() % 730;
        player->speedX = 0;
        player->speedY = 0;
        player->timeLastTP = GetTime();
    }
}

void playerPolygonUpdate(Player* player)
{
    player->playerPolygon.center.x = player->position.x;
    player->playerPolygon.center.y = player->position.y;

    player->playerPolygon.colisionBoxAABB.pos.x = player->position.x - 25;
    player->playerPolygon.colisionBoxAABB.pos.y = player->position.y - 25;
    playerTriangleRecalculus(&player->playerPolygon);
}

void playerShoot(Game* game, Float2 bulletPos, float angle, int id)
{
    if (game->bulletCount < BULLET_CAPACITY)
    {
        game->bullets[game->bulletCount].position = bulletPos;
        game->bullets[game->bulletCount].angle = angle;
        game->bullets[game->bulletCount].flag = true;
        game->bullets[game->bulletCount].box = (AABB){(Float2){0, 0}, 13, 13};
        game->bullets[game->bulletCount].polygon = bulletPolygonInit();
        game->bullets[game->bulletCount].type = BT_PLAYER;
        game->bullets[game->bulletCount].time = GetTime();
        game->bullets[game->bulletCount].playerID = id;
        game->bulletCount++;
    }
}

void playerUpdateAndDraw(Game* game, int id, Player* player, KeyboardKey left, KeyboardKey right, KeyboardKey forward, KeyboardKey shoot, KeyboardKey tp1, KeyboardKey tp2, Color color)
{
    if (!player->isAlive)
    {
        player->position.x = -100;
        player->position.y = -100;
    }

    if (player->life <= 0)
    {
        player->life = 0;
        player->isAlive = false;
    }

    // Update
    if (IsKeyDown(left))
    {
        player->angle -= 6.0f;
        if (player->angle <= 0)
            player->angle = 360;
        makePlayerPointRotation(player);
    }
    
    if (IsKeyDown(right))
    {
        player->angle += 6.0f;
        if (player->angle >= 360)
            player->angle = 0;
        makePlayerPointRotation(player);
    }

    if (IsKeyDown(forward))
    {
        speedCalculus(player);
    }
    else
    {
        speedSlowDown(player);
    }

    if (IsKeyPressed(tp1) || IsKeyPressed(tp2))
    {
        playerTeleportation(player);
    }

    if (IsKeyPressed(shoot))
        if (GetTime() - game->time > 0.2f && player->isAlive) playerShoot(game, (Float2){player->position.x + cosf(degreesToRad(player->angle))*40, player->position.y + sinf(degreesToRad(player->angle))*40}, player->angle, id);

    player->position.x += player->speedX;
    player->position.y += player->speedY;

    playerPolygonUpdate(player);

    entityColisionBorder(&player->position);

    if (GetTime() - player->timeLastDeath <= 2)
    {
        drawPlayerTexture(player, WHITE);
    }
    else 
    {
        drawPlayerTexture(player, color);
    }
}