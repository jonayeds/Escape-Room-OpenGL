// #include<windows.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>
#include <iostream>
#include <math.h>
#include "draw/shapes.h"
#include "globals/globals.h"
#include "components/components.h"

using namespace std;


void mouseMove(int x, int y) {
    if (x > windowWidth  || y > windowHeight || x < 0 || y < 0) {
        return; 
    }

    if (lastMouseX == -1 || lastMouseY == -1) {
        lastMouseX = x;
        lastMouseY = y;
        return;
    }
    float dx = x - lastMouseX;
    float dy = lastMouseY - y;

    lastMouseX = x;
    lastMouseY = y;

    yaw = yaw + (dx * sensitivity);
    pitch = pitch + (dy * sensitivity);

    if (pitch > 89.0f) pitch = 89.0f;
    if (pitch < -89.0f) pitch = -89.0f;

    float radYaw = yaw * (3.14159f / 180.0f);
    float radPitch = pitch * (3.14159f / 180.0f);

    lookDirX = cos(radYaw) * cos(radPitch);
    lookDirY = sin(radPitch);
    lookDirZ = sin(radYaw) * cos(radPitch);

    int padding = 50;
    if (x < padding || x > windowWidth - padding || y < padding || y > windowHeight - padding) {
        int centerX = windowWidth / 2;
        int centerY = windowHeight / 2;
        
        lastMouseX = centerX;
        lastMouseY = centerY;

        glutWarpPointer(centerX, centerY);
    }
}

static void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // In your display() function:
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Calculate where the camera is looking by adding the direction to the position
    float targetX = posX + lookDirX;
    float targetY = posY + lookDirY;
    float targetZ = posZ + lookDirZ;

    // Apply the camera
    gluLookAt(posX, posY, posZ,          
              targetX, targetY, targetZ, 
              0.0f, 1.0f, 0.0f);         

    // glTranslatef(posX, posY, posZ);
    // glTranslatef(0, 0, 13);

    glRotated(degreeX, 1.0, 0.0, 0.0);
    glRotated(degreeY, 0.0, 1.0, 0.0);
    glRotated(degreeZ, 0.0, 0.0, 1.0);
    glScalef(scale, scale, scale);

    Room();

    glutSwapBuffers();
}

static void reshape(int width, int height)
{
    if (height == 0)
    {
        height = 1;
    }

    windowWidth = width;
    windowHeight = height;
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, static_cast<double>(width) / height, 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

static void key(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 27:
    case 'q':
        exit(0);
        break;

    case 'a':
        degreeX += 2.5;
        break;

    case 'b':
        degreeX -= 2.5;
        break;

    case 'c':
        degreeY += 2.5;
        break;

    case 'd':
        degreeY -= 2.5;
        break;

    case 'e':
        degreeZ += 2.5;
        break;

    case 'f':
        degreeZ -= 2.5;
        break;

    case 'm':
        if (scale < 2.0)
        {
            scale += 0.05;
        }
        break;
    case 'n':
        if (scale > 0.1)
        {
            scale -= 0.05;
        }
    }
    glutPostRedisplay();
}

void specialKey(int key, int x, int y)
{
    float speed = 0.5f;

    float radYaw = yaw * (3.14159f / 180.0f);

    float forwardX = cos(radYaw);
    float forwardZ = sin(radYaw);

    float rightX = cos(radYaw + (3.14159f / 2.0f));
    float rightZ = sin(radYaw + (3.14159f / 2.0f));

    switch (key)
    {
    case GLUT_KEY_UP: // Walk Forward
        posX += forwardX * speed;
        posZ += forwardZ * speed;
        break;

    case GLUT_KEY_DOWN: // Walk Backward
        posX -= forwardX * speed;
        posZ -= forwardZ * speed;
        break;

    case GLUT_KEY_LEFT: // Strafe Left
        posX -= rightX * speed;
        posZ -= rightZ * speed;
        break;

    case GLUT_KEY_RIGHT: // Strafe Right
        posX += rightX * speed;
        posZ += rightZ * speed;
        break;
    }
}


void timer(int value) {
    glutPostRedisplay();           // 1. Redraw the screen
    glutTimerFunc(16, timer, 0);   // 2. Wait 16ms, then run this function again
}

int main(int argc, char *argv[])
{

    cout << "------------- Keyboard Input -------------" << endl;
    cout << "a: Rotate X-axis +2.5 degree" << endl;
    cout << "b: Rotate X-axis -2.5 degree" << endl;
    cout << "c: Rotate Y-axis +2.5 degree" << endl;
    cout << "d: Rotate Y-axis -2.5 degree" << endl;
    cout << "e: Rotate Z-axis +2.5 degree" << endl;
    cout << "f: Rotate Z-axis -2.5 degree" << endl;
    cout << "m: Scale up +0.05" << endl;
    cout << "n: Scale down -0.05" << endl;
    cout << "up/down arrow: Move up/down" << endl;
    cout << "left/right arrow: Move left/right" << endl;
    cout << "shift + up/down arrow: Move forward/backward" << endl;
    cout << "----------------------------------------" << endl;

    glutInit(&argc, argv);
    glutInitWindowSize(1080, 720);
    glutInitWindowPosition(10, 10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutCreateWindow("2023000000202");

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(key);
    glutSpecialFunc(specialKey);
    glutTimerFunc(0, timer, 0);

    glClearColor(0, 0, 0, 1);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glShadeModel(GL_SMOOTH);

    glutPassiveMotionFunc(mouseMove);
    glutSetCursor(GLUT_CURSOR_NONE);

    glutMainLoop();

    return EXIT_SUCCESS;
}
