#include "shapes.h"
// #include<windows.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>
#include <iostream>
#include <math.h>

void Quads(float x, float y, float z)
{
    glBegin(GL_QUADS);
    float max_x = x + 1.0f;
    float max_y = y + 1.0f;
    float max_z = z + 1.0f;

    // glColor3f(1.0f, 1.0f, 1.0f);
    glNormal3f(0.0f, 0.0f, -1.0f);
    glVertex3f(x, max_y, z);
    glVertex3f(max_x, max_y, z);
    glVertex3f(max_x, y, z);
    glVertex3f(x, y, z);

    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(x, max_y, max_z);
    glVertex3f(x, max_y, z);
    glVertex3f(x, y, z);
    glVertex3f(x, y, max_z);

    glNormal3f(0.0f, 0.0f, 1.0f);
    glVertex3f(max_x, max_y, max_z);
    glVertex3f(x, max_y, max_z);
    glVertex3f(x, y, max_z);
    glVertex3f(max_x, y, max_z);

    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(max_x, max_y, z);
    glVertex3f(max_x, max_y, max_z);
    glVertex3f(max_x, y, max_z);
    glVertex3f(max_x, y, z);

    glNormal3f(0.0f, -1.0f, 0.0f);
    glVertex3f(max_x, y, max_z);
    glVertex3f(x, y, max_z);
    glVertex3f(x, y, z);
    glVertex3f(max_x, y, z);

    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(max_x, max_y, z);
    glVertex3f(x, max_y, z);
    glVertex3f(x, max_y, max_z);
    glVertex3f(max_x, max_y, max_z);

    glEnd();
}

void DrawGrid_XZ(float width, float depth)
{
    float startX = -width / 2.0f;
    float startZ = -depth / 2.0f;

    for (int x = 0; x < width; x++)
    {
        for (int z = 0; z < depth; z++)
        {
            float curX = startX + x;
            float curZ = startZ + z;
            Quads(curX, 0, curZ);
        }
    }
}

void DrawGrid_XY(float width, float height)
{
    float startX = -width / 2.0f;
    float startY = -height / 2.0f;

    for (int x = 0; x < width; x++)
    {
        for (int y = 0; y < height; y++)
        {
            float curX = startX + x;
            float curY = startY + y;
            Quads(curX, curY, 0);
        }
    }
}

void DrawGrid_YZ(float height, float depth)
{
    float startY = -height / 2.0f;
    float startZ = -depth / 2.0f;

    for (int y = 0; y < height; y++)
    {
        for (int z = 0; z < depth; z++)
        {
            float curY = startY + y;
            float curZ = startZ + z;
            Quads(0, curY, curZ);
        }
    }
}

