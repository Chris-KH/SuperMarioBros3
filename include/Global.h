#pragma once

#include"../include/Singleton.h"
#include"../include/ResourceManager.h"
#include"../include/FPSManager.h"
#include"../include/InputManager.h"
#include"../include/Settings.h"
#include<random>
#include<vector>
#include<map>
#include<unordered_map>


extern const int GAME_FPS;

extern ResourceManager& RESOURCE_MANAGER;
extern FPSManager& FPS_MANAGER;
extern InputManager& INPUT_MANAGER;
extern Settings& SETTINGS;

enum Orientation {
	LEFT,
	RIGHT,
	UP,
	DOWN,
	DOWNLEFT,
	UPLEFT,
	DOWNRIGHT,
	UPRIGHT
};

enum Edge {
	LEFT_EDGE,
	RIGHT_EDGE,
	TOP_EDGE,
	BOTTOM_EDGE
};

enum EntityType {
	CHACRACTER,
	ENEMY,
	ITEM,
	BLOCK
};

//Character
enum CharacterType {
	MARIO,
	LUIGI
};

enum STATE {
	NORMAL,
	SUPER,
	FIRE,
	STARMAN
};

//Item
enum ItemType {
	COIN,
	MUSHROOM,
	SUPERLEAF,
	FLOWER,
	STAR
};

enum MushroomType {
	MUSHROOM_SUPER, //Enlarges Mario, turning him into Super Mario and allowing him to survive one hit.
	MUSHROOM_1UP //Provides an extra life.
};

//Enemy
enum EnemyType {
	GOOMBA,
	KOOPATROOPA,
	PLANT
};

enum GoomBaType {
	BROWN_GoomBa,
	RED_GoomBa,
	REDPARA_GoomBa,
	BROWNPARA_GoomBa,
	MICRO_GoomBa
};

enum KoopaTroopaType {
	GREEN_KoopaTroopa,
	RED_KoopaTroopa,
	GREEN_KoopaParaTroopa,
	RED_KoopaParaTroopa
};

enum PlantType {
	RED_PIRANHA,
	RED_FIREPIRANHA,
	GREEN_PIRANHA,
	GREEN_FIREPIRANHA
};

//Block
enum BlockType {
	FLOOR,
	BRICK, // breakable
	SOLIDBLOCK, // unmovable, unbreakable
	MOVINGBLOCK,
	ITEMBLOCK,
	HIDDEN,
	SPIKE,
	PIPE,
	TEMPBLOCK,
	DECOR
};