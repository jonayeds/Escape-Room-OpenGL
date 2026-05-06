// #include<windows.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>
#include <iostream>
#include <math.h>

using namespace std;

float degreeX = 0;
float degreeY = 0;
float degreeZ = 0;
float scale = 0.5;
float posX = 0.0f;
float posZ = -10.0f;
float posY = 0.0f;

// The direction the camera is looking
float lookDirX = 0.0f;
float lookDirY = 0.0f;
float lookDirZ = 1.0f;

float yaw = -90.0f; 
float pitch = 0.0f;
float sensitivity = 0.1f;
int windowWidth = 1080;
int windowHeight = 720;




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


int mouseX = 0;
int mouseY = 0;
int lastMouseX = -1;
int lastMouseY = -1;     

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
        
        // CRITICAL: We must update the lastMouse variables to the center,
        // otherwise the next frame will think you jerked the mouse 400 pixels!
        lastMouseX = centerX;
        lastMouseY = centerY;
        
        // Execute the heavy Mac OS system call
        glutWarpPointer(centerX, centerY);
    }
}

static void light()
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

static void Room()
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

    // rojof
    glPushMatrix();
    glTranslatef(0, 3.5, 0);
    DrawGrid_XZ(15.0f, 15.0f);
    glPopMatrix();
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
    const int mods = glutGetModifiers();
    const bool shift = mods == GLUT_ACTIVE_SHIFT;
    switch (key)
    {
    case GLUT_KEY_LEFT:
        posX += 0.5f;
        break;
    case GLUT_KEY_RIGHT:
        posX -= 0.5f;
        break;
    case GLUT_KEY_UP:
        if (shift)
        {
            posY += 0.5f;
        }
        else
        {
            posZ += 0.5f;
        }
        break;
    case GLUT_KEY_DOWN:
        if (shift)
        {
            posY -= 0.5f;
        }
        else
        {
            posZ -= 0.5f;
        }
        break;
    }
    glutPostRedisplay();
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
