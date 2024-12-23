#ifndef MAP_H
#define MAP_H
#include "Entity.h"
#include "BaseBlock.h"
#include "BlockFactory.h"
#include "GoomBa.h"
#include "KoopaTroopa.h"
#include "Plant.h"
#include "Shell.h"
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <vector>
#include <string>

class MapHelper {
public:
    static bool loadFromTextFile(std::ifstream& file, std::vector<BaseBlock*>& blocks, std::vector<Enemy*>& enemies, std::vector<Item*>& items, std::vector<BaseBlock*>& decor);
    static void saveToTextFile(const std::string& filename, const std::vector<Entity*>& entities); /// not using.

private:
    static bool stringToEnemyType(std::string& enemyTypeStr, std::string& subTypeStr, EnemyType& enemyTypeOut, int& subTypeOut);
    static Color getDefaultColorForBlockType(BlockType blockType);
    static BlockType stringToBlockType(const std::string& typeStr);
    static string blockTypeToString(BlockType type);
    static ItemType stringToItemType(const string& typeStr);
};

class Map {
public:
    Map();
    ~Map();

    Vector2 getMapSize();
    //void addEntity(Entity* entity);
    void loadFromFile(const std::string& filename);
    void saveToFile(const std::string& filename) const;

    std::vector<BaseBlock*> getBlocks() const;
    std::vector<Enemy*> getEnemies() const;
    std::vector<Item*> getItems() const;
    std::vector<BaseBlock*> getDecor() const;

    void loadBackground(const std::string& filePath);
    void renderAllBlock();
    void renderBackground() const;

private:
    std::vector<BaseBlock*> blockArray;
    std::vector<Enemy*> enemies;
    std::vector<Item*> items;
    std::vector<BaseBlock*> decor;
    Texture2D background;

    void clearThings();
};

class Level {
private:
    std::string mapPath;
    std::string backGroundPath;
    string music;

public: 
    Level(const std::string& map, const std::string& background,string music);
    std::string getMapPath() const;
    std::string getBackGroundPath() const;
    string getMusic() const;
};
#endif