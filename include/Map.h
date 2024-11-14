//#pragma once
//
//#include "Entity.h"
//#include "Item.h"
//#include "Enemy.h"
//#include "Hitbox.h"
//#include <vector>
//
//class Map {
//    public:
//    Map();
//
//    ~Map();
//    virtual void fluff() = 0;
//    virtual void background() = 0;
//
//};
//
//class Block : public Map {
//    public:
//    Block(int x, int y, int width, int height) {
//        hitbox.setPosition(x, y);
//        hitbox.setSize(width, height);
//    }
//    /*void render() {
//
//    }
//    void update() {
//
//    }*/
//    Hitbox getHitbox() const {
//        return hitbox;
//    }
//
//    private:
//    Hitbox hitbox;
//    int x, y;
//};
//
//class InteractBlock : public Block {
//    protected:
//    std::vector<Block*> block;
//    std::vector<Item*> item;
//    std::vector<Enemy*> enemy;
//
//    public:
//
//};
//
//class NonInteractBlock : public Block {
//
//};
//
//class NonInteractMoveBlock : public NonInteractBlock {
//
//};
//
//class Lava : public Map {
//    public:
//    Lava(int x, int y, int width, int height) {
//        hitbox.setPosition(x, y);
//        hitbox.setSize(width, height);
//    }
//    /*void render() {
//
//    }
//    void update() {
//
//    }*/
//    Hitbox getHitbox() const {
//        return hitbox;
//    }
//    
//    private:
//    Hitbox hitbox;
//    int x, y;
//
//};
//
//class Pipe : public Map {
//    Pipe(int x, int y, int width, int height) {
//        hitbox.setPosition(x, y);
//        hitbox.setSize(width, height);
//    }
//    /*void render() {
//
//    }
//    void update() {
//
//    }*/
//    Hitbox getHitbox() const {
//        return hitbox;
//    }
//
//    private:
//    Hitbox hitbox;
//    int x, y;
//    
//};
//
