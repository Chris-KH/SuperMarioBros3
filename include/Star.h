#ifndef STAR_H
#define STAR_H

#include "Item.h"

class Star : public Item {
private:
    const int POINT = 1000;
    const float SPEED = 70.f;

    StarType type;
    Animation* starAnimation;
public:
    Star(StarType type = YELLOW_STAR, Vector2 position = { 0.f, 0.f }, Orientation orientation = RIGHT);

    void update(float deltaTime) override;

    const StarType& getStarType() const;

    ItemType getItemType() const override;
};

#endif // STAR_H