#pragma once

#include "Block.h"
#include "BlockFactory.h"
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <vector>
#include <string>

class MapHelper {
public:
    // Load entities from a text file
    static std::vector<Entity*> loadFromTextFile(const std::string& filename) {
        std::vector<Entity*> entities;
        std::ifstream file(filename);

        if (!file.is_open()) {
            throw std::runtime_error("Failed to open file: " + filename);
        }

        std::string line;
        while (std::getline(file, line)) {
            std::istringstream stream(line);
            std::string blockTypeStr;
            float x, y, width, height;

            // Read block data
            if (!(stream >> blockTypeStr >> x >> y >> width >> height)) {
                throw std::runtime_error("Malformed line in file: " + line);
            }

            // Convert block type string to BlockType enum
            BlockType blockType = stringToBlockType(blockTypeStr);

            // Create block using the factory
            BaseBlock* block = BlockFactory::getInstance().createBlock(
                blockType, { x, y }, { width, height }, getDefaultColorForBlockType(blockType));

            // Ensure the block was successfully created
            if (!block) {
                throw std::runtime_error("Unknown block type: " + blockTypeStr);
            }

            // Store as Entity*
            entities.push_back(static_cast<Entity*>(block));
        }

        return entities;
    }

    // Save entities to a text file
    static void saveToTextFile(const std::string& filename, const std::vector<Entity*>& entities) {
        std::ofstream file(filename);

        if (!file.is_open()) {
            throw std::runtime_error("Failed to open file: " + filename);
        }

        for (Entity* entity : entities) {
            // Attempt to cast the Entity* back to BaseBlock*
            BaseBlock* block = dynamic_cast<BaseBlock*>(entity);
            if (!block) {
                throw std::runtime_error("Invalid entity type: Cannot save non-block entities.");
            }

            // Write block data to the file
            file << blockTypeToString(block->getBlockType()) << " "
                << block->getPosition().x << " "
                << block->getPosition().y << " "
                << block->getSize().x << " "
                << block->getSize().y << "\n";
        }
    }

private:
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
        clearBlocks();
        if (background.id > 0) {
            UnloadTexture(background);
        }
    }

    void addEntity(Entity* entity) {
        blockArray.push_back(entity);
    }

    void loadFromFile(const std::string& filename) {
        clearBlocks();
        blockArray = MapHelper::loadFromTextFile(filename);
    }

    void saveToFile(const std::string& filename) const {
        MapHelper::saveToTextFile(filename, blockArray);
    }

    const std::vector<Entity*>& getEntities() const {
        return blockArray;
    }

    std::vector<BaseBlock*> getBlocks() const {
        std::vector<BaseBlock*> blocks;
        for (Entity* entity : blockArray) {
            if (BaseBlock* block = dynamic_cast<BaseBlock*>(entity)) {
                blocks.push_back(block);
            }
        }
        return blocks;
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
    vector<Entity*>* returnBlockArray()
    {
        return &blockArray;
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
    std::vector<Entity*> blockArray;
    Texture2D background;
    void clearBlocks() {
        for (Entity* entity : blockArray) {
            delete entity;
        }
        blockArray.clear();
    }
};