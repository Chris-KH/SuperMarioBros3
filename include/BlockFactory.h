#ifndef BLOCKFAC_H
#define BLOCKFAC_H
#include <unordered_map>
#include <functional>
#include "BaseBlock.h"
#include "Floor.h"
#include "ItemBlock.h"
#include "MovingBlock.h"
#include "SolidBlock.h"
#include "HiddenBlock.h"
#include "PipeBlock.h"
#include "SpikeBlock.h"
#include "Brick.h"
#include "TemporaryBlock.h"
#include "DecorBlock.h"


class BlockFactory {
public:
    using BlockCreator = std::function<BaseBlock* (Vector2, Vector2)>;

    static BlockFactory& getInstance() {
        static BlockFactory instance;
        return instance;
    }

    void registerBlock(BlockType type, BlockCreator creator) {
        creators[type] = creator;
    }

    BaseBlock* createBlock(BlockType type, Vector2 pos = { 0, 0 }, Vector2 size = { 1, 1 }) {
        auto it = creators.find(type);
        if (it != creators.end()) {
            return it->second(pos, size);
        }
        return nullptr;
    }

private:
    std::unordered_map<BlockType, BlockCreator> creators;

    BlockFactory() = default;
    ~BlockFactory() = default;

    BlockFactory(const BlockFactory&) = delete;
    BlockFactory& operator=(const BlockFactory&) = delete;
};

inline void registerBlocks() {
    BlockFactory& factory = BlockFactory::getInstance();

    factory.registerBlock(FLOOR, [](Vector2 pos, Vector2 size) {
        return new Floor(pos, size);
        });

    factory.registerBlock(BRICK, [](Vector2 pos, Vector2 size) {
        return new Brick(pos, size);
        });

    factory.registerBlock(SOLIDBLOCK, [](Vector2 pos, Vector2 size) {
        return new SolidBlock(pos, size);
        });

    factory.registerBlock(MOVINGBLOCK, [](Vector2 pos, Vector2 size) {
        return new MovingBlock(pos, size);
        });

    factory.registerBlock(ITEMBLOCK, [](Vector2 pos, Vector2 size) {
        return new ItemBlock(pos, size);
        });

    factory.registerBlock(HIDDEN, [](Vector2 pos, Vector2 size) {
        return new HiddenBlock(pos, size);
        });

    factory.registerBlock(SPIKE, [](Vector2 pos, Vector2 size) {
        return new SpikeBlock(pos, size);
        });

    factory.registerBlock(PIPE, [](Vector2 pos, Vector2 size) {
        return new PipeBlock(pos, size);
        });

    factory.registerBlock(DECOR, [](Vector2 pos, Vector2 size) {
        return new DecorBlock(pos, size);
        });

    factory.registerBlock(TEMPBLOCK, [](Vector2 pos, Vector2 size) {
        return new TemporaryBlock(pos, size);
        });
}
//BlockFactory& factory = BlockFactory::getInstance();
// blocks.push_back(factory.createBlock(FLOOR, {10, 10}, {50, 50}, GREEN));
//BaseBlock* block = BlockFactory::getInstance().createBlock( blockType, { x, y }, { width, height });
#endif