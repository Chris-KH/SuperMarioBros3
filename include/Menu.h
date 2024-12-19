#pragma once
#include "raylib.h"
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
    ~Menu(); 
    void run();
    void setState(std::unique_ptr<MenuState> newState);

    void configureSettings(bool audioEnabled, bool musicEnabled);
    void selectCharacter(int characterIndex);
    void selectMap(int mapIndex);
    bool isAudioEnabled() const;
    bool isMusicEnabled() const;
    int getSelectedCharacter() const;
    int getSelectedMap() const;

    void returnToMainMenu();
    void setBackground(const std::string& imagePath);
    Character* player;
    Level* map;

private:
    vector<Level*> loadedLevel;
    bool audioEnabled;
    bool musicEnabled;
    int selectedCharacter;
    int selectedMap;
    std::unique_ptr<MenuState> currentState;
    Texture2D backgroundTexture;
};

class MenuState {
public:
    virtual void draw() = 0;
    virtual void handleInput() = 0;
    virtual ~MenuState() = default;

    void setMenu(Menu* menu) { this->menu = menu; }

protected:
    Menu* menu;
};

class MainMenuState : public MenuState {
public:
    explicit MainMenuState(Menu* menu); // Constructor declaration
    void draw() override;
    void handleInput() override;
private:
    Rectangle startButton;
    Rectangle continueButton;
    Rectangle settingsButton;
    Rectangle charSelectionButton;
    Rectangle mapSelectionButton;
};

class SettingState : public MenuState {
public:
    explicit SettingState(Menu* menu);
    void draw() override;
    void handleInput() override;
private:
    Rectangle audioButton{ 155, 720, 300, 40 };
    Rectangle musicButton{ 515, 720, 300, 40 };
    Rectangle backButton{ 895, 720, 300, 40 };
};

class CharSelection : public MenuState {
public:
    explicit CharSelection(Menu* menu);
    void draw() override;
    void handleInput() override;
private:
    Rectangle marioButton = { 170, 720, 150, 40 };  
    Rectangle luigiButton = { 540, 720, 150, 40 };
    Rectangle backButton = { 910, 720, 300, 40 };
};

// MapState
class MapSelection : public MenuState {
public:
    explicit MapSelection(Menu* menu);
    void draw() override;
    void handleInput() override;
private:
    Rectangle map1Button = { 170, 720, 150, 40 };
    Rectangle map2Button = { 540, 720, 150, 40 }; 
    Rectangle map3Button = { 910, 720, 150, 40 };
    //Rectangle backButton = { 1040, 720, 150, 40 }; 

};
