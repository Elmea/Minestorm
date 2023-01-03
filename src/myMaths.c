#include "myMaths.h"
#include <float.h>
#include <math.h>

float getSquareRoot(float X)
{
    float A,B,M,XN;
    if(X==0.0) 
    {
        return 0.0;
    }
    else
    {
        M=1.0;
        XN=X;
        while(XN>=2.0)
        {
            XN=0.25*XN;
            M=2.0*M;
        }
        while(XN<0.5)
        {
            XN=4.0*XN;
            M=0.5*M;
        }
        A=XN;
        B=1.0-XN;
        do 
        {
            A=A*(1.0+0.5*B);
            B=0.25*(3.0+B)*B*B;
        } while(B>=1.0E-15);
        return A*M;
    }
}

float Pythagoreantheorem(int nb_values, ...)
{
    va_list args;
    float nextValue;
    float result;

    va_start(args, nb_values);

    result = 0;
    for (int i = 0; i < nb_values; i++)
    {
        nextValue = va_arg(args, double);
        result += nextValue*nextValue;
    }
    va_end(args);

    return getSquareRoot(result);
}

int absoluteValueInt(int value)
{
    if (value < 0)
        return -value;
    else 
        return value;
}

float absoluteValueFloat(float value)
{
    if (value < 0)
        return -value;
    else 
        return value;
}

float crossProduct2D(Float2 vector1, Float2 vector2)
{
    return vector1.x*vector2.y - vector1.y*vector2.x;
}

bool vectorIsCollinear(Float2 vector1, Float2 vector2)
{
    float delta = crossProduct2D(vector1, vector2);
    if (delta == 0)
    {
        return true;
    }
    else 
    {
        return false;
    }
}

float getPointYByLineEquation(myLine line, Float2 point)
{
    return line.m*point.x + line.p;
}

float pointLineDistance2D(myLine line, Float2 point)
{
    float a = absoluteValueFloat((-line.m)*point.x + point.y - line.p);
    float b = Pythagoreantheorem(2, -line.m, -line.p);

    return a/b;
}

float degreesToRad(float degrees)
{
    return degrees*MY_PI/180;
}

float radToDregrees(float rad)
{
    return rad*180/MY_PI;
}

Float2 barrycentre(int nb_values, ...)
{
    va_list args;
    Float2 nextValue;
    Float2 result = {0};

    va_start(args, nb_values);

    for (int i = 0; i < nb_values; i++)
    {
        nextValue = va_arg(args, Float2);
        result.x += nextValue.x;
        result.y += nextValue.y;
    }
    va_end(args);

    result.x = result.x/nb_values;
    result.y = result.y/nb_values;

    return result;
}

float dotProduct(Float2* vect1, Float2* vect2)
{
    return (vect1->x * vect2->x) + (vect1->y * vect2->y);
}

void planRotation(Float2* point, float angle)
{
    float tmpx = point->x;
    point->x = point->x*cosf(degreesToRad(angle)) - point->y*sinf(degreesToRad(angle));
    point->y = tmpx*sinf(degreesToRad(angle)) + point->y*cosf(degreesToRad(angle));
}

// ================================ Colision function ================================

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

myTriangle getWorldTriangle(myTriangle* triangle, Float2* pos)
{
    myTriangle world;

    for (int i = 0; i < 3; i++)
    {
        world.vertex[i].x = pos->x + triangle->vertex[i].x;
        world.vertex[i].y = pos->y + triangle->vertex[i].y;
    }

    return world;
}

bool triangleSATColision(myTriangle* triangle1, Float2* pos1, myTriangle* triangle2, Float2* pos2)
{
    Float2 axisToTest;

    myTriangle world1 = getWorldTriangle(triangle1, pos1);
    myTriangle world2 = getWorldTriangle(triangle1, pos2);
    
    for(int i = 0; i < 6; i++)
    {
        //Axis to test are Normal vector of the edges
        if (i < 3) axisToTest = (Float2){-(world1.vertex[(i+1) % 3].y - world1.vertex[i%3].y), (world1.vertex[(i+1) % 3].x - world1.vertex[i%3].x)}; // For triangle 1
        else axisToTest = (Float2){-(world2.vertex[(i+1) % 3].y - world2.vertex[i%3].y), (world2.vertex[(i+1) % 3].x - world2.vertex[i%3].x)}; // For triangle 2

        Float2 axisTemp = axisToTest;

        axisToTest.x = axisTemp.x/sqrtf(axisTemp.x*axisTemp.x + axisTemp.y*axisTemp.y);
        axisToTest.y = axisTemp.y/sqrtf(axisTemp.x*axisTemp.x + axisTemp.y*axisTemp.y);

        Float2 projection1 = triangleProjectionOnAxis(&world1, &axisToTest, pos1); //x is min, y is max
        Float2 projection2 = triangleProjectionOnAxis(&world2, &axisToTest, pos2);

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
            if (triangleSATColision(&polygon1->triangle[i], &polygon1->center, &polygon2->triangle[j], &polygon2->center))
                return true;
        }
    }
    return false;
}

bool isCollisionAABB(AABB box1,AABB box2)
{
    if ((box2.pos.x >= box1.pos.x + box1.width)
    || (box2.pos.x + box2.width <= box1.pos.x)
    || (box2.pos.y >= box1.pos.y + box1.height)
    || (box2.pos.y + box2.height <= box1.pos.y)) 
        return false;
    else 
        return true;
}

bool isPolygonColision(Polygon* polygon1, Polygon* polygon2)
{
    if (!isCollisionAABB(polygon1->colisionBoxAABB, polygon2->colisionBoxAABB))
         return false;

    if (!isColisionSAT(polygon1, polygon2))
        return false;

    return true;
}