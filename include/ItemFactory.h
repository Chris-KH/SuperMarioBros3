#pragma once
#include"Item.h"
#include"Coin.h"
#include"Mushroom.h"
#include"Flower.h"
#include"Star.h"
class ItemFactory {
public:
    using ItemCreator = std::function<Item* (Vector2, Orientation, int)>;

    static ItemFactory& getInstance() {
        static ItemFactory instance;
        return instance;
    }

    void registerItem(ItemType type, ItemCreator creator) {
        creators[type] = creator;
    }

    Item* createItem(ItemType type, Vector2 pos = { 0.f, 0.f }, Orientation orientation = RIGHT, int subtype = 0) {
        auto it = creators.find(type);
        if (it != creators.end()) {
            return it->second(pos, orientation, subtype);
        }
        return nullptr;
    }

private:
    std::unordered_map<ItemType, ItemCreator> creators;

    ItemFactory() = default;
    ~ItemFactory() = default;

    ItemFactory(const ItemFactory&) = delete;
    ItemFactory& operator=(const ItemFactory&) = delete;
};
inline void registerItems() {
    ItemFactory& factory = ItemFactory::getInstance();

    factory.registerItem(COIN, [](Vector2 pos, Orientation orientation, int subtype) {
        return new Coin(static_cast<CoinType>(subtype), pos);
        });

    factory.registerItem(MUSHROOM, [](Vector2 pos, Orientation orientation, int subtype) {
        return new Mushroom(static_cast<MushroomType>(subtype), pos, orientation);
        });

    factory.registerItem(FLOWER, [](Vector2 pos, Orientation orientation, int subtype) {
        return new Flower(static_cast<FlowerType>(subtype), pos, orientation);
        });

    factory.registerItem(STAR, [](Vector2 pos, Orientation orientation, int subtype) {
        return new Star(static_cast<StarType>(subtype), pos, orientation);
        });

    //factory.registerItem(SUPERLEAF, [](Vector2 pos, Orientation orientation, int subtype) {
    //    return new SuperLeaf(pos, orientation); // No subtype for SuperLeaf
    //    });
}