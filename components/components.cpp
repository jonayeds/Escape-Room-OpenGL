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
    GLfloat light_ambient_1[] = {0.2f, 0.2f, 0.2f, 0.5f};
    GLfloat light_diffuse_1[]  = {1.0f, 1.0f, 1.0f, 1.0f};
    glLightfv(GL_LIGHT0, GL_POSITION, light_position_1);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient_1);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse_1);      

    glPushMatrix();
    glDisable(GL_LIGHTING);
    glColor3d(1, 1, 1);
    glTranslatef(-4.0f, 2.25f, -4.0f);
    glutSolidSphere(0.5, 64, 64);
    glEnable(GL_LIGHTING);
    glPopMatrix();
}


void table(){
    glBindTexture(GL_TEXTURE_2D, woodTex);
    glColor3f(0.8, 0.8, 0.8);
    glPushMatrix();
    glTranslatef(3.5, -1, 4);
    glScalef(0.6,0.5,0.5);
    glPushMatrix();
    glScalef(4,0.25,3);
    Quads(0,0,0);
    glPopMatrix();
    
    glTranslatef(0,-3,0);
    glPushMatrix();
    glScalef(0.25,3,0.25);
    Quads(0,0,0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(3.75,0,0);
    glScalef(0.25,3,0.25);
    Quads(0,0,0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(3.75,0,2.75);
    glScalef(0.25,3,0.25);
    Quads(0,0,0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,0,2.75);
    glScalef(0.25,3,0.25);
    Quads(0,0,0);
    glPopMatrix();



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
    glBindTexture(GL_TEXTURE_2D, metalTex);
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
    glDisable(GL_TEXTURE_2D);
    glPushMatrix();
    glColor3f(0.9, 0.9, 0.9);
    glTranslatef(0, -0.25, 0.15);
    glScalef(0.8, 0.4, 0.4);
    Quads(-0.5, -0.5, -0.5);
    glPopMatrix();
    
    glPushMatrix();
    glColor3f(0, 0, 0);
    drawText(-0.25, 0.3, 0.35, 0.0007, "Next Number");
    glPopMatrix();
    
    glPushMatrix();
    glColor3f(1, 1, 1);
    drawText(-0.15, 0.1, 0.4, 0.0007, inputCode.c_str());
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
    glEnable(GL_TEXTURE_2D);
}

void door()
{
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, doorTex);  
    glColor3f(1,1,1);
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
}

void Room()
{
    light();

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, concreteTex);
    // floor
    glPushMatrix();
    glTranslatef(0, -3.5, 0);
    glScalef(4, 1, 4);
    glColor3f(0.7,0.7,0.7);
    DrawGrid_XZ(4.0f, 4.0f);
    
    
    glPopMatrix();
    glBindTexture(GL_TEXTURE_2D, brickTex);
    glColor3f(0.6,0.6,0.6);

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
    glScalef(3,3,1);
    DrawGrid_XY(2, 2.33);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(4, 0, 6.5);
    glScalef(3,3,1);
    DrawGrid_XY(2, 2.33);
    glPopMatrix();

    // back side
    glPushMatrix();
    glTranslatef(4.5, 0, -7.5);
    glScalef(3,3,1);
    DrawGrid_XY(2, 2.33);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-4.5, 0, -7.5);
    glScalef(3,3,1);
    DrawGrid_XY(2, 2.33);
    glPopMatrix();

    // left side
    glPushMatrix();
    glTranslatef(-7.5, 0, -4);
    glScalef(1,3,3);
    DrawGrid_YZ(2.33, 2);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-7.5, 0, 4);
    glScalef(1,3,3);
    DrawGrid_YZ(2.33, 2);
    glPopMatrix();

    // right side
    glPushMatrix();
    glTranslatef(6.5, 0, -4);
    glScalef(1,3,3);
    DrawGrid_YZ(2.33, 2);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(6.5, 0, 4);
    glScalef(1,3,3);
    DrawGrid_YZ(2.33, 2);
    glPopMatrix();

    // wall fillers

    // front
    glPushMatrix();
    glTranslatef(0, -2.25, 6.5);
    glScalef(2, 3, 1);
    DrawGrid_XY(1,1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 2.5, 6.5);
    glScalef(2, 3, 1);
    DrawGrid_XY(1,1);
    glPopMatrix();

    // left side
    glPushMatrix();
    glTranslatef(6.5, 2.5, 0);
    glScalef(1, 3, 2);
    DrawGrid_YZ(1,1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(6.5, -2.25, 0);
    glScalef(1, 3, 2);
    DrawGrid_YZ(1,1);
    glPopMatrix();

    // right side
    glPushMatrix();
    glTranslatef(-7.5, 2.5, 0);
    glScalef(1, 3, 2);
    DrawGrid_YZ(1,1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-7.5, -2.25, 0);
    glScalef(1, 3, 2);
    DrawGrid_YZ(1,1);
    glPopMatrix();

    // roof
    glBindTexture(GL_TEXTURE_2D, concreteTex);
    glPushMatrix();
    glTranslatef(0, 3.5, 0);
    glScalef(4, 1, 4);
    DrawGrid_XZ(4.0f, 4.0f);
    glPopMatrix();
    
    door();
    table();
    glDisable(GL_TEXTURE_2D);   
}
