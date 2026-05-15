#include "components.h"

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "../draw/shapes.h"
#include "../globals/globals.h"
#include "../utils/utils.h"
#include <iostream>
using namespace std;

void light()
{
    GLfloat light_position_1[] = {-4.0f, 2.25f, -4.0f, 1.0f};
    glLightfv(GL_LIGHT0, GL_POSITION, light_position_1);

    glPushMatrix();
    glDisable(GL_LIGHTING);
    glColor3d(1, 1, 1);
    glTranslatef(-4.0f, 2.25f, -4.0f);
    glutSolidSphere(0.5, 64, 64);
    glEnable(GL_LIGHTING);
    glPopMatrix();
}



void drawText(float x, float y, float z, float size, const char *text)
{
    glPushMatrix();
    glDisable(GL_LIGHTING);
    glTranslatef(x, y, z);
    glScalef(size, size, size);
    glLineWidth(2);
    while (*text)
    {
        glutStrokeCharacter(GLUT_STROKE_ROMAN, *text);
        text++;
    }
    glLineWidth(1.0f);
    glEnable(GL_LIGHTING);
    glPopMatrix();
}

void doorLock()
{
    glPushMatrix();
    glColor3f(0.8, 0.8, 0.8);
    glScalef(1, 1, 0.3);
    Quads(-0.5, -0.5, 0);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.3, 0.3, 0.3);
    glTranslatef(0, 0.15, 0.15);
    glScalef(0.4, 0.2, 0.4);
    Quads(-0.5, -0.5, -0.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.9, 0.9, 0.9);
    glTranslatef(0, -0.25, 0.15);
    glScalef(0.8, 0.4, 0.4);
    Quads(-0.5, -0.5, -0.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0, 0, 0);
    drawText(-0.25, 0.3, 0.35, 0.0007, "Whats Next?");
    glPopMatrix();

    glTranslatef(-0.35, -0.2, 0.36);
    glPushMatrix();
    glColor3f(0, 0, 0);
    drawText(0.0, 0.0, 0.0, 0.0008, "1");
    drawText(0.15, 0.0, 0.0, 0.0008, "2");
    drawText(0.3, 0.0, 0.0, 0.0008, "3");
    drawText(0.45, 0.0, 0.0, 0.0008, "4");
    drawText(0.6, 0.0, 0.0, 0.0008, "5");
    drawText(0.0, -0.2, 0.0, 0.0008, "6");
    drawText(0.15, -0.2, 0.0, 0.0008, "7");
    drawText(0.3, -0.2, 0.0, 0.0008, "8");
    drawText(0.45, -0.2, 0.0, 0.0008, "9");
    drawText(0.6, -0.2, 0.0, 0.0008, "0");
    glPopMatrix();
}

void door()
{
    glPushMatrix();
    glColor3f(0.516, 0.367, 0.254);
    glTranslatef(0.25, 0.5, -6.75);
    glTranslatef(2, 0, 0);
    glRotatef(doorAngle, 0, 1, 0);
    glTranslatef(-2, 0, 0);

    glPushMatrix();
    glScalef(4, 6, 0.3);
    Quads(-0.5, -0.5, -0.5);
    glPopMatrix();

    doorLock();

    glPopMatrix();
    // Quads(-0.5,-0.5,-6.5);
}

void Room()
{
    light();

    // floor
    glPushMatrix();
    glTranslatef(0, -3.5, 0);
    DrawGrid_XZ(15.0f, 15.0f);
    glPopMatrix();

    // pillers
    glPushMatrix();
    glTranslatef(7, 0, 7);
    glScalef(1, 7, 1);
    Quads(-0.5, -0.5, -0.5);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(7, 0, -7);
    glScalef(1, 7, 1);
    Quads(-0.5, -0.5, -0.5);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-7, 0, -7);
    glScalef(1, 7, 1);
    Quads(-0.5, -0.5, -0.5);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-7, 0, 7);
    glScalef(1, 7, 1);
    Quads(-0.5, -0.5, -0.5);
    glPopMatrix();

    // walls

    // front side
    glPushMatrix();
    glTranslatef(-4, 0, 6.5);
    DrawGrid_XY(6, 7);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(4, 0, 6.5);
    DrawGrid_XY(6, 7);
    glPopMatrix();

    // back side
    glPushMatrix();
    glTranslatef(4.5, 0, -7.5);
    DrawGrid_XY(4.5, 7);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-4.5, 0, -7.5);
    DrawGrid_XY(4.5, 7);
    glPopMatrix();

    // left side
    glPushMatrix();
    glTranslatef(-7.5, 0, -4);
    DrawGrid_YZ(7, 6);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-7.5, 0, 4);
    DrawGrid_YZ(7, 6);
    glPopMatrix();

    // right side
    glPushMatrix();
    glTranslatef(6.5, 0, -4);
    DrawGrid_YZ(7, 6);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(6.5, 0, 4);
    DrawGrid_YZ(7, 6);
    glPopMatrix();

    // wall fillers

    // front
    glPushMatrix();
    glTranslatef(0, -2.25, 7);
    glScalef(2, 2, 1);
    Quads(-0.5, -0.5, -0.5);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 2.5, 7);
    glScalef(2, 2, 1);
    Quads(-0.5, -0.5, -0.5);
    glPopMatrix();

    // left side
    glPushMatrix();
    glTranslatef(7, 2.5, 0);
    glScalef(1, 2, 2);
    Quads(-0.5, -0.5, -0.5);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(7, -2.25, 0);
    glScalef(1, 2, 2);
    Quads(-0.5, -0.5, -0.5);
    glPopMatrix();

    // right side
    glPushMatrix();
    glTranslatef(-7, 2.5, 0);
    glScalef(1, 2, 2);
    Quads(-0.5, -0.5, -0.5);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-7, -2.25, 0);
    glScalef(1, 2, 2);
    Quads(-0.5, -0.5, -0.5);
    glPopMatrix();

    // roof
    glPushMatrix();
    glTranslatef(0, 3.5, 0);
    DrawGrid_XZ(15.0f, 15.0f);
    glPopMatrix();

    door();
}
