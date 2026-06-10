// #include<windows.h>
#include "shapes.h"
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

    // 1. FRONT FACE (+Z)
    glNormal3f(0.0f, 0.0f, 1.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(x, y, max_z);         // Bottom-Left
    glTexCoord2f(1.0f, 0.0f); glVertex3f(max_x, y, max_z);     // Bottom-Right
    glTexCoord2f(1.0f, 1.0f); glVertex3f(max_x, max_y, max_z); // Top-Right
    glTexCoord2f(0.0f, 1.0f); glVertex3f(x, max_y, max_z);     // Top-Left

    // 2. BACK FACE (-Z)
    // Note: Viewed from the back, max_x is the LEFT edge, x is the RIGHT edge.
    glNormal3f(0.0f, 0.0f, -1.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(max_x, y, z);         // Bottom-Left
    glTexCoord2f(1.0f, 0.0f); glVertex3f(x, y, z);             // Bottom-Right
    glTexCoord2f(1.0f, 1.0f); glVertex3f(x, max_y, z);         // Top-Right
    glTexCoord2f(0.0f, 1.0f); glVertex3f(max_x, max_y, z);     // Top-Left

    // 3. LEFT FACE (-X)
    // Note: Viewed from the left, z is the LEFT edge, max_z is the RIGHT edge.
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(x, y, z);             // Bottom-Left
    glTexCoord2f(1.0f, 0.0f); glVertex3f(x, y, max_z);         // Bottom-Right
    glTexCoord2f(1.0f, 1.0f); glVertex3f(x, max_y, max_z);     // Top-Right
    glTexCoord2f(0.0f, 1.0f); glVertex3f(x, max_y, z);         // Top-Left

    // 4. RIGHT FACE (+X)
    // Note: Viewed from the right, max_z is the LEFT edge, z is the RIGHT edge.
    glNormal3f(1.0f, 0.0f, 0.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(max_x, y, max_z);     // Bottom-Left
    glTexCoord2f(1.0f, 0.0f); glVertex3f(max_x, y, z);         // Bottom-Right
    glTexCoord2f(1.0f, 1.0f); glVertex3f(max_x, max_y, z);     // Top-Right
    glTexCoord2f(0.0f, 1.0f); glVertex3f(max_x, max_y, max_z); // Top-Left

    // 5. TOP FACE (+Y)
    glNormal3f(0.0f, 1.0f, 0.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(x, max_y, max_z);     // Bottom-Left
    glTexCoord2f(1.0f, 0.0f); glVertex3f(max_x, max_y, max_z); // Bottom-Right
    glTexCoord2f(1.0f, 1.0f); glVertex3f(max_x, max_y, z);     // Top-Right
    glTexCoord2f(0.0f, 1.0f); glVertex3f(x, max_y, z);         // Top-Left

    // 6. BOTTOM FACE (-Y)
    glNormal3f(0.0f, -1.0f, 0.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(x, y, z);             // Bottom-Left
    glTexCoord2f(1.0f, 0.0f); glVertex3f(max_x, y, z);         // Bottom-Right
    glTexCoord2f(1.0f, 1.0f); glVertex3f(max_x, y, max_z);     // Top-Right
    glTexCoord2f(0.0f, 1.0f); glVertex3f(x, y, max_z);         // Top-Left

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

void circle(float z, float radius, bool is_top)
{
    glBegin(GL_POLYGON);
    glNormal3f(0, 0, is_top ? -1 : 1);

    if (is_top)
    {
        for (int i = 359; i >= 0; i--)
        {
            float theta = 2 * 3.1416f * i / 360;
            float x = cos(theta);
            float y = sin(theta);
            glTexCoord2f(x * 0.5f + 0.5f, y * 0.5f + 0.5f   );
            glVertex3f(x * radius, y * radius, z);
        }
    }
    else
    {
        for (int i = 0; i < 360; i++)
        {
            float theta = 2 * 3.1416f * i / 360;
            float x = cos(theta);
            float y = sin(theta);
            glTexCoord2f(x * 0.5f + 0.5f, y * 0.5f + 0.5f   );
            glVertex3f(x * radius, y * radius, z);
        }
    }

    glEnd();
}


void cylinder(float radius, float height)
{
    glPushMatrix();

    float half_height = height * 0.5f;
    circle(-half_height, radius, true);
    circle(half_height, radius, false);
    glBegin(GL_QUAD_STRIP);
    for (int i = 0; i <= 360; i++)
    {
        float theta = 2 * 3.1416f * i / 360;
        float x = cos(theta);
        float y = sin(theta);
        glNormal3f(x, y, 0);
        glTexCoord2f(i / 360.0f, 1.0f);
        glVertex3f(x * radius, y * radius, half_height);
        glTexCoord2f(i / 360.0f , 0);
        glVertex3f(x * radius, y * radius, -half_height);
    }
    glEnd();
    glPopMatrix();
}
