#ifndef STAR_H
#define STAR_H

#include "Item.h"

class Star : public Item {
private:
    static constexpr int POINT = 1000;
    static constexpr float SPEED = 70.f;

    StarType type;
    Animation* starAnimation;

    static constexpr float APPEAR_SPEED = 16.f;
public:
    Star(StarType type = YELLOW_STAR, Vector2 position = { 0.f, 0.f }, Orientation orientation = RIGHT);

    void update(float deltaTime) override;

    const StarType& getStarType() const;

    ItemType getItemType() const override;
};

#endif // STAR_H