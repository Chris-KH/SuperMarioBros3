#pragma once
#include <iostream>
#include <raylib.h>
#include "Map.h"
#include "Block.h"
#include "Entity.h"
class GameCamera {
public:
    float cameraX;          // GameCamera position on the X-axis
    float cameraY;          // GameCamera position on the Y-axis
    float cameraWidth;      // Width of the camera view
    float cameraHeight;     // Height of the camera view

    RenderTexture2D renderTexture; // Off-screen render texture

    GameCamera(float width, float height, int mapWidth, int mapHeight)
        : cameraWidth(width), cameraHeight(height), cameraX(0), cameraY(0) {
        renderTexture = LoadRenderTexture(mapWidth, mapHeight);
    }

    ~GameCamera() {
        UnloadRenderTexture(renderTexture);
    }

    void update(float characterX, float characterY) {
        // Calculate the offset needed to center the camera on the character
        cameraX = characterX - cameraWidth / 2;
        cameraY = characterY - cameraHeight / 2;

        //    // Optional: Clamp the camera position so it doesn't go out of map bounds
        //    if (cameraX < 0) cameraX = 0;
        //    if (cameraY < 0) cameraY = 0;
        //    if (cameraX + cameraWidth > renderTexture.texture.width) {
        //        cameraX = renderTexture.texture.width - cameraWidth;
        //    }
        //    if (cameraY + cameraHeight > renderTexture.texture.height) {
        //        cameraY = renderTexture.texture.height - cameraHeight;
        //    }
        //
    }

    // Draw the current view to the screen
    void render() const {
        // Calculate source and destination rectangles for drawing
        Rectangle sourceRec = { cameraX, cameraY, cameraWidth, cameraHeight };
        Rectangle destRec = { 0, 0, (float)GetScreenWidth(), (float)GetScreenHeight() };

        // Draw the relevant section of the render texture to the window
        DrawTexturePro(renderTexture.texture, sourceRec, destRec, Vector2{ 0, 0 }, 0.0f, WHITE);
    }

    // Begin drawing to the off-screen texture
    void beginDrawing() {
        BeginTextureMode(renderTexture);
        ClearBackground(RAYWHITE);
    }

    // End drawing to the off-screen texture
    void endDrawing() {
        EndTextureMode();
    }
};

class Chunk {
public:
    int x;                     // Chunk grid position (horizontal only)
    bool isLoaded;             // Whether this chunk is loaded
    std::vector<Block*> blocks; // Blocks belonging to this chunk

    Chunk(int x) : x(x), isLoaded(false) {}

    void load() {
        isLoaded = true;
    }

    void unload() {
        isLoaded = false;
        blocks.clear();
    }

    void render() const {
        if (isLoaded) {
            for (const auto& block : blocks) {
                block->render();
            }
        }
    }
};
class GameEngine {
private:
    //Map map;
    std::vector<Chunk> chunks; // Horizontal chunks
    int chunkSize;             // Size of each chunk in pixels
    GameCamera camera;
    float characterX;

public:
    GameEngine(float screenWidth, float screenHeight, float mapWidth, float mapHeight, int chunkSize)
        : /*map(mapWidth, mapHeight)*/ 
        camera(screenWidth, screenHeight, mapWidth, screenHeight), chunkSize(chunkSize),
        characterX(500) {
        int numChunks = mapWidth / chunkSize;
        chunks.reserve(numChunks);
        for (int i = 0; i < numChunks; ++i) {
            chunks.emplace_back(i);
        }
    }
    // implement later
   /* void loadMap(const std::string& filePath) {
        map.loadFromFile(filePath);

        // Assign blocks to chunks
        for (auto& block : map.getBlocks()) {
            int blockChunk = block.getPos().first / chunkSize;
            if (blockChunk >= 0 && blockChunk < chunks.size()) {
                chunks[blockChunk].blocks.push_back(&block);
            }
        }
    }*/

    void update() {
        // Simulate character movement
        if (IsKeyDown(KEY_RIGHT)) characterX += 2;
        if (IsKeyDown(KEY_LEFT)) characterX -= 2;

        // Determine the character's current chunk
        int currentChunk = characterX / chunkSize;

        // Update active chunks
        updateChunks(currentChunk);

        // Update camera
        camera.update(characterX, 0);
    }

    void updateChunks(int characterChunk) {
        // Load and keep chunks within range
        for (int i = characterChunk - 1; i <= characterChunk + 1; ++i) {
            if (i >= 0 && i < chunks.size() && !chunks[i].isLoaded) {
                chunks[i].load();
            }
        }

        // Unload chunks outside the range
        for (int i = 0; i < chunks.size(); ++i) {
            if (chunks[i].isLoaded && (i < characterChunk - 1 || i > characterChunk + 1)) {
                chunks[i].unload();
            }
        }
    }

    void render() {
        camera.beginDrawing();

        // Render active chunks
        for (const auto& chunk : chunks) {
            chunk.render();
        }

        // Render character
        DrawRectangle(characterX - 10, 500 - 10, 20, 20, RED);

        camera.endDrawing();

        BeginDrawing();
        ClearBackground(RAYWHITE);
        camera.render();
        EndDrawing();
    }

    void run() {
        while (!WindowShouldClose()) {
            update();
            render();
        }
    }
};


