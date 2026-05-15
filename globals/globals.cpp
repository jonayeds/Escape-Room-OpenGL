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
string doorCode = "1234";
string inputCode = "";     