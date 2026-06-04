#include "utils.h"
#include "../globals/globals.h"

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <iostream>
using namespace std;


bool detectInteraction(float minX, float maxX, float minY, float maxY, float minZ, float maxZ)
{
    float maxReach = 3.5f;
    float stepSize = 0.1f;

    for (float t = 0.0f; t < maxReach; t += stepSize)
    {
        float checkX = posX + (lookDirX * t);
        float checkY = posY + (lookDirY * t);
        float checkZ = posZ + (lookDirZ * t);

        if (checkX >= minX && checkX <= maxX &&
            checkY >= minY && checkY <= maxY &&
            checkZ >= minZ && checkZ <= maxZ)
        {
            return true;
        }
    }
    return false;
}



// TEST FUNCTIONS
void drawDebugHitbox(ComponentPosition pos)
{
    glDisable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);

    glColor3f(1.0f, 1.0f, 0.0f); // Yellow color

    // Calculate the center and size of the box
    float centerX = (pos.minX + pos.maxX) / 2.0f;
    float centerY = (pos.minY + pos.maxY) / 2.0f;
    float centerZ = (pos.minZ + pos.maxZ) / 2.0f;

    float width = pos.maxX - pos.minX;
    float height = pos.maxY - pos.minY;
    float depth = pos.maxZ - pos.minZ;

    glPushMatrix();
    glTranslatef(centerX, centerY, centerZ);
    glScalef(width, height, depth);
    glutWireCube(1.0); // Draws the wireframe!
    glPopMatrix();

    glEnable(GL_LIGHTING);
}


void drawDebugLaser()
{
    glDisable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);

    glColor3f(1.0f, 0.0f, 1.0f);

    glBegin(GL_LINES);
    glVertex3f(posX + lookDirX - 0.2, posY + lookDirY - 0.2, posZ + lookDirZ);
    glVertex3f(posX + (lookDirX * 1), posY + (lookDirY * 1), posZ + (lookDirZ * 1));
    glEnd();

    glEnable(GL_LIGHTING);
}
