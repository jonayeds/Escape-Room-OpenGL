#include "globals.h"
#include <iostream>
using namespace std;
float degreeX = 0;
float degreeY = 0;
float degreeZ = 0;
float scale = 0.5;
float posX = 0.0f;
float posZ = 0.0f;
float posY = 0.0f;

// The direction the camera is looking
float lookDirX = 0.0f;
float lookDirY = 0.0f;
float lookDirZ = 1.0f;

float yaw = 90.0f; 
float pitch = 0.0f;
float sensitivity = 0.1f;
int windowWidth = 1080;
int windowHeight = 720;

int mouseX = 0;
int mouseY = 0;
int lastMouseX = -1;
int lastMouseY = -1;     

float doorAngle = 0.0f;
bool doorAnimating = false;

int selectedComponent = -1;
int doorLockId = 0;
int tableId = 1;
int bookId = 2;
int chairId = 3;
int wallFrame1Id = 4;
int wallFrame2Id = 5;
int teapotId = 6;
string doorCode = "1234";
string inputCode = "";   

// texture IDs
unsigned int woodTex, brickTex, sceneryTex, doorTex, metalTex, concreteTex, bookPagesTex, bookCoverTex, painting1Tex, painting2Tex;

// components positions
ComponentPosition doorPosition = {-0.3f, 0.8f, 0.0f, 1.0f, -6.5f, -6.3f};
ComponentPosition tablePosition = {3.5, 5.95f, -2.5f, -0.85f, 4.0f, 5.5f};
ComponentPosition bookPosition = {4.36, 5.0, -0.8f, -0.6f, 4.25f, 4.75f};
ComponentPosition chairPosition = {4.2f, 5.2f, -2.5f, -0.5f, 3.0f, 4.0f};
ComponentPosition wallFrame1Position = {6.44f, 6.56f, -0.5f, 0.5f, -3.1f, -1.9f};
ComponentPosition wallFrame2Position = {4.5f, 5.5f, 0.0f, 1.0f, 6.44f, 6.55f};
ComponentPosition teapotPosition = {3.5f, 4.0f, -0.8f, -0.5, 4.2f, 4.6f};

