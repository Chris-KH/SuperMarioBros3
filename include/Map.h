#pragma once

#include "Block.h"
#include "BlockFactory.h"
#include <fstream>
#include <sstream>
#include <stdexcept>

class MapHelper {
public:
    static std::vector<BaseBlock*> loadFromTextFile(const std::string& filename) {
        std::vector<BaseBlock*> blocks;
        std::ifstream file(filename);

        if (!file.is_open()) {
            throw std::runtime_error("Failed to open file: " + filename);
        }

        std::string line;
        while (std::getline(file, line)) {
            std::istringstream stream(line);
            std::string blockTypeStr;
            float x, y, width, height;

            stream >> blockTypeStr >> x >> y >> width >> height;

            BlockType blockType = stringToBlockType(blockTypeStr);

            BaseBlock* block = BlockFactory::getInstance().createBlock(
                blockType, { x, y }, { width, height }, getDefaultColorForBlockType(blockType));

            if (block) {
                blocks.push_back(block);
            }
            else {
                throw std::runtime_error("Unknown block type: " + blockTypeStr);
            }
        }

        return blocks;
    }

    static void saveToTextFile(const std::string& filename, const std::vector<BaseBlock*>& blocks) {
        std::ofstream file(filename);

        if (!file.is_open()) {
            throw std::runtime_error("Failed to open file: " + filename);
        }

        for (BaseBlock* block : blocks) {
            if (block) {
                file << blockTypeToString(block->getBlockType()) << " "
                    << block->getPosition().x << " "
                    << block->getPosition().y << " "
                    << block->getSize().x << " "
                    << block->getSize().y << "\n";
            }
        }
    }

private:
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
    static BlockType stringToBlockType(const std::string& typeStr) {
        if (typeStr == "FLOOR") return FLOOR;
        if (typeStr == "BRICK") return BRICK;
        if (typeStr == "SOLIDBLOCK") return SOLIDBLOCK;
        if (typeStr == "MOVINGBLOCK") return MOVINGBLOCK;
        if (typeStr == "ITEMBLOCK") return ITEMBLOCK;
        if (typeStr == "HIDDEN") return HIDDEN;
        if (typeStr == "SPIKE") return SPIKE;
        if (typeStr == "PIPE") return PIPE;
        if (typeStr == "TEMPBLOCK") return TEMPBLOCK;
        if (typeStr == "DECOR") return DECOR;

        throw std::invalid_argument("Invalid block type string: " + typeStr);
    }

    static std::string blockTypeToString(BlockType type) {
        switch (type) {
        case FLOOR: return "FLOOR";
        case BRICK: return "BRICK";
        case SOLIDBLOCK: return "SOLIDBLOCK";
        case MOVINGBLOCK: return "MOVINGBLOCK";
        case ITEMBLOCK: return "ITEMBLOCK";
        case HIDDEN: return "HIDDEN";
        case SPIKE: return "SPIKE";
        case PIPE: return "PIPE";
        case TEMPBLOCK: return "TEMPBLOCK";
        case DECOR: return "DECOR";
        default: return "UNKNOWN";
        }
    }
};
class Map {
public:
    ~Map() {
        clearBlocks();
    }

    void addBlock(BaseBlock* block) {
        blocks.push_back(block);
    }

    void loadFromFile(const std::string& filename) {
        clearBlocks();
        blocks = MapHelper::loadFromTextFile(filename);
    }

    void saveToFile(const std::string& filename) const {
        MapHelper::saveToTextFile(filename, blocks);
    }

    const std::vector<BaseBlock*>& getBlocks() const {
        return blocks;
    }

private:
    std::vector<BaseBlock*> blocks;

    void clearBlocks() {
        for (BaseBlock* block : blocks) {
            delete block;
        }
        blocks.clear();
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
