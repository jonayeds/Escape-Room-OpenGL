// #include<windows.h>
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

    GLfloat light_diffuse_2[]  = {0.5f, 0.5f, 0.5f, 0.1f};
    glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse_2);      

    glPushMatrix();
    glTranslatef(-4.0f, 2.25f, -4.0f);
    glPushMatrix();
    glTranslatef(0,1,0);
    glScalef(0.2,1,0.2);
    glColor3f(0.2, 0.2, 0.2);
    Quads(-0.5f, -0.5f, -0.5f);
    glPopMatrix();
    glDisable(GL_LIGHTING);
    if(isLightOn){
        glColor3f(1, 1, 1);
    }else{
        glColor3f(0.2, 0.2, 0.2);
    }
    glutSolidSphere(0.5, 64, 64);
    glEnable(GL_LIGHTING);
    glPopMatrix();
}

void drawText(float x, float y, float z, float size, const char *text, float lineWidth = 2.0f)
{
    glPushMatrix();
    glDisable(GL_LIGHTING);
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glTranslatef(x, y, z);
    glScalef(size, size, size);
    glLineWidth(lineWidth);
    int passes = 3 ; 

    for (int p = 0; p < passes; p++)
    {
        glPushMatrix();
        const char *c = text;
        while (*c)
        {
            glutStrokeCharacter(GLUT_STROKE_ROMAN, *c);
            c++;
        }
        
        glPopMatrix();
    }
    glLineWidth(1.0f);
    glDisable(GL_BLEND);
    glDisable(GL_LINE_SMOOTH);
    glEnable(GL_LIGHTING);
    glPopMatrix();
}


void dodecahedron(){
    glBindTexture(GL_TEXTURE_2D, woodTex);
    glPushMatrix();
    glTranslatef(-3.5, -2.0, 3);
    glScalef(0.4, 0.4, 0.4);

    glColor3f(0.5f, 0.5f, 0.5f);

    glutSolidDodecahedron();

    glPopMatrix();
}

void wallMap(){
    glPushMatrix();
    glTranslatef(-4, 0.5, 6.5); 
    

     glPushMatrix();
    glColor3f(1, 1, 1);
    glTranslatef(0.0, 0.0, 0.1); 
    glDisable(GL_TEXTURE_2D);
    glScalef(4, 4, 0.1f);
    Quads(-0.5f, -0.5f, -0.5f);
    glEnable(GL_TEXTURE_2D);    
    glPopMatrix();
    // map
    glPushMatrix();
    glTranslatef(0.0, 0.0, -0.01); 
    glScalef(4, 4, 0.1f);
    glBindTexture(GL_TEXTURE_2D, wallMapTex);
    glColor3f(0.45, 0.45, 0.45);
    Quads(-0.5f, -0.5f, -0.5f);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0, 0, 0); 
    glTranslatef(-0.0, 0.0, 0.2);
    drawText(0, 0.0, 0.0, 0.0009, "5"); 
    glPopMatrix();

    glPopMatrix();
}

void wallClock(){
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, metalTex);
    glTranslatef(-6.3f, 0.0f, -2.5f); 
    glRotated(-180, 0, 1, 0);
    glRotatef(-90, 0, 1, 0); 
    glScalef(0.5f, 0.5f, 0.5f);
    glColor3f(0.8, 0.8, 0.8);
    cylinder(1, 0.1);
    glColor3f(1,1,1);
    glDisable(GL_TEXTURE_2D);
    glScalef(0.85f, 0.85f, 0.85f);
    glTranslatef(0,0,0.05);
    cylinder(1, 0.1);
    glEnable(GL_TEXTURE_2D);

    glPushMatrix(); 
    glRotatef(-clockRotation, 0, 0, 1);
    glTranslatef(0,0.4,0.1);
    glScalef(0.025f, 0.8f, 0.025f); 
    Quads(-0.5,-0.5,-0.5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(1, 0, 0);   
    glRotatef((float)-clockRotation/12, 0, 0, 1); 
    glTranslatef(0.3,0.0,0.1);
    glRotatef(90, 0, 0, 1);
    glScalef(0.025f, 0.6f, 0.025f); 
    Quads(-0.5, -0.5,-0.5); 
    glPopMatrix();

    glColor3f(0.2, 0.2, 0.2);
    drawText(0.7f, -0.0, 0.1f, 0.0015f, "3", 3.0f);
    drawText(-0.9f, -0.0, 0.1f, 0.0015f, "9", 3.0f);
    drawText(-0.1f, 0.7, 0.1f, 0.0015f, "12", 3.0f);
    drawText(-0.1f, -0.85, 0.1f, 0.0015f, "6", 3.0f);
    glPopMatrix();          
}

void book2(){
    glBindTexture(GL_TEXTURE_2D, bookPagesTex);
    glPushMatrix();
    glTranslatef(6, -0.4, 4.5);
    if(selectedComponent == -1){
        glRotatef(-120, 0, 0, 1);
    }
        glPushMatrix(); 
        glTranslatef(0.3, 0.4935, 1.2);
        glRotatef(-90, 1, 0, 0); 
        glColor3f(0, 0, 0);
        drawText(0.1, 1.15, -0.4, 0.0008, "7", 3.0f);
        glPopMatrix();  
    glScalef(0.5, 0.5, 0.5);
    glPushMatrix();
    glTranslatef(-0.1,0.015,0);
    glColor3f((float)144/255, (float)125/255, (float)85/255);
    cylinder(0.165, 1);
    glPopMatrix();
    glScalef(1, 0.3, 1.01); 
    glTranslatef(-0.1,0,0);
    glColor3f((float)204/255, (float)186/255, (float)142/255);

    Quads(0,-0.5,-0.5);
    glScalef(1.1,0.1,1.01);
    glBindTexture(GL_TEXTURE_2D, book2CoverTex);
    Quads(0,5,-0.5);
    Quads(0,-5.005,-0.5);


    glPopMatrix();
}

void teapot(float size )
{
    glPushMatrix();
    glTranslatef(3.8f, -0.65f, 4.4f);
    glScalef(0.2, 0.2, 0.2);
    glRotatef(180, 0,1,0);

    glDisable(GL_CULL_FACE);
    glColor3f(1.0f, 1.0f, 1.0f);
    glBindTexture(GL_TEXTURE_2D, metalTex);

    glutSolidTeapot(size);

    glPopMatrix();
}

void wall_frame2 (){
    glPushMatrix();
    glTranslatef(5, 0.5, 6.5); 
    
    // Frame
    glBindTexture(GL_TEXTURE_2D, woodTex);
    glColor3f(0.8, 0.8, 0.8);
    glPushMatrix();
    glScalef(1, 1, 0.1);
    Quads(-0.5f, -0.5f, -0.5f);
    glPopMatrix();
    
    // Painting
    glPushMatrix();
    glColor3f(1, 1, 1);
    glTranslatef(0.0, 0.0, -0.01); 
    glScalef(0.9f, 0.9f, 0.1f);
    glBindTexture(GL_TEXTURE_2D, painting2Tex);
    Quads(-0.5f, -0.5f, -0.5f);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0, 0, 0); 
    glTranslatef(-0.0, 0.0, 0.1);
    drawText(0, 0.0, 0.0, 0.0009, "5"); 
    glPopMatrix();

    glPopMatrix();
}

void wall_frame (){
    glPushMatrix();
    glTranslatef(6.5, 0.0, -2.5); // Position on the right wall
    
    // Frame
    glBindTexture(GL_TEXTURE_2D, woodTex);
    glColor3f(0.8, 0.8, 0.8);
    glPushMatrix();
    glScalef(0.1, 1, 1);
    Quads(-0.5f, -0.5f, -0.5f);
    glPopMatrix();
    
    // Painting
    glPushMatrix();
    glColor3f(1, 1, 1);
    glTranslatef(-0.01, 0.0, 0); 
    glScalef(0.1f, 0.9f, 0.9f);
    glBindTexture(GL_TEXTURE_2D, painting1Tex);
    Quads(-0.5f, -0.5f, -0.5f);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0, 0, 0); 
    glTranslatef(0.1, 0.0, 0.4);
    glRotatef(90, 0, 1, 0);
    drawText(0, 0.0, 0.0, 0.0006, "Maximum combination",1); 
    drawText(0, -0.1, 0.0, 0.0006, "is the code", 1.0); 
    glPopMatrix();

    glPopMatrix();
}

void book(){
    glBindTexture(GL_TEXTURE_2D, bookPagesTex);
    glPushMatrix();
    glTranslatef(4.5, -0.7, 4.5);
        glPushMatrix(); 
        glTranslatef(0.3, 0.4935, 1.2);
        glRotatef(-90, 1, 0, 0); 
        glColor3f(0.5, 0.5, 0.5);
        drawText(0, 1.2, -0.4, 0.001, "2", 3.0f);
        glPopMatrix();  
    glScalef(0.5, 0.5, 0.5);
    glPushMatrix();
    glTranslatef(-0.1,0.015,0);
    glColor3f(0.796,0.76,0.745);
    cylinder(0.165, 1);
    glPopMatrix();
    glScalef(1, 0.3, 1.01); 
    glTranslatef(-0.1,0,0);
    glColor3f(0.9, 0.9, 0.9);
    Quads(0,-0.5,-0.5);
    glScalef(1.1,0.1,1.01);
    glBindTexture(GL_TEXTURE_2D, bookCoverTex);
    Quads(0,5,-0.5);
    Quads(0,-5.001,-0.5);


    glPopMatrix();
    
}

void chair(){
    glBindTexture(GL_TEXTURE_2D, woodTex);
    glColor3f(0.8, 0.8, 0.8);
    glPushMatrix();
    glTranslatef(4.2, -1.7, 3.0);     

    // Seat
    glPushMatrix();
    glScalef(1.0, 0.2, 1.0);
    Quads(0,0,0);
    glPopMatrix();

    // Backrest
    glPushMatrix();
    glTranslatef(0, 0.2, 0);
    glScalef(1.0, 1.0, 0.1);
    Quads(0,0,0);
    glPopMatrix();

    // Legs
    glPushMatrix();
    glTranslatef(0, -0.8, 0);
    glScalef(0.1, 0.8, 0.1);
    Quads(0,0,0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.9, -0.8, 0);
    glScalef(0.1, 0.8, 0.1);
    Quads(0,0,0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, -0.8, 0.9);
    glScalef(0.1, 0.8, 0.1);
    Quads(0,0,0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.9, -0.8, 0.9);
    glScalef(0.1, 0.8, 0.1);
    Quads(0,0,0);
    glPopMatrix();

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
    chair();
    book();
    book2();
    wall_frame();   
    wall_frame2();  
    teapot(); 
    wallClock();
    wallMap();
    dodecahedron();
    glDisable(GL_TEXTURE_2D);   


    
}
