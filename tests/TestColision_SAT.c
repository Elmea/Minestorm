#include <raylib.h>
#include <stdbool.h>
#include <float.h>
#include <math.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 800

typedef struct Float2
{
    float x;
    float y;
}Float2;

typedef struct myTriangle
{
    Float2 vertex[3];
}myTriangle;

typedef struct Polygon
{
    int vertexCount;
    Float2 vertex[4];
    Float2 center;

    int triangleCount;
    myTriangle triangle[2];
}Polygon;

typedef struct Entity
{
    Polygon entity[5];
}Entity;

void initTest(Entity* test)
{
    test->entity[0].vertexCount = 4;

    test->entity[0].vertex[0] = (Float2){0.0f, 50.0f};
    test->entity[0].vertex[1] = (Float2){50.0f, -50.0f};
    test->entity[0].vertex[3] = (Float2){-50.0f, -50.0f};
    test->entity[0].vertex[2] = (Float2){0.0f, -100.0f};

    test->entity[0].triangle[0] = (myTriangle){{(Float2)test->entity[0].vertex[0], (Float2)test->entity[0].vertex[1], (Float2)test->entity[0].vertex[2]}};
    test->entity[0].triangle[1] = (myTriangle){{(Float2)test->entity[0].vertex[2], (Float2)test->entity[0].vertex[3], (Float2)test->entity[0].vertex[0]}};
    test->entity[0].triangleCount = 2;

    test->entity[0].center.x = WINDOW_WIDTH/2;
    test->entity[0].center.y = WINDOW_HEIGHT/2;
    
    test->entity[1].vertexCount = 3;

    test->entity[1].vertex[0] = (Float2){-60.0f, 20.0f};
    test->entity[1].vertex[1] = (Float2){-50.0f, -40.0f};
    test->entity[1].vertex[2] = (Float2){60.0f, -20.0f};

    test->entity[1].triangle[0] = (myTriangle){{(Float2)test->entity[1].vertex[0], (Float2)test->entity[1].vertex[1], (Float2)test->entity[1].vertex[2]}};
    test->entity[1].triangleCount = 1;

    test->entity[1].center.x = 250;
    test->entity[1].center.y = WINDOW_HEIGHT/2;

    test->entity[2].vertexCount = 3;

    test->entity[2].vertex[0] = (Float2){45.0f, 0.0f};
    test->entity[2].vertex[1] = (Float2){0.0f, -40.0f};
    test->entity[2].vertex[2] = (Float2){-60.0f, 20.0f};

    test->entity[2].triangle[0] = (myTriangle){{(Float2)test->entity[2].vertex[0], (Float2)test->entity[2].vertex[1], (Float2)test->entity[2].vertex[2]}};
    test->entity[2].triangleCount = 1;

    test->entity[2].center.x = WINDOW_WIDTH/2;
    test->entity[2].center.y = 600;

    test->entity[3].vertexCount = 3;

    test->entity[3].vertex[0] = (Float2){60.0f, 20.0f};
    test->entity[3].vertex[1] = (Float2){50.0f, -40.0f};
    test->entity[3].vertex[2] = (Float2){-60.0f, -20.0f};

    test->entity[3].triangle[0] = (myTriangle){{(Float2)test->entity[3].vertex[0], (Float2)test->entity[3].vertex[1], (Float2)test->entity[3].vertex[2]}};
    test->entity[3].triangleCount = 1;

    test->entity[3].center.x = 0;
    test->entity[3].center.y = 0;

    test->entity[4].vertexCount = 3;

    test->entity[4].vertex[0] = (Float2){20.0f, 0.0f};
    test->entity[4].vertex[1] = (Float2){0.0f, -25.0f};
    test->entity[4].vertex[2] = (Float2){-20.0f, 0.0f};

    test->entity[4].triangle[0] = (myTriangle){{(Float2)test->entity[4].vertex[0], (Float2)test->entity[4].vertex[1], (Float2)test->entity[4].vertex[2]}};
    test->entity[4].triangleCount = 1;

    test->entity[4].center.x = 0;
    test->entity[4].center.y = 0;
}

void drawPolygon(Polygon* polygon, Color color)
{
    for (int i = 0; i < polygon->vertexCount; i++)
    {
        DrawLine(polygon->center.x + polygon->vertex[i].x, polygon->center.y + polygon->vertex[i].y, polygon->center.x + polygon->vertex[(i+1)%polygon->vertexCount].x, polygon->center.y + polygon->vertex[(i+1)%polygon->vertexCount].y, color);
    }
}

float dotProduct(Float2* vect1, Float2* vect2)
{
    return (vect1->x * vect2->x) + (vect1->y * vect2->y);
}

Float2 triangleProjectionOnAxis(myTriangle* triangle, Float2* axis, Float2* position)
{
    float min = FLT_MAX;
    float max = -(FLT_MAX);
    float temp;
    for (int i = 0; i < 3; i++)
    {
        //Take world position
        Float2 tempVertex;
        tempVertex.x = triangle->vertex[i].x + position->x;
        tempVertex.y = triangle->vertex[i].y + position->y;

        temp = dotProduct(&tempVertex, axis);

        if (temp < min) min = temp;
        if (temp > max) max = temp;
    }
    return (Float2){min, max};
}

bool triangleSATColision(myTriangle* triangle1, Float2* pos1, myTriangle* triangle2, Float2* pos2)
{
    Float2 axisToTest;
    for(int i = 0; i < 6; i++)
    {
        //Axis to test are Normal vector of the edges
        if (i < 3) axisToTest = (Float2){-(triangle1->vertex[(i + 1) % 3].y - triangle1->vertex[i%3].y), (triangle1->vertex[(i + 1) % 3].x - triangle1->vertex[i%3].x)}; // For triangle 1
        else axisToTest = (Float2){-(triangle2->vertex[(i + 1) % 3].y - triangle2->vertex[i%3].y), (triangle2->vertex[(i + 1) % 3].x - triangle2->vertex[i%3].x)}; // For triangle 2

        Float2 axisTemp = axisToTest;

        axisToTest.x = axisTemp.x/sqrtf(axisTemp.x*axisTemp.x + axisTemp.y*axisTemp.y);
        axisToTest.y = axisTemp.y/sqrtf(axisTemp.x*axisTemp.x + axisTemp.y*axisTemp.y);

        Float2 projection1 = triangleProjectionOnAxis(triangle1, &axisToTest, pos1); //x is min, y is max
        Float2 projection2 = triangleProjectionOnAxis(triangle2, &axisToTest, pos2);

        //Check if ther is a gap, if there is one, there is no colision.
        if (projection1.y < projection2.x || projection1.x > projection2.y)
            return false;
    }
    return true;
}

bool isColisionSAT(Polygon* polygon1, Polygon* polygon2)
{
    for (int i = 0; i < polygon1->triangleCount; i++)
    {
        for (int j = 0; j < polygon2->triangleCount; j++)
        {
            if (triangleSATColision(&polygon1->triangle[i], &polygon1->center, &polygon2->triangle[j], &polygon2->center)) return true;
        }
    }
    return false;
}

int main()
{
    SetConfigFlags(FLAG_VSYNC_HINT);
    InitWindow(800, 800, "Test SAT colision");
    InitAudioDevice();

    Entity test = {0};
    initTest(&test);
    
    Color colorx;
    Color colory;
    Color colorz;
    Color colorCur;

    while (!WindowShouldClose())
    {
        colorx = YELLOW;
        colory = PURPLE;
        colorz = GREEN;
        colorCur = WHITE;

        test.entity[1].center.x++;
        if (test.entity[1].center.x > WINDOW_WIDTH) test.entity[1].center.x = 0;

        test.entity[2].center.y++;
        if (test.entity[2].center.y > WINDOW_WIDTH) test.entity[2].center.y = 0;

        test.entity[3].center.y++;
        test.entity[3].center.x++;
        if (test.entity[3].center.y > WINDOW_WIDTH) test.entity[3].center.y = 0;
        if (test.entity[3].center.x > WINDOW_WIDTH) test.entity[3].center.x = 0;

        test.entity[4].center.x = GetMouseX();
        test.entity[4].center.y = GetMouseY();

        BeginDrawing();
        ClearBackground(BLACK);
        DrawText("Test SAT", 250, 200, 50, WHITE);

        if (isColisionSAT(&test.entity[0], &test.entity[1]))
        {
            colorx = RED;
            DrawText("Colision detected !", WINDOW_WIDTH/2 - 50, WINDOW_HEIGHT/2 - 70, 11, RED);
        }

        if (isColisionSAT(&test.entity[0], &test.entity[2]))
        {
            colory = RED;
            DrawText("Colision detected !", WINDOW_WIDTH/2 + 50, WINDOW_HEIGHT/2, 11, RED);
        }

        if (isColisionSAT(&test.entity[0], &test.entity[3]))
        {
            colorz = RED;
            DrawText("Colision detected !", WINDOW_WIDTH/2 + 50, WINDOW_HEIGHT/2 + 50, 11, RED);
        }

        if (isColisionSAT(&test.entity[0], &test.entity[4]))
        {
            colorCur = RED;
            DrawText("Colision detected !", GetMouseX(), GetMouseY() - 30, 15, RED);
        }

        drawPolygon(&test.entity[0], BLUE);
        drawPolygon(&test.entity[1], colorx);
        drawPolygon(&test.entity[2], colory);
        drawPolygon(&test.entity[3], colorz);
        drawPolygon(&test.entity[4], colorCur);

        EndDrawing();
    }
    CloseWindow();
    return 0;
}