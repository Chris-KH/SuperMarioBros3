#include "Entity.h"

//For moving object
class Sprite : public Entity {
protected:
    Vector2 velocity;      // Velocity vector (dx, dy)
    Vector2 acceleration;  // Acceleration vector (ax, ay)
    Vector2 maxSpeed;      // Maximum speed (x, y)
    bool isDead;           // Indicates if the sprite is "dead"
    bool isFlipped;        // Flip sprite horizontally

public:
    Sprite();
    Sprite(Vector2 pos = { 0, 0 }, Vector2 size = { 1, 1 }, Color color = Color(255, 255, 255, 255));
    Sprite(const Sprite& other);

    virtual ~Sprite() = default;

    // Movement and physics methods
    Vector2 getVelocity() const;
    void setVelocity(Vector2 vel);

    Vector2 getAcceleration() const;
    void setAcceleration(Vector2 acc);

    Vector2 getMaxSpeed() const;
    void setMaxSpeed(Vector2 max);

    void update(float deltaTime);

    // Flip sprite horizontally
    void flip(bool flip);

    // Draw method override
    virtual void draw() const override;
};