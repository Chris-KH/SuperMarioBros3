#pragma once
#include "../lib/raylib.h"
#include <map>
#include <string>
#include <filesystem>
#include <iostream>
#include <memory>

using namespace std;
namespace fs = std::filesystem;

class Animation;

/*
 * ResourceManager class handles the loading and management of game resources,
 * including animations, backgrounds, fonts, music, and sound effects.
 * It provides methods to load resources from a file, retrieve specific resources,
 * bind texture atlases, and play audio tracks.
*/
class ResourceManager {
private:
    map<string, unique_ptr<Animation>> animationResource;
    map<string, unique_ptr<Font>> fontResource;
    map<string, unique_ptr<Music>> musicResource;
    map<string, unique_ptr<Sound>> soundResource;

    map<string, Texture2D> textures;
    mutable string currentTrack;
    void loadTextures();
    void loadAnimationFromFile(const string& filePath, const string& fileName);
    void loadAnimation();  // Load animation resources
    void loadFont();      // Load font resources
    void loadMusic();     // Load music resources
    void loadSound();     // Load sound effect resources

    void unloadAnimation();
    void unloadFonts();
    void unloadSounds();
    void unloadMusic();
    void unloadTexture();

public:
    ResourceManager();     // Constructor
    ~ResourceManager();    // Destructor

    void loadAllResource();

    Animation* getAnimation(const string& name) const; 

    const Music* getMusic(const string& name) const;

    const Sound* getSound(const string& name) const;

    Font* getFont(const string& name) const;

    const Texture2D& getTexture(const string& name) const;

    // Play a music track
    void playMusic(const string& trackName) const; 
    bool isMusicPlaying(const string& musicName) const;
    void stopMusic(const string& musicName) const;
    void stopCurrentMusic() const;
    // Play a sound effect
    void playSound(const string& soundName) const; 
    bool isSoundPlaying(const string& soundName) const;
    void stopSound(const string& soundName) const;
    bool ends_with(const std::string &str, const std::string &suffix) {
        return str.size() >= suffix.size() && str.compare(str.size() - suffix.size(), suffix.size(), suffix) == 0;
    }
};
