#pragma once

#include <memory>
#include <vector>
#include "ResourceManager.h"
#include "GameEngine.h"

class MenuState {
public:
    virtual void draw() = 0;
    virtual void handleInput() = 0;
    virtual ~MenuState() = default;
};

class MainMenuState : public MenuState {
public:
    MainMenuState() = default;
    explicit MainMenuState(class Menu* menu) : menu(menu) {};
    void draw() override {
        DrawText("MAIN MENU", 300, 100, 40, DARKBLUE);
        DrawText("1. Start", 300, 200, 30, BLACK);
        DrawText("2. Settings", 300, 250, 30, BLACK);
    }
    void handleInput() override {
        if (IsKeyPressed(KEY_ONE)) {
            menu->setState(std::make_unique<MenuState>(menu));
        } else if (IsKeyPressed(KEY_TWO)) {
            menu->setState(std::make_unique<MenuState>(menu));
        }
    }

private:
    Menu* menu;
};

class SettingState : public MenuState {
public:
    explicit SettingState(class Menu* menu) : menu(menu), audioEnabled(true), musicEnabled(true) {};
    void draw() override {
        DrawText("SETTINGS", 300, 100, 40, DARKBLUE);
        DrawText(TextFormat("Audio: %s", audioEnabled ? "On" : "Off"), 300, 200, 30, BLACK);
        DrawText(TextFormat("Music: %s", musicEnabled ? "On" : "Off"), 300, 250, 30, BLACK);
        DrawText("Press S to toggle Sound", 300, 300, 20, GRAY);
        DrawText("Press M to toggle Music", 300, 330, 20, GRAY);
        DrawText("Press BACKSPACE to return", 300, 360, 20, GRAY);
    }
    void handleInput() override {
        if (IsKeyPressed(KEY_S)) audioEnabled = !audioEnabled;
        if (IsKeyPressed(KEY_M)) musicEnabled = !musicEnabled;
        if (IsKeyPressed(KEY_BACKSPACE)) menu->setState(std::make_unique<MenuState>(menu));
    }

private:
    Menu* menu;
    bool audioEnabled;
    bool musicEnabled;

};

class CharacterState : public MenuState {
public:
    explicit CharacterState(class Menu* menu) : menu(menu), currentCharacter(0) {};
    void draw() override {
        //Chờ Character
    }
    void handleInput() override {
        //Chờ Character
    }
private:
    Menu* menu;
    int currentCharacter;
};

class MapState : public MenuState {
public:
    explicit MapState(class Menu* menu) : menu(menu), currentMap(0) {};
    void draw() override {
        //Chờ Map
    }
    void handleInput() override {
        //Chờ Map
    }

private:
    Menu* menu;
    int currentMap;
};

class Menu {
public:
    Menu() {
        setState(std::make_unique<MenuState>(this));
    }
    void run() {
        InitWindow(500, 500, "Super Mario 3");
        SetTargetFPS(60);
        while (!WindowShouldClose()) {
            BeginDrawing();
            ClearBackground(WHITE);
            if (currentState) {
                currentState->draw();
                currentState->handleInput();
            }
            EndDrawing();
        }
        CloseWindow();
    }
    
    void setState(std::unique_ptr<MenuState> newState) {
        currentState = std::move(newState);
    }
    void startGame(int currentCharacter, int currentMap) {
        //Chờ handle GameEngine
    }

private:
    std::unique_ptr<MenuState> currentState;
};