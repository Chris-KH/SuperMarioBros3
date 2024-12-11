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
        case FLOOR:      return GREEN;
        case BRICK:      return BROWN;
        case SOLIDBLOCK: return DARKBROWN;
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
        entities.push_back(entity);
    }

    void loadFromFile(const std::string& filename) {
        clearBlocks();
        entities = MapHelper::loadFromTextFile(filename);
    }

    void saveToFile(const std::string& filename) const {
        MapHelper::saveToTextFile(filename, entities);
    }

    const std::vector<Entity*>& getEntities() const {
        return entities;
    }

    std::vector<BaseBlock*> getBlocks() const {
        std::vector<BaseBlock*> blocks;
        for (Entity* entity : entities) {
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

    void renderAllBlock() {
        for (Entity* entity : entities)
            entity->draw();

    }
    
    void renderBackground() const {
        if (background.id > 0) {
            DrawTexture(background, 0, 0, WHITE);
        }
    }

private:
    std::vector<Entity*> entities;
    Texture2D background;
    void clearBlocks() {
        for (Entity* entity : entities) {
            delete entity;
        }
        entities.clear();
    }
};


//
//class Map {
//public:
//   Map() {}
//
//    ~Map() {
//        for (BaseBlock* block : blocks) {
//            delete block;
//        }
//    }
//
//    void addBlock(BaseBlock* block) {
//        blocks.push_back(block);
//    }
//
//    void saveMap(std::string &filename) {
//        std::ofstream savedFile(filename, std::ios::binary);
//        if (savedFile.is_open()) {
//            size_t numBlocks = blocks.size();
//            savedFile.write(reinterpret_cast<const char*>(&numBlocks), sizeof(numBlocks));
//            for (std::vector<BaseBlock*>::iterator it = blocks.begin(); it != blocks.end(); ++it) {
//                //(*it)->savetoBinaryFile(savedFile);
//            }
//        }
//    }
//
//    void loadMap(std::string &filename) {
//        std::ifstream loadedFile(filename, std::ios::binary);
//        if (loadedFile.is_open()) {
//            int numBlocks = 0;
//            loadedFile.read(reinterpret_cast<char*>(&numBlocks), sizeof(numBlocks));
//            blocks.clear();
//            for (int i = 0; i < numBlocks; ++i) {
//                //BaseBlock* block = new SolidBlock(0, 0, 0, 0);
//                //block->loadfromBinaryFile(loadedFile);
//                //blocks.push_back(block);
//            }
//        }
//    }
//    
//private:
//    std::vector<BaseBlock*> blocks;
//    BaseBlock* createBlockByType(BlockType blockType) {
//        switch (blockType) {
//            /*case FLOOR: return new Floor();
//            case BRICK: return new Brick();
//            case SOLIDBLOCK: return new SolidBlock();
//            case MOVINGBLOCK: return new MovingBlock();
//            case ITEMBLOCK: return new ItemBlock();
//            case HIDDEN: return new HiddenBlock();
//            case SPIKE: return new SpikeBlock();
//            case PIPE: return new PipeBlock();
//            case DECOR: return new DecorBlock();*/
//            default: return nullptr;
//        }
//    }
//};

class MapHelper {
public:
    // Load entities from a bitmap file
    static std::vector<Entity*> loadFromBitmap(const std::string& filename) {
        std::vector<Entity*> entities;
        int width, height, channels;
        unsigned char* data = stbi_load(filename.c_str(), &width, &height, &channels, 3); // Load dưới dạng RGB
        if (!data) {
            throw std::runtime_error("Failed to load bitmap file: " + filename);
        }
        // Iterate over the bitmap pixels
        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                // Get pixel color
                int index = (y * width + x) * 3; // Each pixel has 3 channels (R, G, B)
                Color pixelColor = { data[index], data[index + 1], data[index + 2], 255 };
                // Determine blockType based on pixel color
                BlockType blockType = colorToBlockType(pixelColor);
                if (blockType) {
                    BaseBlock* block = BlockFactory::getInstance().createBlock(blockType, { static_cast<float>(x), static_cast<float>(y) }, { 1.0f, 1.0f }, pixelColor);
                    if (block) {
                        entities.push_back(static_cast<Entity*>(block));
                    }
                }
            }
        }
        stbi_image_free(data); //Giải phóng data
        return entities;
    }

private:
    // Map pixel colors to block types
    static BlockType colorToBlockType(const Color& color) {
        if (color == GREEN) return FLOOR;
        if (color == BROWN) return BRICK;
        if (color == DARKBROWN) return SOLIDBLOCK;
        if (color == DARKGRAY) return MOVINGBLOCK;
        if (color == YELLOW) return ITEMBLOCK;
        if (color == WHITE) return HIDDEN;
        if (color == BLACK) return SPIKE;
        if (color == DARKGREEN) return PIPE;
        if (color == BLANK) return TEMPBLOCK;
        if (color == LIGHTGRAY) return DECOR;
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
        entities.push_back(entity);
    }

    void loadFromBitmapFile(const std::string& filename) {
        clearBlocks();
        entities = MapHelper::loadFromBitmap(filename);
    }

    void save2TextFile(const std::string &filename, std::vector<Entity*>& Entities) {
        std::ofstream file(filename);
        if (!file.is_open()) {
            throw std::runtime_error("Failed to open file: " + filename);
        }
        for (Entity* entity : entities) {
            BaseBlock* block = dynamic_cast<BaseBlock*>(entity);
            file << blockTypeToString(block->getBlockType()) << " "
                 << block->getPosition().x << " "
                 << block->getPosition().y << " "
                 << block->getSize().x << " "
                 << block->getSize().y << "\n";
        }
        file.close();
    }

    const std::vector<Entity*>& getEntities() const {
        return entities;
    }

    std::vector<BaseBlock*> getBlocks() const {
        std::vector<BaseBlock*> blocks;
        for (Entity* entity : entities) {
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

    void renderAllBlock() {
        for (Entity* entity : entities)
            entity->draw();

    }

    void renderBackground() const {
        if (background.id > 0) {
            DrawTexture(background, 0, 0, WHITE);
        }
    }

private:
    std::vector<Entity*> entities;
    Texture2D background;
    void clearBlocks() {
        for (Entity* entity : entities) {
            delete entity;
        }
        entities.clear();
    }
};

