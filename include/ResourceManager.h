#pragma once
#include <raylib.h>
#include "raylib.h"
#include <map>
#include <string>
#include <filesystem>
#include <iostream>
#include <memory>

using namespace std;
namespace fs = std::filesystem;

class Animation;
class Background;

/*
 * ResourceManager class handles the loading and management of game resources,
 * including animations, backgrounds, fonts, music, and sound effects.
 * It provides methods to load resources from a file, retrieve specific resources,
 * bind texture atlases, and play audio tracks.
*/
class ResourceManager {
private:
    map<string, unique_ptr<Animation>> animationResource;
    map<string, unique_ptr<Background>> backgroundResource;
    map<string, unique_ptr<Font>> fontResource;
    map<string, unique_ptr<Music>> musicResource;
    map<string, unique_ptr<Sound>> soundResource;

    void loadAnimation();  // Load animation resources
    void loadBackground(); // Load background resources
    void loadFont();      // Load font resources
    void loadMusic();     // Load music resources
    void loadSound();     // Load sound effect resources

    void unloadFonts();
    void unloadSounds();
    void unloadMusic();

public:
    ResourceManager();     // Constructor
    ~ResourceManager();    // Destructor

    void loadAllResource();

    const Animation& getAnimation(const string& name) const; 

    const Background& getBackground(const string& name) const; 

    const Music& getMusic(const string& name) const;

    const Sound& getSound(const string& name) const;

    const Font& getFont(const string& name) const;

    // Play a music track
    void playMusic(const string& trackName) const; 

    // Play a sound effect
    void playSound(const string& soundName) const; 
};



