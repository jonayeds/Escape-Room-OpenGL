#pragma once

#include <iostream>
using namespace std;

extern float degreeX;
extern float degreeY;
extern float degreeZ;
extern float scale;
extern float posX;
extern float posZ;
extern float posY;

extern float lookDirX;
extern float lookDirY;
extern float lookDirZ;

extern float yaw;
extern float pitch;
extern float sensitivity;
extern int windowWidth;
extern int windowHeight;

extern int mouseX;
extern int mouseY;
extern int lastMouseX;
extern int lastMouseY;

extern float doorAngle;
extern bool doorAnimating;

extern int selectedComponent;
extern int doorLockId;
extern int tableId;
extern int bookId;
extern int chairId;
extern int wallFrame1Id;
extern int wallFrame2Id;
extern string doorCode;
extern string inputCode;

struct ComponentPosition
{
    float minX;
    float maxX;
    float minY;
    float maxY;
    float minZ;
    float maxZ;
};

extern unsigned int woodTex, brickTex, sceneryTex, doorTex, metalTex, concreteTex, bookPagesTex, bookCoverTex, painting1Tex, painting2Tex;

extern ComponentPosition doorPosition;
extern ComponentPosition tablePosition;
extern ComponentPosition bookPosition;
extern ComponentPosition chairPosition;
extern ComponentPosition wallFrame1Position;
extern ComponentPosition wallFrame2Position;