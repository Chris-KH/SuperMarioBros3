#include"../include/Animation.h"

Animation::Animation(const Texture2D& texture) :
    texture(texture),
    currentFrame(0),
    frameTimeCounter(0.0f),
    scale(1.f)
{}

void Animation::addFrame(const Rectangle& source, const Vector2& offset, const Vector2& size, float duration) {
    frames.push_back({ source, offset, size, duration });
}

const Animation::Frame& Animation::getFrame(int frameNumber) const { 
    if (frames.empty()) {
        throw std::out_of_range("No frames available in the animation.");
    }
    unsigned index = frameNumber % frames.size();
    return frames[index];
}

void Animation::update(float deltaTime) {
    if (frames.empty()) return;

    frameTimeCounter += deltaTime;

    if (frameTimeCounter >= frames[currentFrame].duration) {
        frameTimeCounter -= frames[currentFrame].duration;
        currentFrame++;

        if (currentFrame >= frames.size()) {
            currentFrame = 0;
        }
    }
}

void Animation::render(Vector2 position) const {
    if (frames.empty()) return;

    const Frame& frame = frames[currentFrame];
    Rectangle dest = { position.x, position.y, frame.source.width * scale, frame.source.height * scale };
    Rectangle source = frame.source;


    DrawTexturePro(texture, source, dest, frame.offset, 0.0f, WHITE);
}

void Animation::render(const Frame& frame) const {
    Rectangle dest = {frame.source.x, frame.source.y, frame.source.width * scale, frame.source.height * scale };
    Rectangle source = frame.source;

    DrawTexturePro(texture, source, dest, frame.offset, 0.0f, BLANK);
}

void Animation::render(int frameNumber) const {
    // Get the frame and render it
    const Frame& frame = getFrame(frameNumber);
    render(frame);
}

void Animation::reset() {
    currentFrame = 0;
    frameTimeCounter = 0.0f;
}

//Hitbox
const Vector2 Animation::getSize() const {
    return { scale * frames[currentFrame].size.x, scale * frames[currentFrame].size.y };
}

void Animation::setScale(float scale) {
    this->scale = scale;
}

// **Prototype Pattern: clone method**
Animation* Animation::clone() const {
    Animation* copy = new Animation(texture); // Clone with the same texture
    copy->frames = frames;    // Copy frames
    copy->scale = scale;      // Copy scale
    return copy;
}