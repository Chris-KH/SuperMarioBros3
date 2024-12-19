#pragma once

#include "Block.h"
#include "BlockFactory.h"
#include "GoomBa.h"
#include "KoopaTroopa.h"
#include "Plant.h"
#include "Shell.h"
#include <fstream>
#include <sstream>
#include <stdexcept>

class MapHelper {
public:

    static bool loadFromTextFile(std::ifstream& file, std::vector<Entity*>& blocks, std::vector<Entity*>& enemies, std::vector<Entity*>& items)
    {
        std::string line;
        std::string currentSection;

        while (std::getline(file, line)) {
            if (line.empty()) {
                continue;
            }

            // Check for section marker
            if (line == "block" || line == "enemy" || line == "item") {
                currentSection = line;
                continue;
            }

            if (currentSection == "block") {
                std::istringstream stream(line);
                std::string blockTypeStr;
                float x, y, width, height, boundRight, boundBottom, velocityX, velocityY;

                // Read the block type first
                if (!(stream >> blockTypeStr)) {
                    throw std::runtime_error("Malformed line in file: " + line);
                }

                BlockType blockType = stringToBlockType(blockTypeStr);

                if (blockType == MOVINGBLOCK) {
                    if (!(stream >> x >> y >> width >> height >> boundRight >> boundBottom >> velocityX >> velocityY)) {
                        throw std::runtime_error("Malformed line for moving block: " + line);
                    }

                    MovingBlock* block = dynamic_cast<MovingBlock*>(
                        BlockFactory::getInstance().createBlock(
                            blockType, { x, y }, { width, height }, getDefaultColorForBlockType(blockType)));

                    if (!block) {
                        throw std::runtime_error("Failed to create moving block: " + blockTypeStr);
                    }

                    block->setBounds(x, boundRight, y, boundBottom);
                    block->setVelocity({ velocityX, velocityY });

                    blocks.push_back(static_cast<Entity*>(block));
                }
                else {
                    if (!(stream >> x >> y >> width >> height)) {
                        throw std::runtime_error("Malformed line for static block: " + line);
                    }

                    BaseBlock* block = BlockFactory::getInstance().createBlock(
                        blockType, { x, y }, { width, height }, getDefaultColorForBlockType(blockType));

                    if (!block) {
                        throw std::runtime_error("Failed to create static block: " + blockTypeStr);
                    }

                    blocks.push_back(static_cast<Entity*>(block));
                }
            }
            else if (currentSection == "enemy") {
                std::istringstream stream(line);
                std::string enemyTypeStr;
                std::string specificType;
                float x, y, boundLeft, boundRight;
                int orientation;

                EnemyType type;
                int subtype;
                stream >> enemyTypeStr >> specificType;
                if(!stringToEnemyType(enemyTypeStr, specificType,type,subtype))
                    throw std::runtime_error("Malformed line in file: " + line);
                if (!(stream >> x >> y >> boundLeft >> boundRight >> orientation)) {
                    throw std::runtime_error("Malformed line : " + line);
                }
                if(orientation >=8)
                    throw std::runtime_error("Malformed line (orientation error): " + line);
                Orientation facing = static_cast<Orientation>(orientation);
                if (type == GOOMBA)
                {

                    GoomBa* enemy = new GoomBa(static_cast<GoomBaType>(subtype), { x,y },facing);
                    enemy->setBoudary({ boundLeft,boundRight });
                    enemies.push_back(enemy);
                }
                else if (type == KOOPATROOPA)
                {
                    KoopaTroopa* enemy = new KoopaTroopa(static_cast<KoopaTroopaType>(subtype), { x,y }, facing);
                    enemy->setBoudary({ boundLeft,boundRight });
                    enemies.push_back(enemy);
                }
                //if (type == PLANT)
                //{
                //    Plant* enemy = new Plant(static_cast<PlantType>(subtype), { x,y }, facing);
                //    enemy->setBoudary({ boundLeft,boundRight });
                //    enemies.push_back(enemy);
                //}
                else if (type == SHELL)
                {
                    Shell* enemy = new Shell(static_cast<ShellType>(subtype), { x,y });
                    enemy->setBoudary({ boundLeft,boundRight });
                    enemies.push_back(enemy);
                }



            }
            else if (currentSection == "item") {
                // Placeholder for item loading logic               
            }
            else {
                throw std::runtime_error("Unknown section: " + currentSection);
            }
        }

        return true;
    }




    static void saveToTextFile(const std::string& filename, const std::vector<Entity*>& entities) {
        //std::ofstream file(filename);

        //if (!file.is_open()) {
        //    throw std::runtime_error("Failed to open file: " + filename);
        //}

        //for (Entity* entity : entities) {
        //    // Attempt to cast the Entity* back to BaseBlock*
        //    BaseBlock* block = dynamic_cast<BaseBlock*>(entity);
        //    if (!block) {
        //        throw std::runtime_error("Invalid entity type: Cannot save non-block entities.");
        //    }

        //    // Write block data to the file
        //    file << blockTypeToString(block->getBlockType()) << " "
        //        << block->getPosition().x << " "
        //        << block->getPosition().y << " "
        //        << block->getSize().x << " "
        //        << block->getSize().y << "\n";
        //}
    }

private:
    static bool stringToEnemyType( std::string& enemyTypeStr, std::string& subTypeStr, EnemyType& enemyTypeOut, int& subTypeOut) {
        if (enemyTypeStr == "GOOMBA") {
            enemyTypeOut = GOOMBA;
            if (subTypeStr == "BROWN_GoomBa") {
                subTypeOut = BROWN_GoomBa;
            }
            else if (subTypeStr == "RED_GoomBa") {
                subTypeOut = RED_GoomBa;
            }
            else if (subTypeStr == "REDPARA_GoomBa") {
                subTypeOut = REDPARA_GoomBa;
            }
            else if (subTypeStr == "BROWNPARA_GoomBa") {
                subTypeOut = BROWNPARA_GoomBa;
            }
            else if (subTypeStr == "MICRO_GoomBa") {
                subTypeOut = MICRO_GoomBa;
            }
            else {
                return false;
            }
        }
        else if (enemyTypeStr == "KOOPATROOPA") {
            enemyTypeOut = KOOPATROOPA;
            if (subTypeStr == "GREEN_KoopaTroopa") {
                subTypeOut = GREEN_KoopaTroopa;
            }
            else if (subTypeStr == "RED_KoopaTroopa") {
                subTypeOut = RED_KoopaTroopa;
            }
            else if (subTypeStr == "GREENPARA_KoopaTroopa") {
                subTypeOut = GREENPARA_KoopaTroopa;
            }
            else if (subTypeStr == "REDPARA_KoopaTroopa") {
                subTypeOut = REDPARA_KoopaTroopa;
            }
            else {
                return false;
            }
        }
        else if (enemyTypeStr == "PLANT") {
            enemyTypeOut = PLANT;
            if (subTypeStr == "RED_PIRANHA") {
                subTypeOut = RED_PIRANHA;
            }
            else if (subTypeStr == "RED_FIREPIRANHA") {
                subTypeOut = RED_FIREPIRANHA;
            }
            else if (subTypeStr == "GREEN_PIRANHA") {
                subTypeOut = GREEN_PIRANHA;
            }
            else if (subTypeStr == "GREEN_FIREPIRANHA") {
                subTypeOut = GREEN_FIREPIRANHA;
            }
            else {
                return false;
            }
        }
        else if (enemyTypeStr == "SHELL") {
            enemyTypeOut = SHELL;
            if (subTypeStr == "GREEN_SHELL") {
                subTypeOut = GREEN_SHELL;
            }
            else if (subTypeStr == "RED_SHELL") {
                subTypeOut = RED_SHELL;
            }
            else {
                return false;
            }
        }
        else {
            return false;
        }
        return true;
    }


    // Get default color for a given block type
    static Color getDefaultColorForBlockType(BlockType blockType) {
        switch (blockType) {
        case FLOOR:      return BLANK;
        case BRICK:      return BROWN;
        case SOLIDBLOCK: return BLANK;
        case MOVINGBLOCK: return DARKGRAY;
        case ITEMBLOCK:  return YELLOW;
        case HIDDEN:     return WHITE;
        case SPIKE:      return BLACK;
        case PIPE:       return DARKGREEN;
        case TEMPBLOCK:  return BLANK;
        case DECOR:      return LIGHTGRAY;
        default:         return ORANGE;
        }
    }

    // Convert string to BlockType enum
    static BlockType stringToBlockType(const std::string& typeStr) {
        if (typeStr == "FLOOR")      return FLOOR;
        if (typeStr == "BRICK")      return BRICK;
        if (typeStr == "SOLIDBLOCK") return SOLIDBLOCK;
        if (typeStr == "MOVINGBLOCK") return MOVINGBLOCK;
        if (typeStr == "ITEMBLOCK")  return ITEMBLOCK;
        if (typeStr == "HIDDEN")     return HIDDEN;
        if (typeStr == "SPIKE")      return SPIKE;
        if (typeStr == "PIPE")       return PIPE;
        if (typeStr == "TEMPBLOCK")  return TEMPBLOCK;
        if (typeStr == "DECOR")      return DECOR;

        throw std::invalid_argument("Invalid block type string: " + typeStr);
    }

    // Convert BlockType enum to string
    static std::string blockTypeToString(BlockType type) {
        switch (type) {
        case FLOOR:      return "FLOOR";
        case BRICK:      return "BRICK";
        case SOLIDBLOCK: return "SOLIDBLOCK";
        case MOVINGBLOCK: return "MOVINGBLOCK";
        case ITEMBLOCK:  return "ITEMBLOCK";
        case HIDDEN:     return "HIDDEN";
        case SPIKE:      return "SPIKE";
        case PIPE:       return "PIPE";
        case TEMPBLOCK:  return "TEMPBLOCK";
        case DECOR:      return "DECOR";
        default:         return "UNKNOWN";
        }
    }
};

class Map {
public:
    Map() : background({ 0 }) {}
    ~Map() {
       if (background.id > 0) {
            UnloadTexture(background);
            background.id = 0;
        }
        clearThings();

    }
    Vector2 getMapSize()
    {
        if (background.id <= 0)
            throw std::runtime_error("error loading map");
        float x = (float)background.width;
        float y = (float)background.height;
        return { x,y };
    }
    void addEntity(Entity* entity) {
        blockArray.push_back(entity);
    }

    void loadFromFile(const std::string& filename) {
        clearThings();
        std::ifstream file(filename);
        if (!file.is_open()) {
            throw std::runtime_error("Failed to open file: " + filename);
        }
        MapHelper::loadFromTextFile(file,blockArray,enemies,items);
        file.close();
    }

    void saveToFile(const std::string& filename) const {
        MapHelper::saveToTextFile(filename, blockArray);
    }

 /*   const std::vector<Entity*>& getEntities() const {
        return blockArray;
    }*/

    vector<Entity*> getBlocks() const {
        std::vector<Entity*> blocks;
        for (Entity* entity : blockArray) {
            if (Entity* block = entity) {
                blocks.push_back(block);
            }
        }
        return blocks;
    }
    vector<Entity*> getEnemies() const {
        std::vector<Entity*> things;
        for (Entity* entity : enemies) {
            if (Entity* thing = entity) {
                things.push_back(thing);
            }
        }
        return things;
    }   
    vector<Entity*> getItems() const {
        std::vector<Entity*> things;
        for (Entity* entity : items) {
            if (Entity* thing = entity) {
                things.push_back(thing);
            }
        }
        return things;
    }
    void loadBackground(const std::string& filePath) {
        if (background.id > 0) {
            UnloadTexture(background);
        }
        background = LoadTexture(filePath.c_str());
        if (background.id == 0) {
            throw std::runtime_error("Failed to load background texture: " + filePath);
        }
    }
    void renderAllBlock()
    {
        for (Entity* entity : blockArray)
            entity->draw();
    }
    void renderBackground() const {
        if (background.id > 0) {
            DrawTexture(background, 0, 0, WHITE);
        }
    }
private:
    vector<Entity*> blockArray;
    vector<Entity*> enemies;
    vector<Entity*> items;
    Texture2D background;
    void clearThings() {
        for (Entity* entity : blockArray) {
            if(entity)
            delete entity;
        }
        for (Entity* entity : enemies)
        {
            if (entity)
            delete entity;
        }
        for (Entity* entity : items)
        {
            if (entity)
            delete entity;
        }

        blockArray.clear();
    }
};

class Level {
private:
    string mapPath;
    string backGroundPath;

public:
    Level(const string& map, const string& background)
        : mapPath(map), backGroundPath(background) {}
    string getMapPath() const {
        return mapPath;
    }
    string getBackGroundPath() const {
        return backGroundPath;
    }
};