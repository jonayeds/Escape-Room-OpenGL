#pragma once
#include "../globals/globals.h"

bool detectInteraction(float minX, float maxX, float minY, float maxY, float minZ, float maxZ);
void drawDebugHitbox(ComponentPosition pos);
void drawDebugLaser();