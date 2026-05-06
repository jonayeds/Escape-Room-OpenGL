// #include<windows.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>
#include <iostream>
using namespace std;

float degreeX = 0;
float degreeY = 0;
float degreeZ = 0;
float scale = 0.5;
float posX = 0.0f;
float posZ = -23.0f;
float posY = 0.0f;

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

    for (int x = 0; x < width; x++) {
        for (int z = 0; z < depth; z++) {
            float curX = startX + x;
            float curZ = startZ + z ;
            Quads(curX, 0, curZ);
        }
    }
}

void DrawGrid_XY(float width, float height) 
{
    float startX = -width / 2.0f;
    float startY = -height / 2.0f;

    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            float curX = startX + x;
            float curY = startY + y ;
            Quads(curX,  curY, 0);
        }
    }
}

void DrawGrid_YZ(float height, float depth) 
{
    float startY = -height / 2.0f;
    float startZ = -depth / 2.0f;

    for (int y = 0; y < height; y++) {
        for (int z = 0; z < depth; z++) {
            float curY = startY + y;
            float curZ = startZ + z ;
            Quads(0,curY, curZ);
        }
    }
}


static void light(){
GLfloat light_position[] = {0.0f, 0.0f, 0.0f, 1.0f};
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    
    glPushMatrix();
        glDisable(GL_LIGHTING); 
        glColor3d(1, 1, 1);
        glTranslatef(0.0f, 0.0f, 0.0f);
        glutSolidSphere(0.5, 64, 64);
        glEnable(GL_LIGHTING); 
    glPopMatrix();
    


}


static void Room()
{
    light();


    // floor
    glPushMatrix();
    glTranslatef(0,-3.5,0);
    DrawGrid_XZ(15.0f,15.0f);
    glPopMatrix();
    
    // pillers
    glPushMatrix();
    glTranslatef(7,0,7);
    glScalef(1,7,1);
    Quads(-0.5,-0.5,-0.5);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(7,0,-7);
    glScalef(1,7,1);
    Quads(-0.5,-0.5,-0.5);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-7,0,-7);
    glScalef(1,7,1);
    Quads(-0.5,-0.5,-0.5);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-7,0,7);
    glScalef(1,7,1);
    Quads(-0.5,-0.5,-0.5);
    glPopMatrix();
    
    
    // walls

    // front side
    glPushMatrix();
    glTranslatef(-4,0,6.5);
    DrawGrid_XY(6,7);   
    glPopMatrix();

    glPushMatrix();
    glTranslatef(4,0,6.5);
    DrawGrid_XY(6,7);
    glPopMatrix();

    // back side
    glPushMatrix();
    glTranslatef(4.5,0,-7.5);
    DrawGrid_XY(4.5,7);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-4.5,0,-7.5);
    DrawGrid_XY(4.5,7);
    glPopMatrix();

    // left side
    glPushMatrix();
    glTranslatef(-7.5,0,-4);
    DrawGrid_YZ(7,6);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-7.5,0,4);
    DrawGrid_YZ(7,6);
    glPopMatrix();

    // right side
    glPushMatrix();
    glTranslatef(6.5,0,-4);
    DrawGrid_YZ(7,6);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(6.5,0,4);
    DrawGrid_YZ(7,6);
    glPopMatrix();


    // wall fillers

    // front
    glPushMatrix();
    glTranslatef(0,-2.25,7);
    glScalef(2,2,1);
    Quads(-0.5,-0.5,-0.5);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,2.5,7);
    glScalef(2,2,1);
    Quads(-0.5,-0.5,-0.5);
    glPopMatrix();
    
    // left side
    glPushMatrix();
    glTranslatef(7,2.5,0);
    glScalef(1,2,2);
    Quads(-0.5,-0.5,-0.5);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(7,-2.25,0);
    glScalef(1,2,2);
    Quads(-0.5,-0.5,-0.5);
    glPopMatrix();

    // right side
    glPushMatrix();
    glTranslatef(-7,2.5,0);
    glScalef(1,2,2);
    Quads(-0.5,-0.5,-0.5);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-7,-2.25,0);
    glScalef(1,2,2);
    Quads(-0.5,-0.5,-0.5);
    glPopMatrix();

    // roof
    glPushMatrix();
    glTranslatef(0,3.5,0);
    DrawGrid_XZ(15.0f, 15.0f);
    glPopMatrix();

    


}




static void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glTranslatef(posX, posY, posZ);
    glTranslatef(0, 0, 13);
    
    
    // light
    // light();

    
    

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
        posX -= 0.5f;
        break;
    case GLUT_KEY_RIGHT:
        posX += 0.5f;
        break;
    case GLUT_KEY_UP:
        if (shift)
        {
            posZ += 0.5f;
        }
        else
        {
            posY += 0.5f;
        }
        break;
    case GLUT_KEY_DOWN:
        if (shift)
        {
            posZ -= 0.5f;
        }
        else
        {
            posY -= 0.5f;
        }
        break;
    }
    glutPostRedisplay();
}

static void idle(void)
{
    glutPostRedisplay();
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
    glutIdleFunc(idle);

    glClearColor(0, 0, 0, 1);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glShadeModel(GL_SMOOTH);

    

    glutMainLoop();

    return EXIT_SUCCESS;
}
