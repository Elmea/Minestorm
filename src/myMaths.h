#pragma once
#include <stdbool.h>
#include <stdarg.h>

#define MY_PI 3.14159265

typedef struct Float2
{
    float x;
    float y;
}Float2;

typedef struct myLine
{
    float m;
    float p;
}myLine;

typedef struct myCircle
{
    Float2 center;
    float radius;
}myCircle;

typedef struct myTriangle
{
    Float2 vertex[3];
}myTriangle;

typedef struct AABB
{
    Float2 pos;
    float width;
    float height;
}AABB;

typedef struct Polygon
{
    int vertexCount;
    Float2* vertex;
    Float2 center;

    int triangleCount;
    myTriangle* triangle;
    AABB colisionBoxAABB;
}Polygon;

float Pythagoreantheorem(int nb_values, ...);

float getSquareRoot(float X);

int absoluteValueInt(int value);

float absoluteValueFloat(float value);

float crossProduct2D(Float2 vector1, Float2 vector2);

bool vectorIsCollinear(Float2 vector1, Float2 vector2);

float getPointYByLineEquation(myLine line, Float2 point);

float pointLineDistance2D(myLine line, Float2 point);

float degreesToRad(float degrees);

float radToDregrees(float rad);

void getTriangleListByPolygon(Polygon* polygon);

Float2 barrycentre(int nb_values, ...);

void planRotation(Float2* point, float angle);

float dotProduct(Float2* vect1, Float2* vect2);

bool isCollisionAABB(AABB box1,AABB box2);

bool isColisionSAT(Polygon* polygon1, Polygon* polygon2);

Float2 triangleProjectionOnAxis(myTriangle* triangle, Float2* axis, Float2* position);

bool triangleSATColision(myTriangle* triangle1, Float2* pos1, myTriangle* triangle2, Float2* pos2);

bool isPolygonColision(Polygon* polygon1, Polygon* polygon2);

bool isCollisionAABB(AABB box1,AABB box2);