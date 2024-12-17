#pragma once
#include "../lib/raylib.h"
#include <memory>
#include <vector>

// Forward declarations
class MenuState;

// Menu class declaration
class Menu {
public:
    Menu();
    void run();
    void setState(std::unique_ptr<MenuState> newState);

    // Configuration functions for settings, character, and maps
    void configureSettings(bool audioEnabled, bool musicEnabled);
    void selectCharacter(int characterIndex);
    void selectMap(int mapIndex);

private:
    std::unique_ptr<MenuState> currentState;
};

// Base MenuState class
class MenuState {
public:
    virtual void draw() = 0;
    virtual void handleInput() = 0;
    virtual ~MenuState() = default;

protected:
    Menu* menu;
};

// MainMenuState
class MainMenuState : public MenuState {
public:
    explicit MainMenuState(Menu* menu);
    void draw() override;
    void handleInput() override;
};

// SettingState
class SettingState : public MenuState {
public:
    explicit SettingState(Menu* menu);
    void draw() override;
    void handleInput() override;

private:
    bool audioEnabled;
    bool musicEnabled;
};

// CharacterState
class CharSelection : public MenuState {
public:
    explicit CharSelection(Menu* menu);
    void draw() override;
    void handleInput() override;

private:
    int currentCharacter;
};

// MapState
class MapState : public MenuState {
public:
    explicit MapState(Menu* menu);
    void draw() override;
    void handleInput() override;

private:
    int currentMap;
};
