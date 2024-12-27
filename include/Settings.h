#ifndef SETTINGS_H
#define SETTINGS_H

template <class T>
class Singleton;

class Settings {
    template <class T>
    friend class Singleton;
private:
    int screenWidth;  //The width of the screen
    int screenHeight; //The height of the screen
    int scale;        //The zoom level for rendering
    bool fullscreen;  //Full screen on/off
    bool sound;       //Sound effects on/off
    bool music;       //Music on/off

    // Constructor to initialize settings with default values
    Settings();
    Settings(const Settings& other) = delete;
    Settings& operator=(const Settings& other) = delete;
public:
    
    ~Settings() = default;

    // Getter for screen width
    int getScreenWidth() const;

    // Setter for screen width
    void setScreenWidth(int width);

    // Getter for screen height
    int getScreenHeight() const;

    // Setter for screen height
    void setScreenHeight(int height);

    // Getter for scale
    int getScale() const;

    // Setter for scale
    void setScale(int newScale);

    // Getter for fullscreen mode
    bool isFullscreen() const;

    // Setter for fullscreen mode
    void setFullscreen(bool isFullscreen);

    // Getter for sound effects
    bool isSoundEnabled() const;

    // Setter for sound effects
    void setSound(bool isEnabled);

    // Getter for music
    bool isMusicEnabled() const;

    // Setter for music
    void setMusic(bool isEnabled);

    // Method to reset settings to default values
    void resetToDefaults();
};
#endif