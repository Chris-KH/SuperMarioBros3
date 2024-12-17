#pragma once

#include"../include/Singleton.h"
#include"../include/ResourceManager.h"
#include"../include/FPSManager.h"
#include"../include/InputManager.h"
#include"../include/Settings.h"


extern const int GAME_FPS;

extern ResourceManager& RESOURCE_MANAGER;
extern FPSManager& FPS_MANAGER;
extern InputManager& INPUT_MANAGER;
extern Settings& SETTINGS;