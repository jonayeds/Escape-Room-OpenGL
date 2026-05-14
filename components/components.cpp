#include "components.h"

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "../draw/shapes.h"
#include "../globals/globals.h"

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


void door(){
    glPushMatrix();
    glColor3f(0.516, 0.367, 0.254);
    glTranslatef(0.25,0.5,-6.75);
    glTranslatef(2,0,0);
    glRotatef(doorAngle, 0, 1, 0); 
    glTranslatef(-2,0,0);
    glScalef(4, 6, 0.3 );
    Quads(-0.5,-0.5,-0.5);

    glPopMatrix();
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

