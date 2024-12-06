#include"../include/Global.h"

const int GAME_FPS = 120;

ResourceManager& RESOURCE_MANAGER = Singleton<ResourceManager>::getInstance();
FPSManager& FPS_MANAGER = Singleton<FPSManager>::getInstance(GAME_FPS);
InputManager& INPUT_MANAGER = Singleton<InputManager>::getInstance();
Settings& SETTINGS = Singleton<Settings>::getInstance();