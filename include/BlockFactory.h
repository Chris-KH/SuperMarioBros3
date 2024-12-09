#pragma once
#include <unordered_map>
#include <functional>
#include "Block.h"

// Factory class to create blocks dynamically
class BlockFactory {
public:
    using BlockCreator = std::function<BaseBlock* (Vector2, Vector2, Color)>;

    // Singleton instance of BlockFactory
    static BlockFactory& getInstance() {
        static BlockFactory instance;
        return instance;
    }

    // Register a block type with its creation function
    void registerBlock(BlockType type, BlockCreator creator) {
        creators[type] = creator;
    }

    // Create a block instance based on BlockType
    BaseBlock* createBlock(BlockType type, Vector2 pos = { 0, 0 }, Vector2 size = { 1, 1 }, Color color = ORANGE) {
        auto it = creators.find(type);
        if (it != creators.end()) {
            return it->second(pos, size, color);
        }
        return nullptr; // Return nullptr if type is not registered
    }

private:
    std::unordered_map<BlockType, BlockCreator> creators;

    BlockFactory() = default;
    ~BlockFactory() = default;

    BlockFactory(const BlockFactory&) = delete;
    BlockFactory& operator=(const BlockFactory&) = delete;
};

void registerBlocks() {
    BlockFactory& factory = BlockFactory::getInstance();

    factory.registerBlock(FLOOR, [](Vector2 pos, Vector2 size, Color color) {
        return new Floor(pos, size, color);
        });

    factory.registerBlock(BRICK, [](Vector2 pos, Vector2 size, Color color) {
        return new Brick(pos, size, color);
        });

    factory.registerBlock(SOLIDBLOCK, [](Vector2 pos, Vector2 size, Color color) {
        return new SolidBlock(pos, size, color);
        });

    factory.registerBlock(MOVINGBLOCK, [](Vector2 pos, Vector2 size, Color color) {
        return new MovingBlock(pos, size, color);
        });

    factory.registerBlock(ITEMBLOCK, [](Vector2 pos, Vector2 size, Color color) {
        return new ItemBlock(pos, size, color);
        });

    factory.registerBlock(HIDDEN, [](Vector2 pos, Vector2 size, Color color) {
        return new HiddenBlock(pos, size, color);
        });

    factory.registerBlock(SPIKE, [](Vector2 pos, Vector2 size, Color color) {
        return new SpikeBlock(pos, size, color);
        });

    factory.registerBlock(PIPE, [](Vector2 pos, Vector2 size, Color color) {
        return new PipeBlock(pos, size, color);
        });

    factory.registerBlock(DECOR, [](Vector2 pos, Vector2 size, Color color) {
        return new DecorBlock(pos, size, color);
        });

    factory.registerBlock(TEMPBLOCK, [](Vector2 pos, Vector2 size, Color color) {
        return new TemporaryBlock(pos, size, color);
        });
}
//BlockFactory& factory = BlockFactory::getInstance();
// blocks.push_back(factory.createBlock(FLOOR, {10, 10}, {50, 50}, GREEN));
//BaseBlock* block = BlockFactory::getInstance().createBlock( blockType, { x, y }, { width, height });