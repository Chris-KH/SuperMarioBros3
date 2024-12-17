#include "../include/Menu.h"
#include <memory>
#include <utility>

// Menu implementation
Menu::Menu() {
    setState(std::make_unique<MainMenuState>(this));
}

void Menu::run() {
    InitWindow(1000, 600, "Super Mario 3");
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

void Menu::setState(std::unique_ptr<MenuState> newState) {
    currentState = std::move(newState);
}

void Menu::configureSettings(bool audioEnabled, bool musicEnabled) {
    // Apply global settings
}

void Menu::selectCharacter(int characterIndex) {
    // Handle character selection
}

void Menu::selectMap(int mapIndex) {
    // Handle map selection
}

// MainMenuState implementation
MainMenuState::MainMenuState(Menu* menu) {
    this->menu = menu;
}

void MainMenuState::draw() {
    DrawText("MAIN MENU", 300, 100, 40, DARKBLUE);
    DrawText("1. Start Game", 300, 200, 30, BLACK);
    DrawText("2. Settings", 300, 250, 30, BLACK);
    DrawText("3. Characters", 300, 300, 30, BLACK);
    DrawText("4. Maps", 300, 350, 30, BLACK);
}

void MainMenuState::handleInput() {
    if (IsKeyPressed(KEY_ONE)) {
        // Start the game
    }
    else if (IsKeyPressed(KEY_TWO)) {
        menu->setState(std::make_unique<SettingState>(menu));
    }
    else if (IsKeyPressed(KEY_THREE)) {
        menu->setState(std::make_unique<CharSelection>(menu));
    }
    else if (IsKeyPressed(KEY_FOUR)) {
        menu->setState(std::make_unique<MapState>(menu));
    }
}

// SettingState implementation
SettingState::SettingState(Menu* menu) : audioEnabled(true), musicEnabled(true) {
    this->menu = menu;
}

void SettingState::draw() {
    DrawText("SETTINGS", 300, 100, 40, DARKBLUE);
    DrawText(TextFormat("Audio: %s", audioEnabled ? "On" : "Off"), 300, 200, 30, BLACK);
    DrawText(TextFormat("Music: %s", musicEnabled ? "On" : "Off"), 300, 250, 30, BLACK);
    DrawText("Press S to toggle Sound", 300, 300, 20, GRAY);
    DrawText("Press M to toggle Music", 300, 330, 20, GRAY);
    DrawText("Press BACKSPACE to return", 300, 360, 20, GRAY);
}

void SettingState::handleInput() {
    if (IsKeyPressed(KEY_S)) audioEnabled = !audioEnabled;
    if (IsKeyPressed(KEY_M)) musicEnabled = !musicEnabled;
    if (IsKeyPressed(KEY_BACKSPACE)) {
        menu->setState(std::make_unique<MainMenuState>(menu));
    }
    menu->configureSettings(audioEnabled, musicEnabled);
}

// CharacterState implementation
CharSelection::CharSelection(Menu* menu) : currentCharacter(0) {
    this->menu = menu;
}

void CharSelection::draw() {
    DrawText("CHARACTER SELECTION", 300, 100, 40, DARKBLUE);
    DrawText("Press BACKSPACE to return", 300, 360, 20, GRAY);
}

void CharSelection::handleInput() {
    if (IsKeyPressed(KEY_BACKSPACE)) {
        menu->setState(std::make_unique<MainMenuState>(menu));
    }
    // Additional character selection logic
}

// MapState implementation
MapState::MapState(Menu* menu) : currentMap(0) {
    this->menu = menu;
}

void MapState::draw() {
    DrawText("MAP SELECTION", 300, 100, 40, DARKBLUE);
    DrawText("Press BACKSPACE to return", 300, 360, 20, GRAY);
}

void MapState::handleInput() {
    if (IsKeyPressed(KEY_BACKSPACE)) {
        menu->setState(std::make_unique<MainMenuState>(menu));
    }
    // Additional map selection logic
}

int main() {
    Menu menu;
    menu.run();
    return 0;
}