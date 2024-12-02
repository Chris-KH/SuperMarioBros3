//#pragma once
//
//#include "Block.h"
//#include <vector>
//
//class Map {
//public:
//    Map() {}
//
//    ~Map() {
//        for (std::vector<Block*>::iterator it = blocks.begin(); it != blocks.end(); ++it) {
//            delete *it;
//        }
//    }
//
//    void addBlock(Block* block) {
//        blocks.push_back(block);
//    }
//
//    void saveMap(std::string &filename) {
//        std::ofstream savedFile(filename, std::ios::binary);
//        if (savedFile.is_open()) {
//            size_t numBlocks = blocks.size();
//            savedFile.write(reinterpret_cast<const char*>(&numBlocks), sizeof(numBlocks));
//            for (std::vector<Block*>::iterator it = blocks.begin(); it != blocks.end(); ++it) {
//                (*it)->savetoBinaryFile(savedFile);
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
//                Block* block = new Block(0, 0, 0, 0, normal);
//                block->loadfromBinaryFile(loadedFile);
//                blocks.push_back(block);
//            }
//        }
//    }
//    
//private:
//    std::vector<Block*> blocks;
//};
