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
#include "utils/utils.h"
#define STB_IMAGE_IMPLEMENTATION
#include "libraries/stb_image.h"

using namespace std;

void pointer()
{
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);

    glColor3f(0.0f, 1.0f, 0.0f);
    glBegin(GL_LINES);
    glVertex2f(-0.1f, 0.0);
    glVertex2f(0.1f, 0.0f);
    glVertex2f(0.0f, -0.1f);
    glVertex2f(0.0f, 0.1f);
    glEnd();

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);

    glPopMatrix();

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
}

void mouseMove(int x, int y)
{
    if (x > windowWidth || y > windowHeight || x < 0 || y < 0)
    {
        return;
    }

    if (lastMouseX == -1 || lastMouseY == -1)
    {
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

    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    float radYaw = yaw * (3.14159f / 180.0f);
    float radPitch = pitch * (3.14159f / 180.0f);

    lookDirX = cos(radYaw) * cos(radPitch);
    lookDirY = sin(radPitch);
    lookDirZ = sin(radYaw) * cos(radPitch);

    // cout << "lookDirX: " << lookDirX << " lookDirY: " << lookDirY << " lookDirZ: " << lookDirZ << endl;
    // cout << "posX: " << posX << " posY: " << posY << " posZ: " << posZ << endl;

    int padding = 50;
    if (x < padding || x > windowWidth - padding || y < padding || y > windowHeight - padding)
    {
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

    if (selectedComponent == -1)
    {
        // ==========================================
        // MODE 1: NORMAL ROOM VIEW
        // ==========================================
        float targetX = posX + lookDirX;
        float targetY = posY + lookDirY;
        float targetZ = posZ + lookDirZ;

        gluLookAt(posX, posY, posZ, targetX, targetY, targetZ, 0.0f, 1.0f, 0.0f);

        // test
        // drawDebugLaser();
        // drawDebugHitbox(bookPosition);

        glPushMatrix();
        Room();
        glPopMatrix();

        pointer();
    }
    else
    {
        // ==========================================
        // MODE 2: INSPECT COMPONENT VIEW
        // ==========================================
        gluLookAt(0.0f, 0.0f, 2.5f,
                  0.0f, 0.0f, 0.0f,
                  0.0f, 1.0f, 0.0f);

        GLfloat light_position[] = {1.0f, 1.0f, 2.0f, 1.0f};
        glLightfv(GL_LIGHT0, GL_POSITION, light_position);

        glRotated(degreeX, 1.0, 0.0, 0.0);
        glRotated(degreeY, 0.0, 1.0, 0.0);
        glRotated(degreeZ, 0.0, 0.0, 1.0);

        if (selectedComponent == doorLockId)
        {
            doorLock();
        }
        else if (selectedComponent == tableId)
        {
            glEnable(GL_TEXTURE_2D);
            glScalef(0.5, 0.5, 0.5);
            glTranslatef(-3.5, 1, -4);
            glTranslatef(-1.25, 0.5, -0.75);
            table();
            glDisable(GL_TEXTURE_2D);
        }
        else if (selectedComponent == bookId){
            glEnable(GL_TEXTURE_2D);
            glScalef(1.5,1.5,1.5);  
            glTranslatef(-4.8, 0.7, -4.5);
            book();
            glDisable(GL_TEXTURE_2D);
        }
    }

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

    case 'x':
        degreeX += 2.5;
        break;

    case 'X':
        degreeX -= 2.5;
        break;

    case 'y':
        degreeY += 2.5;
        break;

    case 'Y':
        degreeY -= 2.5;
        break;

    case 'z':
        degreeZ += 2.5;
        break;

    case 'Z':
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
        break;
    case 'o':
        doorAnimating = true;
        break;
    }

    if (selectedComponent == doorLockId && key >= '0' && key <= '9' && inputCode.size() < doorCode.size())
    {
        inputCode += key;
        if (inputCode == doorCode)
        {
            cout << "Door Unlocked!" << endl;
            selectedComponent = -1;
            doorAnimating = true;
        }
        else if (inputCode.size() == doorCode.size())
        {
            cout << "Wrong Code. Try Again." << endl;
            inputCode = "";
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

    if (posX >= 4.0f)
        posX = 4.0f;
    if (posX <= -4.0f)
        posX = -4.0f;
    if (posZ <= -4.0f)
        posZ = -4.0f;
    if (posZ >= 4.0f)
        posZ = 4.0;
}

void mouseClick(int button, int state, int x, int y)
{

    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        if (selectedComponent != -1)
        {
            selectedComponent = -1;
            degreeX = 0;
            degreeY = 0;
            degreeZ = 0;
            cout << "Returned to room." << endl;
            glutPostRedisplay();
            return;
        }

        if (detectInteraction(doorPosition.minX, doorPosition.maxX, doorPosition.minY, doorPosition.maxY, doorPosition.minZ, doorPosition.maxZ))
        {
            cout << "You clicked the door lock!" << endl;
            selectedComponent = doorLockId;
        }
        else if (detectInteraction(bookPosition.minX, bookPosition.maxX, bookPosition.minY, bookPosition.maxY, bookPosition.minZ, bookPosition.maxZ))
        {
            cout << "You clicked the door lock!" << endl;
            selectedComponent = bookId;
        }
        else if (detectInteraction(tablePosition.minX, tablePosition.maxX, tablePosition.minY, tablePosition.maxY, tablePosition.minZ, tablePosition.maxZ))
        {
            cout << "You clicked the door lock!" << endl;
            selectedComponent = tableId;
        }

        else
        {
            selectedComponent = -1;
            cout << "You clicked on empty space." << endl;
        }
    }
}

void timer(int value)
{
    if (doorAnimating)
    {
        if (doorAngle > -60)
        {
            doorAngle -= 5.0f;
        }
        else
        {
            doorAnimating = false;
        }
    }

    glutPostRedisplay();
    glutTimerFunc(16, timer, 0); //  Wait 16ms, then run this function again
}

unsigned int loadTexture(const char *path)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char *data = stbi_load(path, &width, &height, &nrChannels, 0);
    if (data)
    {
        GLenum format = (nrChannels == 4) ? GL_RGBA : GL_RGB;
        glBindTexture(GL_TEXTURE_2D, textureID);
        gluBuild2DMipmaps(GL_TEXTURE_2D, format, width, height, format, GL_UNSIGNED_BYTE, data);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        stbi_image_free(data);
    }
    else
    {
        std::cout << "Texture failed to load at path: " << path << std::endl;
    }
    return textureID;
}

int main(int argc, char *argv[])
{

    cout << "------------- Keyboard Input -------------" << endl;
    cout << "x: Rotate X-axis +2.5 degree" << endl;
    cout << "X: Rotate X-axis -2.5 degree" << endl;
    cout << "y: Rotate Y-axis +2.5 degree" << endl;
    cout << "Y: Rotate Y-axis -2.5 degree" << endl;
    cout << "z: Rotate Y-axis +2.5 degree" << endl;
    cout << "e: Rotate Z-axis +2.5 degree" << endl;
    cout << "Z: Rotate Z-axis -2.5 degree" << endl;
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

    glutCreateWindow("Escape Room");

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
    // glEnable(GL_LIGHT1);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glShadeModel(GL_SMOOTH);

    glutPassiveMotionFunc(mouseMove);
    glutMouseFunc(mouseClick);
    glutSetCursor(GLUT_CURSOR_NONE);

    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    woodTex = loadTexture("/Users/sajjad/University/OpenGL/Escape_Room/assets/wood.jpg");
    brickTex = loadTexture("/Users/sajjad/University/OpenGL/Escape_Room/assets/brick.jpg");
    sceneryTex = loadTexture("/Users/sajjad/University/OpenGL/Escape_Room/assets/images.jpg");
    doorTex = loadTexture("/Users/sajjad/University/OpenGL/Escape_Room/assets/door.png");
    metalTex = loadTexture("/Users/sajjad/University/OpenGL/Escape_Room/assets/metal.png");
    concreteTex = loadTexture("/Users/sajjad/University/OpenGL/Escape_Room/assets/concrete.png");
    bookPagesTex= loadTexture("/Users/sajjad/University/OpenGL/Escape_Room/assets/book_pages.png");

    glutMainLoop();

    return EXIT_SUCCESS;
}
