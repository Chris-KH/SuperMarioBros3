#include"../include/GUI.h"
#include"../include/Character.h"
#include "../include/GameEngine.h"

Texture2D GUI::heartTexture;
Texture2D GUI::coinTexture;
Texture2D GUI::multiplicationSign;
Texture2D GUI::board;


void GUI::drawStatusBar(const Character* player) {
    Rectangle dest, source;

    //Draw board
    dest = { 1621.f, 1949.f, 1138.f, 397.f };
    source = { 20.f, 20.f, 1138.f / 4.f, 397.f / 4.f };
    DrawTexturePro(board, dest, source, { 0.f, 0.f }, 0.f, WHITE);
    source = { 20.f, 120.f, 1138.f / 4.f, 397.f / 4.f };
    DrawTexturePro(board, dest, source, { 0.f, 0.f }, 0.f, WHITE);
    source = { 490.f, 120.f, 1138.f / 4.f, 397.f / 4.f };
    DrawTexturePro(board, dest, source, { 0.f, 0.f }, 0.f, WHITE);

    dest = { 28.f, 1934.f, 1571.f, 421.f };
    source = { 440.f, 20.f, 1571.f / 4.f, 421.f / 4.f };
    DrawTexturePro(board, dest, source, { 0.f, 0.f }, 0.f, WHITE);
    //

    //Draw heart
    dest = { 0, 0, (float)heartTexture.width, (float)heartTexture.height };
    source = { 55.f, 45.f, 40.f, 40.f };
    DrawTexturePro(heartTexture, dest, source, { 0.f, 0.f }, 0.f, WHITE);
    DrawText(to_string(player->getLives()).c_str(), 130, 45, 40, BLACK);
    //

    //Draw Coin
    dest = { 0, 0, (float)coinTexture.width, (float)coinTexture.height };
    source = { 55.f, 145.f, 40.f, 40.f };
    DrawTexturePro(coinTexture, dest, source, { 0.f, 0.f }, 0.f, WHITE);
    DrawText(to_string(player->getCoins()).c_str(), 130, 145, 40, BLACK);
    //

    //Draw X sign
    dest = { 0, 0, (float)multiplicationSign.width, (float)multiplicationSign.height };
    source = { 100.f, 55.f, 20.f, 20.f };
    DrawTexturePro(multiplicationSign, dest, source, { 0.f, 0.f }, 0.f, WHITE);

    source = { 100.f, 155.f, 20.f, 20.f };
    DrawTexturePro(multiplicationSign, dest, source, { 0.f, 0.f }, 0.f, WHITE);
    //

    DrawText(to_string(player->getScores()).c_str(), 440.f + 1571.f / 8.f - MeasureTextEx(GetFontDefault(), to_string(player->getScores()).c_str(), 45.f, 0.f).x / 2.f, 45, 45, BLACK);
    int timer = floor((globalGameEngine->getRemainingTime()));
    DrawText(to_string(timer).c_str(), 440.f + 1571.f / 8.f - MeasureTextEx(GetFontDefault(), to_string(timer).c_str(), 45.f, 0.f).x / 2.f, 145, 45, BLACK);
}

void GUI::drawPauseMenu()
{
    Rectangle dest, source;
    dest = { 2043.f, 295.f, 1997.f, 1465.f };
    source = { 300.f, 200.f, 1997.f / 3.f, 1465.f / 3.f };
    DrawTexturePro(board, dest, source, { 0.f, 0.f }, 0.f, WHITE);
    DrawText("PAUSED", 460, 370, 90, BLACK);
}

void GUI::drawLevelClear()
{
    Rectangle dest, source;
    dest = { 2043.f, 295.f, 1997.f, 1465.f };
    source = { 300.f, 200.f, 1997.f / 3.f, 1465.f / 3.f };
    DrawTexturePro(board, dest, source, { 0.f, 0.f }, 0.f, WHITE);
    DrawText("CLEARED", 440, 370, 90, BLACK);
    DrawText("Press Enter to continue", 360, 550, 45, BLACK);
}

void GUI::drawDeathScreen()
{
    const char* text = "YOU DIED";
    int fontSize = 90;
    int screenWidth = 1280;
    int screenHeight = 800;

    int textWidth = MeasureText(text, fontSize);
    int textHeight = fontSize;

    int posX = (screenWidth - textWidth) / 2;
    int posY = (screenHeight - textHeight) / 2;

    DrawText(text, posX, posY, fontSize, RED);
}
