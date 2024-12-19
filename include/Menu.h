#pragma once
#include "../lib/raylib.h"
#include <memory>
#include <vector>
#include "GameEngine.h"
#include "Mario.h"
#include "Luigi.h"
// Forward declarations
class MenuState;

// Menu class declaration
class Menu {
public:
    Menu();

    void run();
    void setState(std::unique_ptr<MenuState> newState);

    void configureSettings(bool audioEnabled, bool musicEnabled);
    void selectCharacter(int characterIndex);
    void selectMap(int mapIndex);
    void loadBackground(const std::string &filePath);

    // Accessors for settings
    bool isAudioEnabled() const;
    bool isMusicEnabled() const;
    int getSelectedCharacter() const;
    int getSelectedMap() const;

    // State management
    void returnToMainMenu();

    Character* player;
    Map* map;

private:
    bool audioEnabled;
    bool musicEnabled;
    int selectedCharacter;
    int selectedMap;
    std::unique_ptr<MenuState> currentState;
    Texture2D titleScreen;
};

// Base MenuState class
class MenuState {
public:
    virtual void draw() = 0;
    virtual void handleInput() = 0;
    virtual ~MenuState() = default;

    void setMenu(Menu* menu) { this->menu = menu; }

protected:
    Menu* menu;
};

// MainMenuState
class MainMenuState : public MenuState {
public:
    explicit MainMenuState(Menu* menu); // Constructor declaration
    void draw() override;
    void handleInput() override;
private:
    Rectangle startButton{300, 200, 200, 40};
    Rectangle settingsButton{300, 250, 200, 40};
    Rectangle charSelectionButton{300, 300, 200, 40};
    Rectangle mapSelectionButton{300, 350, 200, 40};
};

class SettingState : public MenuState {
public:
    explicit SettingState(Menu* menu);
    void draw() override;
    void handleInput() override;
private:
    Rectangle audioButton{300, 300, 200, 40};
    Rectangle musicButton{300, 350, 200, 40};
    Rectangle backButton{300, 400, 200, 40};
};

class CharSelection : public MenuState {
public:
    explicit CharSelection(Menu* menu);
    void draw() override;
    void handleInput() override;
private:
    Rectangle marioButton{300, 200, 200, 40};
    Rectangle luigiButton{300, 250, 200, 40};
    Rectangle backButton{300, 300, 200, 40};
};

// MapState
class MapSelection : public MenuState {
public:
    explicit MapSelection(Menu* menu);
    void draw() override;
    void handleInput() override;
private:
    Rectangle map1Button{300, 200, 200, 40};
    Rectangle map2Button{300, 250, 200, 40};
    Rectangle map3Button{300, 300, 200, 40};
    Rectangle backButton{300, 350, 200, 40};
};
