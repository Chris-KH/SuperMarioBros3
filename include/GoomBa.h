#pragma once
#include "Enemy.h"
#include "Collision.h"

class GoomBa : public Enemy {
private:
    int direction; //xét -1 là bên trái, 1 là bên phải

public:
    //GoomBa(float x, float y, float speed, Color color) : Enemy(x, y, speed, color), direction(-1) {}
    void move(float deltaTime) {
        if (isAlive) {
            x += direction * speed; //xác định trên chiều đi
            //Check collision
            /*if (x <= CheckCollisionBoxes(box 1, box 2) || x >= CheckCollisionBoxes(box 2, box 1)) {
                direction *= -1;
            }*/
        }
    }

    /*void onStomp() override {
        Enemy::onStomp();
    }*/

    void render() const override {
        if (isAlive) {
            std::cout << x << y;
        }
    }
};
