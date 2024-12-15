#pragma once
#include"raylib.h"
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
    // void selectMap(int mapIndex);

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
};

class SettingState : public MenuState {
public:
    explicit SettingState(Menu* menu);
    void draw() override;
    void handleInput() override;
};

class CharSelection : public MenuState {
public:
    explicit CharSelection(Menu* menu);
    void draw() override;
    void handleInput() override;
};

// MapState
class MapSelection : public MenuState {
public:
    explicit MapSelection(Menu* menu);
    void draw() override;
    void handleInput() override;
};
