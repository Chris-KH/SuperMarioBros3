#include"../include/FPSManager.h"

// Constructor to initialize the desired frames per second (FPS)
FPSManager::FPSManager(int fps) : targetFps(fps), frameCounter(0), lastTickTime(chrono::high_resolution_clock::now()) {
    SetTargetFPS(targetFps); // Set the target FPS for the application
}

// Get the desired frame rate
int FPSManager::getDesiredFrameRate() const {
    return targetFps;
}

// Get the current frame rate using Raylib's GetFPS function
int FPSManager::getFrameRate() const {
    return GetFPS();
}

// Update the FPS manager and control the frame timing
bool FPSManager::update() {
    frameCounter++; // Increment the frame counter
    auto currentTime = chrono::high_resolution_clock::now();
    auto elapsedTime = chrono::duration_cast<chrono::milliseconds>(currentTime - lastTickTime).count();

    // Check if we need to delay to maintain the desired FPS
    if (elapsedTime < (1000 / targetFps)) {
        return false; // Frame was skipped
    }

    lastTickTime = currentTime; // Update the last tick time for the next frame
    return true; // Frame was processed
}