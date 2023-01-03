#include <stdbool.h>
#include <raylib.h>

#include "../src/myMaths.h"
#include "../src/mines.h"

void drawPolygon(Polygon* polygon, float x, float y, minesSize size, Color color)
{
    polygon->center.x = x;
    polygon->center.y = y;
    for (int i = 0; i < polygon->vertexCount; i++)
    {
        if (i == polygon->vertexCount - 1)
            DrawLine(polygon->center.x + polygon->vertex[i].x*size/4, polygon->center.y + polygon->vertex[i].y*size/4, polygon->center.x + polygon->vertex[0].x*size/4, polygon->center.y + polygon->vertex[0].y*size/4, color);
        else
            DrawLine(polygon->center.x + polygon->vertex[i].x*size/4, polygon->center.y + polygon->vertex[i].y*size/4, polygon->center.x + polygon->vertex[i+1].x*size/4, polygon->center.y + polygon->vertex[i+1].y*size/4, color);
    }
}

void drawHitBox(Polygon* polygon, float x, float y, minesSize size, Color color)
{
    polygon->center.x = x;
    polygon->center.y = y;
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

int main()
{
    Float2 mineLayerVertices[11] = {{-127.0f, 32.0f}, {-107.0f, -16.0f}, {-34.0f, -16.0f}, {0.0f, -43.0f}, {33.0f, -16.0f}, {106.0f, -16.0f}, {126.0f, 32.0f}, {108.0f, 11.0f}, {69.0f, 11.0f}, {-64.0f, 11.0f}, {-107.0f, 11.0f}};
    myTriangle mineLayerTriangle[7] = {{{mineLayerVertices[0], mineLayerVertices[1], mineLayerVertices[10]}}, 
                                        {{mineLayerVertices[10], mineLayerVertices[1], mineLayerVertices[9]}},
                                        {{mineLayerVertices[1], mineLayerVertices[2], mineLayerVertices[9]}},
                                        {{mineLayerVertices[9], mineLayerVertices[3], mineLayerVertices[8]}},
                                        {{mineLayerVertices[8], mineLayerVertices[5], mineLayerVertices[4]}},
                                        {{mineLayerVertices[8], mineLayerVertices[5], mineLayerVertices[7]}},
                                        {{mineLayerVertices[5], mineLayerVertices[6], mineLayerVertices[7]}}};
    Polygon mineLayer = {11, mineLayerVertices, {0,0}, false, 7, mineLayerTriangle};

    Float2 floatingMineVertices[6] = {{0.0f, -72.0f}, {18.0f, -14.0f}, {58.0f, 33.0f}, {0.0f, 23.0f}, {-55.0f, 36.0f}, {-18.0f, -13.0f}};
    myTriangle floatingMineTriangle[4] = {{{floatingMineVertices[0], floatingMineVertices[1], floatingMineVertices[5]}}, 
                                        {{floatingMineVertices[1], floatingMineVertices[2], floatingMineVertices[3]}},
                                        {{floatingMineVertices[3], floatingMineVertices[4], floatingMineVertices[5]}},
                                        {{floatingMineVertices[1], floatingMineVertices[3], floatingMineVertices[5]}}};
    Polygon floatingMine = {6, floatingMineVertices, {0,0}, false, 4, floatingMineTriangle};

    Float2 magneticMineVertices[8] = {{-46.0f, -47.0f}, {0.0f, -26.0f}, {46.0f, -47.0f}, {26.0f, 0.0f}, {46.0f, 48.0f}, {0.0f, 27.0f}, {-46.0f, 48.0f}, {-25.0f, 0.0f}};
    myTriangle magneticMineTriangle[6] = {{{magneticMineVertices[0], magneticMineVertices[1], magneticMineVertices[7]}}, 
                                        {{magneticMineVertices[1], magneticMineVertices[2], magneticMineVertices[3]}},
                                        {{magneticMineVertices[3], magneticMineVertices[4], magneticMineVertices[5]}},
                                        {{magneticMineVertices[5], magneticMineVertices[6], magneticMineVertices[7]}},
                                        {{magneticMineVertices[1], magneticMineVertices[5], magneticMineVertices[7]}},
                                        {{magneticMineVertices[1], magneticMineVertices[3], magneticMineVertices[5]}}};
    Polygon magneticMine = {8, magneticMineVertices, {0,0}, false, 6, magneticMineTriangle};

    Float2 magneticFireballVertices[12] = {{-44.0f, -75.0f}, {-32.0f, -45.0f}, {43.0f, -45.0f}, {73.0f, -45.0f}, {43.0f, -31.0f}, {43.0f,46.0f}, {43.0f, 78.0f}, {29.0f, 46.0f}, {-44.0f, 46.0f}, {-73.0f, 46.0f}, {-44.0f, 34.0f}, {-44.0f, -45.0f}};
    myTriangle magneticFireballTriangle[7] = {{{magneticFireballVertices[0], magneticFireballVertices[1], magneticFireballVertices[11]}}, 
                                        {{magneticFireballVertices[1], magneticFireballVertices[2], magneticFireballVertices[5]}},
                                        {{magneticFireballVertices[2], magneticFireballVertices[3], magneticFireballVertices[4]}},
                                        {{magneticFireballVertices[5], magneticFireballVertices[6], magneticFireballVertices[7]}},
                                        {{magneticFireballVertices[7], magneticFireballVertices[8], magneticFireballVertices[11]}},
                                        {{magneticFireballVertices[8], magneticFireballVertices[9], magneticFireballVertices[10]}},
                                        {{magneticFireballVertices[1], magneticFireballVertices[5], magneticFireballVertices[11]}}};
    Polygon magneticFireball = {12, magneticFireballVertices, {0,0}, false, 7, magneticFireballTriangle};

    Float2 fireballMineVertices[8] = {{-50.0f, -50.0f}, {0.0f, -40.0f}, {50.0f, -50.0f}, {40.0f, 0.0f}, {50.0f, 50.0f}, {0.0f, 40.0f}, {-50.0f, 50.0f}, {-40.0f, 0.0f}};
    myTriangle fireballMineTriangle[6] = {{{fireballMineVertices[0], fireballMineVertices[1], fireballMineVertices[7]}}, 
                                        {{fireballMineVertices[1], fireballMineVertices[2], fireballMineVertices[3]}},
                                        {{fireballMineVertices[3], fireballMineVertices[4], fireballMineVertices[5]}},
                                        {{fireballMineVertices[5], fireballMineVertices[6], fireballMineVertices[7]}},
                                        {{fireballMineVertices[7], fireballMineVertices[1], fireballMineVertices[5]}},
                                        {{fireballMineVertices[1], fireballMineVertices[3], fireballMineVertices[5]}}};
    Polygon fireballMine = {8, fireballMineVertices, {0,0}, false, 6, fireballMineTriangle};

    Float2 playerVertices[8] = {{0.0f, -62.0f}, {18.0f, -23.0f}, {31.0f, 76.0f}, {5.0f, 48.0f}, {0.0f, 86.0f}, {-5.0f, 48.0f}, {-30.0f, 76.0f}, {-17.0f, -29.0f}};
    myTriangle playerTriangle[4] = {{{playerVertices[0], playerVertices[1], playerVertices[7]}}, 
                                        {{playerVertices[1], playerVertices[2], playerVertices[3]}},
                                        {{playerVertices[1], playerVertices[4], playerVertices[7]}},
                                        {{playerVertices[5], playerVertices[6], playerVertices[7]}}};
    Polygon player = {8, playerVertices, {0, 0}, false, 4, playerTriangle};

    InitWindow(800, 800, "Test Polygon Drawing");
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();

        ClearBackground(BLACK);

        DrawText("Mine layer", 100, 100, 15, RED);
        drawPolygon(&mineLayer, 100, 150, MS_MEDIUM, RED);
        DrawCircle(100, 150, 2, PURPLE);

        DrawText("Floating Mine", 300, 75, 15, RED);
        drawPolygon(&floatingMine, 300, 150, MS_BIG, RED);
        drawPolygon(&floatingMine, 300, 250, MS_MEDIUM, RED);
        drawPolygon(&floatingMine, 300, 325, MS_SMALL, RED);
        DrawCircle(300, 150, 2, PURPLE);


        DrawText("Magnetic Mine", 500, 95, 15, RED);
        drawPolygon(&magneticMine, 500, 150, MS_BIG, RED);
        drawPolygon(&magneticMine, 500, 250, MS_MEDIUM, RED);
        drawPolygon(&magneticMine, 500, 325, MS_SMALL, RED);
        DrawCircle(500, 150, 2, PURPLE);

        DrawText("Magnetic Fireball Mine", 100, 250, 15, RED);
        drawPolygon(&magneticFireball, 100, 325, MS_BIG, RED);
        drawPolygon(&magneticFireball, 100, 425, MS_MEDIUM, RED);
        drawPolygon(&magneticFireball, 100, 500, MS_SMALL, RED);
        DrawCircle(100, 325, 2, PURPLE);

        DrawText("Fireball Mine", 400, 375, 15, RED);
        drawPolygon(&fireballMine, 400, 450, MS_BIG, RED);
        drawPolygon(&fireballMine, 400, 550, MS_MEDIUM, RED);
        drawPolygon(&fireballMine, 400, 625, MS_SMALL, RED);
        DrawCircle(400, 450, 2, PURPLE);

        DrawText("Player's ship", 650, 575, 15, GREEN);
        drawPolygon(&player, 600, 600, MS_MEDIUM, GREEN);
        DrawCircle(600, 600, 2, PURPLE);

        if (IsKeyDown(KEY_C))
        {
            drawHitBox(&mineLayer, 100, 150, MS_MEDIUM, YELLOW);

            drawHitBox(&floatingMine, 300, 150, MS_BIG, YELLOW);
            drawHitBox(&floatingMine, 300, 250, MS_MEDIUM, YELLOW);
            drawHitBox(&floatingMine, 300, 325, MS_SMALL, YELLOW);

            drawHitBox(&magneticMine, 500, 150, MS_BIG, YELLOW);
            drawHitBox(&magneticMine, 500, 250, MS_MEDIUM, YELLOW);
            drawHitBox(&magneticMine, 500, 325, MS_SMALL, YELLOW);

            drawHitBox(&magneticFireball, 100, 325, MS_BIG, YELLOW);
            drawHitBox(&magneticFireball, 100, 425, MS_MEDIUM, YELLOW);
            drawHitBox(&magneticFireball, 100, 500, MS_SMALL, YELLOW);

            drawHitBox(&fireballMine, 400, 450, MS_BIG, YELLOW);
            drawHitBox(&fireballMine, 400, 550, MS_MEDIUM, YELLOW);
            drawHitBox(&fireballMine, 400, 625, MS_SMALL, YELLOW);

            drawHitBox(&player, 600, 600, MS_MEDIUM, YELLOW);
        }

        EndDrawing();
    }
    
}
