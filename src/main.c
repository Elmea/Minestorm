#include <raylib.h>
#include <stdbool.h>
#include "game.h"
#include "myMaths.h"
#include "player.h"
#include "mines.h"
#include <stdlib.h>
#include "define.h"

void showDebugInfo(Game* game)
{
    DrawCircle(game->player[0].position.x, game->player[0].position.y, 2, PURPLE);

    DrawText(TextFormat("Speed X : %f", game->player[0].speedX), 0, 0, 15, WHITE);
    DrawText(TextFormat("Speed Y : %f", game->player[0].speedY), 0, 16, 15, WHITE);
    DrawText(TextFormat("Angle : %2.0f", game->player[0].angle), 150, 0, 15, WHITE);
    DrawText(TextFormat("cos : %f  sin : %f", cosf(degreesToRad(game->player[0].angle)), sinf(degreesToRad(game->player[0].angle))), 150, 16, 15, WHITE);
    DrawText(TextFormat("Player X : %2.0f", game->player[0].position.x), 380, 0, 15, WHITE);
    DrawText(TextFormat("Player Y : %2.0f", game->player[0].position.y), 380, 16, 15, WHITE);

    DrawText(TextFormat("Enemies alive : %d", game->enemiesAlive), 500, 0, 15, WHITE);

    DrawFPS(20, 780);
}

void displayGameOver(Game* game, int playerFlag)
{
    DrawText("GAME OVER", SCREEN_WIDTH/4, SCREEN_HEIGHT/2 -100, 50,RED);
    DrawText(TextFormat("SCORE PLAYER 1 : %d", game->player[0].score), SCREEN_WIDTH/3, SCREEN_HEIGHT/2 - 30, 20, BLUE);
    if(playerFlag == 2)
    {
    DrawText(TextFormat("SCORE PLAYER 2 : %d", game->player[1].score), SCREEN_WIDTH/3 - 3, SCREEN_HEIGHT/2 - 10, 20, GREEN);
    }
    DrawText(TextFormat("TOTAL : %d", game->player[0].score + game->player[1].score), SCREEN_WIDTH/3 + 20, SCREEN_HEIGHT/2 + 20, 20, YELLOW);
    DrawText(TextFormat("Level : %d", game->level), SCREEN_WIDTH/2 - 35, SCREEN_HEIGHT/2 - 55, 20, YELLOW);

    DrawText("Press \"ENTER\"   MAIN MENU", SCREEN_WIDTH/4 -50, SCREEN_HEIGHT/2 +150, 15,WHITE);
    DrawText("Press \"ESC\"   QUIT", SCREEN_WIDTH/4 +225, SCREEN_HEIGHT/2 +150, 15,WHITE);
}

void displayMainMenu()
{
    DrawText("Do you want to play ?", SCREEN_WIDTH/4, SCREEN_HEIGHT/2 - 100, 30, WHITE);
    DrawText("Press \"F\"         Solo mode", SCREEN_WIDTH/3, SCREEN_HEIGHT/2 - 50, 20, BLUE);
    DrawText("Press \"K\"         Duo mode", SCREEN_WIDTH/3, SCREEN_HEIGHT/2 - 10, 20, GREEN);
    DrawText("Press \"ESC\"     Exit", SCREEN_WIDTH/3, SCREEN_HEIGHT/2 + 30, 20, RED);
}

void displayScore(Game* game, int playerFlag)
{
    if(playerFlag == 2)
        DrawText(TextFormat("SCORE PLAYER 2 : %d", game->player[1].score), SCREEN_WIDTH/3 + 200, SCREEN_HEIGHT/2 - 280, 15, GREEN);   
    DrawText(TextFormat("SCORE PLAYER 1 : %d", game->player[0].score), SCREEN_WIDTH/3 - 150, SCREEN_HEIGHT/2 - 280, 15, BLUE);
    DrawText(TextFormat("%d", game->level), SCREEN_WIDTH/2, 20, 50, YELLOW);
}

void displayPause(Game* game, int playerFlag)
{
    DrawText("PAUSED", SCREEN_WIDTH/3, SCREEN_HEIGHT/2 -100, 50,WHITE);
    DrawText(TextFormat("SCORE PLAYER 1 : %d", game->player[0].score), SCREEN_WIDTH/3, SCREEN_HEIGHT/2 - 30, 20, BLUE);
    if(playerFlag == 2)
    {
        DrawText(TextFormat("SCORE PLAYER 2 : %d", game->player[1].score), SCREEN_WIDTH/3 - 3, SCREEN_HEIGHT/2 - 10, 20, GREEN);
    }
    DrawText(TextFormat("TOTAL : %d", game->player[0].score + game->player[1].score), SCREEN_WIDTH/3 + 20, SCREEN_HEIGHT/2 + 20, 20, YELLOW);
    DrawText(TextFormat("Level : %d", game->level), SCREEN_WIDTH/2 - 35, SCREEN_HEIGHT/2 - 55, 20, YELLOW);

    DrawText("Press \"SPACE\"   RESUME", SCREEN_WIDTH/4 -50, SCREEN_HEIGHT/2 +150, 15,WHITE);
    DrawText("Press \"ESC\"   QUIT", SCREEN_WIDTH/4 +225, SCREEN_HEIGHT/2 +150, 15,WHITE);
}

void DrawLife(Texture2D texture, Float2 pos, Color color)
{
    float frameWidth = texture.width/4;
    float frameHeight = texture.height/2;

    Rectangle frameRec = { 1.0f, 1.0f, (float)frameWidth, (float)frameHeight };

    int currentFrame = 0;
    int currentLine = 0;

    frameRec.x = currentFrame * frameWidth;
    frameRec.y = currentLine * frameHeight;

    Rectangle destRec = { pos.x, pos.y, frameWidth*0.17f, frameHeight*0.17f };
    Float2 center = { destRec.width/2, destRec.height/2};
    
    DrawTexturePro(texture, frameRec, destRec, myVector2ToVector2Convert(center), 0, color);
}

void displayLife(Game* game, Texture2D texture, int playerFlag)
{
    Float2 P1life1, P2life1;
    P1life1.x = 90; P1life1.y = 90;
    
    P2life1.x = 400; P2life1.y = 90;
   

    if(playerFlag == 2)
    {
        for(int i = 0; i<game->player[1].life; i++)
        {
            DrawLife(texture, P2life1, GREEN);
            P2life1.x += 20;
        }
    }
    for(int i = 0; i<game->player[0].life; i++)
    {
        DrawLife(texture, P1life1, BLUE);
        P1life1.x += 20;
    }

}

void displayLevel(Game* game)
{
    DrawText(TextFormat("%d", game->level), SCREEN_WIDTH/2 - 3, SCREEN_HEIGHT/2 - 375, 50, BLUE);
}

int main(void)
{
    SetConfigFlags(FLAG_VSYNC_HINT);
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Minestorm");
    InitAudioDevice();

    Game game = {0};
    srand( time( NULL ) );
    game.level = 1;

    Texture2D asset = LoadTexture("assets/minestorm_sprite_atlas_mine_storm.png");
    Texture2D background = LoadTexture("assets/minestorm_background.png");
    Texture2D foreground = LoadTexture("assets/minestorm_foreground.png");

    bool gameFlag = false;
    bool menuFlag = true;
    bool debug = false;
    bool isPlayerInit = false;
    bool drawHitBoxes = false;
    bool isLevelInit = false;
    bool gameIsOver = false;
    bool gameIsPause = false;

    int playersFlag = 0;
    //main loop
    while (!WindowShouldClose())
    {
        BeginDrawing();

        DrawTexture(background, 0, 0, WHITE);
        DrawTexture(foreground, 0, 0, WHITE);

// ================================= [Main menu] =================================

        if (menuFlag)
        {
            displayMainMenu();

            gameIsOver = false;
            game.player[0].score = 0;
            game.player[1].score = 0;
            game.player[0].angle = 0;
            game.player[1].angle = 0;

            game.player[0].timeLastDeath = 0.0f;
            game.player[1].timeLastDeath = 0.0f;

            game.player[0].speedX = 0.0f;
            game.player[1].speedX = 0.0f;

            game.player[0].speedY = 0.0f;
            game.player[1].speedY = 0.0f;

            gameIsPause = false;

            if (WindowShouldClose())
            {
                break;
            }

            if (IsKeyPressed(KEY_F))
            {
                playersFlag = 1;
                menuFlag = false;
                gameFlag = true;
            }
            if (IsKeyPressed(KEY_K))
            {
                playersFlag = 2;
                menuFlag = false;
                gameFlag = true;
            }
        }

// ================================= [Main game loop] =================================

        if (gameFlag)
        {
            if (!isPlayerInit)
            {
                game.level = 1;
                if (playersFlag == 2)
                {
                    twoPlayerInit(&game);
                }
                else playerInit(&game.player[0]);

                isPlayerInit = true;
            }
            if(!isLevelInit)
            {
                game.enemiesAlive = 0;
                cleanMinesSpawn(&game);
                createMinesSpawnPoint(&game, 7*(2 + game.level));
                createRandomMine(&game, 2 + game.level);
                game.time = GetTime();
                isLevelInit = true;
                gameIsOver = false;
            }

            DrawTexture(background, 0, 0, WHITE);
            
// ================================= [Update and draw] =================================

            playerUpdateAndDraw(&game, 0, &game.player[0], KEY_D, KEY_G, KEY_R, KEY_F, KEY_E, KEY_T, BLUE);
            if (playersFlag == 2)
                playerUpdateAndDraw(&game, 1, &game.player[1], KEY_J, KEY_L, KEY_I, KEY_K, KEY_U, KEY_O, GREEN);

            bulletsUptadteAndDraw(&game, asset);

            mineUpdateAndDraw(&game);

            drawMinesSpawn(&game, asset, 7*(2 + game.level));

            DrawTexture(foreground, 0, 0, WHITE);

            displayScore(&game, playersFlag);
            displayLife(&game, asset, playersFlag);

            if (IsKeyPressed(KEY_F3))
            {
                if (debug)
                    debug = false;
                else
                    debug = true;
            }

            if (IsKeyPressed(KEY_C))
            {
                if (drawHitBoxes)
                    drawHitBoxes = false;
                else
                    drawHitBoxes = true;
            }

            if (IsKeyPressed(KEY_ENTER))
            {
                gameIsPause = true;
                gameFlag = false;
            }

// ================================= [Cheat key] =================================

            if (IsKeyPressed(KEY_F5))
            {
                killPlayer(&game.player[0]);
            }
            if (IsKeyPressed(KEY_F6))
            {
                killPlayer(&game.player[1]);
            }
            if (IsKeyPressed(KEY_F7))
            {
                game.enemiesAlive = 0;
            }
            if (IsKeyPressed(KEY_F9))
            {
                game.player[0].life = 5;
            }
            if (IsKeyPressed(KEY_F10))
            {
                game.player[1].life = 5;
            }
// ================================= [Debug and hitboxes] =================================

            if (debug) showDebugInfo(&game);

            if (drawHitBoxes)
            {
                drawHitBox(&game.player[0].playerPolygon, MS_SMALL, YELLOW);
                drawPlayerDirectionMark(&game.player[0]);
                if (playersFlag == 2) 
                {
                    drawHitBox(&game.player[1].playerPolygon, MS_SMALL, PURPLE);
                    drawPlayerDirectionMark(&game.player[1]);
                }
                for (int i = 0; i < game.bulletCount; i++)
                {
                    drawAABBBox(game.bullets[i].box, YELLOW);
                }
                for (int i = 0; i < game.enemiesAlive; i++)
                {
                    drawHitBox(&game.mines[i].polygon, game.mines[i].size, DARKGREEN);
                }
            }

// ================================= [Colision Check] =================================

            checkPlayerColision(&game, playersFlag);
            checkMineBulletsColision(&game);

            chekDeathMines(&game);

            cleanBullet(&game);

// ================================= [Player respawn] =================================

            if(playersFlag == 1)
            {
                if (!game.player[0].isAlive)
                {
                    if (game.player[0].life > 0)
                    {
                        playersRespawn(&game, 1, &game.player[0]);
                    }
                }
            }
            else if (playersFlag == 2)
            {
                if (!game.player[0].isAlive && !game.player[1].isAlive)
                {
                    if (game.player[0].life > 0 && game.player[1].life > 0)
                    {
                        playersRespawn(&game, 2, &game.player[0]);
                    }
                    else if (game.player[0].life > 0)
                    {
                        playersRespawn(&game, 1, &game.player[0]);
                    }
                    else if (game.player[1].life > 0)
                    {
                        playersRespawn(&game, 1, &game.player[1]);
                    }
                }
            }

// ================================= [Game over] =================================

            if(playersFlag == 2)
            {
                if(game.player[0].life == 0 && game.player[1].life == 0)
                {
                    gameIsOver = true;
                }
            }
            else if(playersFlag == 1)
            {
                if(game.player[0].life == 0)
                {
                    gameIsOver = true;
                }
            }

            if (gameIsOver == true)
            {
                displayGameOver(&game, playersFlag);
                if (IsKeyPressed(KEY_ENTER))
                {
                    gameFlag = false;
                    menuFlag = true;
                    debug = false;
                    isPlayerInit = false;
                    drawHitBoxes = false;
                    isLevelInit = false;
                    gameIsOver = false;
                    game.level = 1;
                    cleanGame(&game);
                }
            }

            if (game.enemiesAlive <= 1)
            {
                    drawHitBoxes = false;
                    isLevelInit = false;
                    gameIsOver = false;
                    game.level++;
                    cleanGame(&game);
            }
        }

        if (gameIsPause)
        {
            displayPause(&game, playersFlag);
            if (IsKeyPressed(KEY_SPACE))
            {
                gameIsPause = false;
                gameFlag = true;
            }
        }

        EndDrawing();
    }
    UnloadTexture(background);
    UnloadTexture(foreground);
    UnloadTexture(asset);

    freePolygon(&game.player->playerPolygon);
    for (int i = 0; i < game.enemiesAlive; i++) freePolygon(&game.mines[i].polygon);

    return 0;
}