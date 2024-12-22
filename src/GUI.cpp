#include"../include/GUI.h"
#include"../include/Character.h"

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

    dest = { 28.f, 1934.f, 1571.f, 421.f };
    source = { 430.f, 20.f, 1571.f / 4.f, 421.f / 4.f };
    DrawTexturePro(board, dest, source, { 0.f, 0.f }, 0.f, WHITE);
    //

    //Draw heart
    dest = { 0, 0, (float)heartTexture.width, (float)heartTexture.height };
    source = { 50.f, 45.f, 40.f, 40.f };
    DrawTexturePro(heartTexture, dest, source, { 0.f, 0.f }, 0.f, WHITE);
    DrawText(to_string(player->getLives()).c_str(), 125, 45, 40, BLACK);
    //

    //Draw Coin
    dest = { 0, 0, (float)coinTexture.width, (float)coinTexture.height };
    source = { 50.f, 145.f, 40.f, 40.f };
    DrawTexturePro(coinTexture, dest, source, { 0.f, 0.f }, 0.f, WHITE);
    DrawText(to_string(player->getCoins()).c_str(), 125, 145, 40, BLACK);
    //

    //Draw X sign
    dest = { 0, 0, (float)multiplicationSign.width, (float)multiplicationSign.height };
    source = { 95.f, 55.f, 20.f, 20.f };
    DrawTexturePro(multiplicationSign, dest, source, { 0.f, 0.f }, 0.f, WHITE);

    source = { 95.f, 155.f, 20.f, 20.f };
    DrawTexturePro(multiplicationSign, dest, source, { 0.f, 0.f }, 0.f, WHITE);
    //

    DrawText(to_string(player->getScores()).c_str(), 430.f + 1571.f / 8.f - MeasureTextEx(GetFontDefault(), to_string(player->getScores()).c_str(), 45, 0.f).x / 2.f, 45, 45, BLACK);
}