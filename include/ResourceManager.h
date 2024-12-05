#pragma once
#include <raylib.h>
#include "raylib.h"
#include <map>
#include <string>

using namespace std;

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
    enum ResourceType {
        RESOURCE_ANIMATION,
        RESOURCE_BACKGROUND,
        RESOURCE_FONT,
        RESOURCE_LEVELTHEME,
        RESOURCE_MUSIC,
        RESOURCE_SOUND
    };

    struct Resource {
        ResourceType type;
        union {
            Animation* animation;
            Background* background;
            Font* font;
            //LevelTheme* levelTheme;
            Music* music;
            Sound* sound;
        };
    };

    map<string, Resource> resources;
    map<string, ResourceManager*> groups;

    const Resource* getResource(const string& name) const;
    void loadAnimation();  // Load animation resources
    void loadBackground(); // Load background resources
    void loadFont();      // Load font resources
    void loadMusic();     // Load music resources
    void loadSound();     // Load sound effect resources
public:
    ResourceManager();     // Constructor
    ~ResourceManager();    // Destructor

    // Retrieve an Animation resource
    const Animation* getAnimation(const string& name) const; 

    // Retrieve a Background resource
    const Background* getBackground(const string& name) const; 

    const Music* getMusic(const string& name) const;

    const Sound* getSound(const string& name) const;

    // Get loading progress of resources
    int getLoadingProgress() const; 

    // Load resources from a specified file
    void loadResources(const string& resourceFileName); 

    // Play a music track
    void playMusic(const string& trackName, bool loop) const; 

    // Play a sound effect
    void playSound(const string& soundName, int channel = -1) const; 
};