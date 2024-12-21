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

void Animation::update(float deltaTime, int beginIndex, int size) {
    if (frames.empty()) return;
    if (beginIndex < 0 || beginIndex >= (int)frames.size()) return;

    int endIndex = 0;

    if (size <= -1) {
        endIndex = (int)frames.size();
    }
    else {
        if (size + beginIndex >= (int)frames.size()) endIndex = (int)frames.size();
        else endIndex = size + beginIndex;
    }

    if (currentFrame < beginIndex) currentFrame = beginIndex;

    frameTimeCounter += deltaTime;

    if (frameTimeCounter >= frames[currentFrame].duration) {
        frameTimeCounter -= frames[currentFrame].duration;
        currentFrame++;

        if (currentFrame >= endIndex) {
            currentFrame = beginIndex;
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

void Animation::render(Vector2 position, const Frame& frame) const {
    Rectangle dest = { position.x, position.y, frame.source.width * scale, frame.source.height * scale };
    Rectangle source = frame.source;

    DrawTexturePro(texture, source, dest, frame.offset, 0.0f, WHITE);
}

void Animation::render(Vector2 position, int frameNumber) const {
    // Get the frame and render it
    const Frame& frame = getFrame(frameNumber);
    render(position, frame);
}

void Animation::reset() {
    currentFrame = 0;
    frameTimeCounter = 0.0f;
}

const Vector2 Animation::getSize() const {
    return { scale * frames[currentFrame].size.x, scale * frames[currentFrame].size.y };
}

void Animation::setScale(float scale) {
    this->scale = scale;
}

float Animation::getAnimationTime() const {
    float time = 0.f;
    for (auto& frame : frames) {
        time += frame.duration;
    }
    return time;
}

Animation* Animation::clone() const {
    Animation* copy = new Animation(texture); // Clone with the same texture
    copy->frames = frames;    // Copy frames
    copy->scale = scale;      // Copy scale
    return copy;
}