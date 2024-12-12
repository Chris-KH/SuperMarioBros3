#pragma once
#include "../lib/raylib.h"
#include "../lib/bits/stdc++.h"

using namespace std;

//A class to manage sprite-based animations using Raylib.
class Animation {
public:
    struct Frame {
        Rectangle source; ///< Position and size of the frame in the texture atlas.
        Vector2 offset;   ///< Offset for rendering the frame.
        float duration;   ///< Duration of the frame in seconds.
    };

    Animation() = default;

    //Constructor with texture.
    Animation(const Texture2D& texture);

    //Add a new frame to the animation.
    void addFrame(const Rectangle& source, const Vector2& offset, float duration = 1.f);

    //Get a frame from the animation.
    const Frame& getFrame(int frameNumber) const;

    //Update the animation based on delta time.
    void update(float deltaTime);

    //Render the current frame of the animation.
    void render(Vector2 position) const;
    void render(const Frame& frame) const;
    void render(int frameNumber) const;

    //Reset the animation to the first frame.
    void reset();

    // Check if the animation has finished (useful for one-shot animations).
    bool isFinished() const;

    //Hitbox
    const Vector2& getSize() const;

    void setScale(float scale);

    // **Prototype Pattern: clone method**
    Animation* clone() const;

private:
    const Texture2D& texture; ///< The texture containing the animation frames.
    vector<Frame> frames; ///< List of frames in the animation.
    int currentFrame; ///< Index of the current frame.
    float frameTimeCounter; ///< Time counter for the current frame.
    bool finished; ///< Whether the animation has finished playing.
    float scale;
};

