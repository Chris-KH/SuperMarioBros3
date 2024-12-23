#pragma once
#include "C:/Users/Dell/Downloads/CS202-SuperMario/lib/raylib.h"
#include <chrono>

using namespace std;

class FPSManager {
public:
    // Constructor to initialize the desired frames per second (FPS)
    FPSManager(int fps);

    // Get the desired frame rate
    int getDesiredFrameRate() const;

    // Get the current frame rate using Raylib's GetFPS function
    int getFrameRate() const;

    // Update the FPS manager and control the frame timing
    bool update();

private:
    int targetFps; // Desired frames per second
    unsigned frameCounter; // Count of frames processed
    chrono::high_resolution_clock::time_point lastTickTime; // Time of the last processed frame
};

