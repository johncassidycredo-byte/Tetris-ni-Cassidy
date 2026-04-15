#include <raylib.h>
#include "game.h"
#include "colors.h"
#include <iostream>

double lastUpdateTime = 0;

// 🔥 Power-up system
double dropSpeed = 0.2;

bool power300 = false;
bool power600 = false;
bool power1000 = false;

bool doubleScoreActive = false;

bool EventTriggered(double interval)
{
    double currentTime = GetTime();
    if (currentTime - lastUpdateTime >= interval)
    {
        lastUpdateTime = currentTime;
        return true;
    }
    return false;
}

int main()
{
    InitWindow(500, 620, "Credo ni Tetris");
    SetTargetFPS(60);

    Font font = LoadFontEx("Font/monogram.ttf", 64, 0, 0);

    Game game = Game();

    while (WindowShouldClose() == false)
    {
        UpdateMusicStream(game.music);
        game.HandleInput();

        // ⚡ 300 - Speed Boost
        if (game.score >= 300 && !power300)
        {
            power300 = true;
            dropSpeed = 0.1;
        }

        // 💥 600 - BONUS SCORE (no error now)
        if (game.score >= 600 && !power600)
        {
            power600 = true;
            game.score += 200;
        }

        // 🎯 1000 - Double Score
        if (game.score >= 1000 && !power1000)
        {
            power1000 = true;
            doubleScoreActive = true;
        }

        if (EventTriggered(dropSpeed))
        {
            game.MoveBlockDown();
        }

        BeginDrawing();
        ClearBackground(darkBlue);

        DrawTextEx(font, "Score", {365, 15}, 38, 2, WHITE);
        DrawTextEx(font, "Next", {370, 175}, 38, 2, WHITE);

        if (game.gameOver)
        {
            DrawTextEx(font, "GAME OVER", {320, 450}, 38, 2, WHITE);
        }

        // ✨ Power-up text
        if (power300)
            DrawTextEx(font, "SPEED UP!", {320, 350}, 25, 2, GREEN);

        if (power600)
            DrawTextEx(font, "BONUS +200!", {300, 390}, 25, 2, ORANGE);

        if (power1000)
            DrawTextEx(font, "DOUBLE SCORE!", {280, 430}, 25, 2, YELLOW);

        DrawRectangleRounded({320, 55, 170, 60}, 0.3, 6, lightBlue);

        int displayScore = game.score;
        if (doubleScoreActive)
        {
            displayScore = game.score * 2;
        }

        char scoreText[10];
        sprintf(scoreText, "%d", displayScore);

        Vector2 textSize = MeasureTextEx(font, scoreText, 38, 2);

        DrawTextEx(font, scoreText,
                   {320 + (170 - textSize.x) / 2, 65},
                   38, 2, WHITE);

        DrawRectangleRounded({320, 215, 170, 180}, 0.3, 6, lightBlue);

        game.Draw();

        EndDrawing();
    }

    CloseWindow();
}