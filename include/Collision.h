#pragma once

//#include"../include/"
class Entity;
class Block;

class ICollisionStrategy {
public:
    virtual bool collides(Entity& entity, const Block& block) = 0;
    virtual ~ICollisionStrategy() = default;
};
class EntityToBlockPushbackCollision : public ICollisionStrategy {
public:
    bool collides(Entity& entity, const Block& block) override;
};
class EntityToBLockCollision : public ICollisionStrategy
{
public:
    bool collides(Entity& entity, const Block& block) override;
};