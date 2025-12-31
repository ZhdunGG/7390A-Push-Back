#pragma once

#include "main.h"

// Initialize the selector
extern lv_obj_t *homeScreen;
void initializeSelector();

// Get the selected autonomous routine ID
// 0: Do Nothing
// 1: Left Side
// 2: Right Side
// 3: Skills
int getSelectedAuton();

// Check alliance color
bool isRedAlliance();
bool isBlueAlliance();