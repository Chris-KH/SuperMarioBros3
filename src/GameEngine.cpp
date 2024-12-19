#include "../include/GameEngine.h"

GameCamera::GameCamera(float width, float height, float initialScale)
    : cameraWidth(width), cameraHeight(height), cameraX(0), cameraY(0), scale(initialScale) {}

GameCamera::~GameCamera() {
    UnloadRenderTexture(renderTexture);
}

void GameCamera::loadRenderTexture(Vector2 size)
{
    renderTexture = LoadRenderTexture(size.x, size.y);
}

void GameCamera::update(float characterX, float characterY) {
    float scaledWidth = cameraWidth / scale;
    float scaledHeight = cameraHeight / scale;

    cameraX = characterX - scaledWidth /2;
    cameraY = renderTexture.texture.height - (characterY + cameraHeight / scale) + 100;

    // Clamp the camera to ensure it stays within the map bounds
    if (cameraX < 0) cameraX = 0;
    if (cameraX + scaledWidth > renderTexture.texture.width)
        cameraX = renderTexture.texture.width - scaledWidth;
    if (cameraY < 0) cameraY = 0;
    if (cameraY + scaledHeight > renderTexture.texture.height)
        cameraY = renderTexture.texture.height - scaledHeight;
}

void GameCamera::render() const {
    Rectangle sourceRec = {
        cameraX,
        cameraY,
        cameraWidth / scale,
        -cameraHeight / scale // Negative height to flip vertically
    };

    Rectangle destRec = {
        0, 0,                        // Render starting at the screen's top-left
        (float)GetScreenWidth(),     // Scale to fit the screen width
        (float)GetScreenHeight()     // Scale to fit the screen height
    };

    DrawTexturePro(renderTexture.texture, sourceRec, destRec, Vector2{ 0, 0 }, 0.0f, WHITE);
}

void GameCamera::beginDrawing() {
    BeginTextureMode(renderTexture);
    ClearBackground(RAYWHITE);
}

void GameCamera::endDrawing() {
    EndTextureMode();
}

void GameCamera::setScale(float newScale) {
    scale = newScale;
    if (scale < 0.1f) scale = 0.1f; // Prevent too small scale
}
