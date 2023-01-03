#include <raylib.h>
#include <stdbool.h>

typedef struct AABB
{
    int x;
    int y;
    int width;
    int height;
}AABB;

typedef struct Entity
{
    int x;
    int y;
    AABB box;
}Entity;

typedef struct Main
{
    Entity entity[5];
}Main;


bool isCollisionAABB(AABB box1,AABB box2)
{
    if ((box2.x >= box1.x + box1.width)
    || (box2.x + box2.width <= box1.x)
    || (box2.y >= box1.y + box1.height)
    || (box2.y + box2.height <= box1.y)) 
        return false;
    else 
        return true;
}

void showDebugInfo(Main* game)
{
    DrawText(TextFormat("Yellow X : %d", game->entity[0].x), 0, 0, 15, YELLOW);
    DrawText(TextFormat("Yellow Xmax : %d", game->entity[0].x + game->entity[0].box.width), 0, 16, 15, YELLOW);
    DrawText(TextFormat("Purple X : %d", game->entity[1].x), 200, 0, 15, PURPLE);
    DrawText(TextFormat("Purple Xmax : %d", game->entity[1].x + game->entity[1].box.width), 200, 16, 15, PURPLE);
    DrawText(TextFormat("Purple Y : %d", game->entity[1].y), 200, 32, 15, PURPLE);
    DrawText(TextFormat("Purple Ymax : %d", game->entity[1].y + game->entity[1].box.height), 200, 48, 15, PURPLE);
    DrawText(TextFormat("Blue Y : %d", game->entity[2].y), 400, 0, 15, BLUE);
    DrawText(TextFormat("Blue Ymax : %d", game->entity[2].y + game->entity[2].box.height), 400, 16, 15, BLUE);
    DrawText(TextFormat("Green X : %d", game->entity[3].x), 600, 0, 15, GREEN);
    DrawText(TextFormat("Green Xmax : %d", game->entity[3].x + game->entity[3].box.width), 600, 16, 15, GREEN);
    DrawText(TextFormat("Green Y : %d", game->entity[3].y), 600, 32, 15, GREEN);
    DrawText(TextFormat("Green Ymax : %d", game->entity[3].y + game->entity[3].box.height), 600, 48, 15, GREEN);

}

void initEntity(Main* game)
{
    game->entity[0].x = 200;
    game->entity[0].y = 400;
    game->entity[1].x = 400;
    game->entity[1].y = 400;
    game->entity[2].x = 400;
    game->entity[2].y = 0;
    game->entity[3].x = 600;
    game->entity[3].y = 600;
    
    game->entity[0].box.width = 50;
    game->entity[0].box.height = 50;
    game->entity[1].box.width = 50;
    game->entity[1].box.height = 50;
    game->entity[2].box.width = 50;
    game->entity[2].box.height = 50;
    game->entity[3].box.width = 50;
    game->entity[3].box.height = 50;
    game->entity[4].box.width = 50;
    game->entity[4].box.height = 50;
}
    
int main()
{
    InitWindow(800, 800, "Test AABB colision");
    SetTargetFPS(60);

    Main game = {0};
    initEntity(&game);
    Color colorx = YELLOW;
    Color colory = BLUE;
    Color colord = GREEN;
    Color colorCur = WHITE;

    while (!WindowShouldClose())
    {
        colorx = YELLOW;
        colory = BLUE;
        colord = GREEN;
        colorCur = WHITE;

        game.entity[0].x++;
        if (game.entity[0].x > 800) game.entity[0].x = 0;

        game.entity[2].y++;
        if (game.entity[2].y > 800) game.entity[2].y = 0;

        game.entity[3].x++;
        game.entity[3].y++;
        if (game.entity[3].y > 800) game.entity[3].y = 0;
        if (game.entity[3].x > 800) game.entity[3].x = 0;

        game.entity[0].box.x = game.entity[0].x;
        game.entity[0].box.y = game.entity[0].y;

        game.entity[1].box.x = game.entity[1].x;
        game.entity[1].box.y = game.entity[1].y;

        game.entity[2].box.x = game.entity[2].x;
        game.entity[2].box.y = game.entity[2].y;

        game.entity[3].box.x = game.entity[3].x;
        game.entity[3].box.y = game.entity[3].y;

        game.entity[4].x = GetMouseX();
        game.entity[4].y = GetMouseY();
        game.entity[4].box.x = game.entity[4].x;
        game.entity[4].box.y = game.entity[4].y;

        if (isCollisionAABB(game.entity[0].box, game.entity[1].box)) 
        {
            DrawText("Colision detected", 465, 375, 15, RED);
            colorx = RED;
        }

        if (isCollisionAABB(game.entity[2].box, game.entity[1].box)) 
        {
            DrawText("Colision detected", 465, 375, 15, RED);
            colory = RED;
        }

        if (isCollisionAABB(game.entity[3].box, game.entity[1].box)) 
        {
            DrawText("Colision detected", 465, 375, 15, RED);
            colord = RED;
        }

        if (isCollisionAABB(game.entity[4].box, game.entity[1].box)) 
        {
            DrawText("Colision detected", 465, 375, 15, RED);
            colorCur = RED;
        }

        BeginDrawing();
        ClearBackground(BLACK);
        DrawText("Test AABB", 200, 200, 50, WHITE);

        DrawRectangle(game.entity[1].x, game.entity[1].y, game.entity[1].box.width, game.entity[1].box.height, PURPLE);
        DrawRectangle(game.entity[0].x, game.entity[0].y, game.entity[0].box.width, game.entity[0].box.height, colorx);
        DrawRectangle(game.entity[2].x, game.entity[2].y, game.entity[2].box.width, game.entity[2].box.height, colory);
        DrawRectangle(game.entity[3].x, game.entity[3].y, game.entity[3].box.width, game.entity[3].box.height, colord);
        DrawRectangle(game.entity[4].x, game.entity[4].y, game.entity[4].box.width, game.entity[4].box.height, colorCur);

        showDebugInfo(&game);
        EndDrawing();
    }
    CloseWindow();
    return 0;
}