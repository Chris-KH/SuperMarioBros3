#pragma once

#include "Block.h"
#include <vector>

class Map {
public:
   Map() {}

    ~Map() {
        for (BaseBlock* block : blocks) {
            delete block;
        }
    }

    void addBlock(BaseBlock* block) {
        blocks.push_back(block);
    }

    void saveMap(std::string &filename) {
        std::ofstream savedFile(filename, std::ios::binary);
        if (savedFile.is_open()) {
            size_t numBlocks = blocks.size();
            savedFile.write(reinterpret_cast<const char*>(&numBlocks), sizeof(numBlocks));
            for (std::vector<BaseBlock*>::iterator it = blocks.begin(); it != blocks.end(); ++it) {
                //(*it)->savetoBinaryFile(savedFile);
            }
        }
    }

    void loadMap(std::string &filename) {
        std::ifstream loadedFile(filename, std::ios::binary);
        if (loadedFile.is_open()) {
            int numBlocks = 0;
            loadedFile.read(reinterpret_cast<char*>(&numBlocks), sizeof(numBlocks));
            blocks.clear();
            for (int i = 0; i < numBlocks; ++i) {
                //BaseBlock* block = new SolidBlock(0, 0, 0, 0);
                //block->loadfromBinaryFile(loadedFile);
                //blocks.push_back(block);
            }
        }
    }
    
private:
    std::vector<BaseBlock*> blocks;
    BaseBlock* createBlockByType(BlockType blockType) {
        switch (blockType) {
            /*case FLOOR: return new Floor();
            case BRICK: return new Brick();
            case SOLIDBLOCK: return new SolidBlock();
            case MOVINGBLOCK: return new MovingBlock();
            case ITEMBLOCK: return new ItemBlock();
            case HIDDEN: return new HiddenBlock();
            case SPIKE: return new SpikeBlock();
            case PIPE: return new PipeBlock();
            case DECOR: return new DecorBlock();*/
            default: return nullptr;
        }
    }
};
