#pragma once
#include"Singleton.h"
#include"ResourceManager.h"
#include"FPSManager.h"
#include"InputManager.h"
#include"Settings.h"
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
	CHARACTER,
	ENEMY,
	ITEM,
	FIREBALL,
	EFFECT,
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
	STARMAN,
	SUPERSTARMAN,
	FIRESTARMAN
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

enum CoinType {
	BLOCK_COIN,
	STATIC_COIN
};

enum FlowerType {
	FIRE_FLOWER, //Grants Mario the ability to throw fireballs.
	ICE_FLOWER, //Grants Mario the ability to throw iceballs.
	BOOMERANG_FLOWER, //Grants Mario the ability to throw boomerangs.
};

enum StarType {
	YELLOW_STAR, //Grants Mario invincibility for a short period of time.
	BLUE_STAR, //Grants Mario invincibility for a longer period of time.
};

//Enemy
enum EnemyType {
	GOOMBA,
	KOOPATROOPA,
	PLANT,
	SHELL
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
	GREENPARA_KoopaTroopa,
	REDPARA_KoopaTroopa
};

enum PlantType {
	RED_PIRANHA,
	RED_FIREPIRANHA,
	GREEN_PIRANHA,
	GREEN_FIREPIRANHA
};

enum ShellType {
	GREEN_SHELL,
	RED_SHELL
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
