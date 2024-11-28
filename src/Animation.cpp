#include"../include/Animation.h"

Animation::Animation():
    texture({ 0 }), 
    currentFrame(0), 
    frameTimeCounter(0.0f), 
    finished(false) 
{}

Animation::Animation(Texture2D texture) :
    texture(texture),
    currentFrame(0),
    frameTimeCounter(0.0f),
    finished(false)
{}

void Animation::addFrame(const Rectangle& source, const Vector2& offset, unsigned duration) {
    frames.push_back({ source, offset, duration });
}

const Animation::Frame& Animation::getFrame(int frameNumber) const { 
    if (frames.empty()) {
        throw std::out_of_range("No frames available in the animation.");
    }
    unsigned index = frameNumber % frames.size();
    return frames[index];
}

void Animation::update(float deltaTime) {
    if (frames.empty() || finished) return;

    frameTimeCounter += deltaTime;

    if (frameTimeCounter >= frames[currentFrame].duration)
    {
        frameTimeCounter -= frames[currentFrame].duration;
        currentFrame++;

        if (currentFrame >= frames.size())
        {
            currentFrame = 0;
            finished = true; // Set finished for one-shot animations.
        }
    }
}

void Animation::render(Vector2 position, bool mirrorX, bool mirrorY, float scale) const {
    if (frames.empty()) return;

    const Frame& frame = frames[currentFrame];
    Rectangle dest = { position.x, position.y, frame.source.width * scale, frame.source.height * scale };
    Rectangle source = frame.source;

    // Handle mirroring.
    if (mirrorX) source.width *= -1;
    if (mirrorY) source.height *= -1;

    DrawTexturePro(texture, source, dest, frame.offset, 0.0f, WHITE);
}

void Animation::render(const Frame& frame, bool mirrorX, bool mirrorY, float scale) const {
    Rectangle dest = {frame.source.x, frame.source.y, frame.source.width * scale, frame.source.height * scale };
    Rectangle source = frame.source;

    // Handle mirroring.
    if (mirrorX) source.width *= -1;
    if (mirrorY) source.height *= -1;

    DrawTexturePro(texture, source, dest, frame.offset, 0.0f, WHITE);
}

void Animation::render(int frameNumber, bool mirrorX, bool mirrorY, float scale) const {
    // Get the frame and render it
    const Frame& frame = getFrame(frameNumber);
    render(frame, mirrorX, mirrorY, scale);
}

void Animation::reset() {
    currentFrame = 0;
    frameTimeCounter = 0.0f;
    finished = false;
}

bool Animation::isFinished() const {
    return finished;
}
