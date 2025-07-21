#include <stdlib.h>
#include "raylib.h"
#include <stdio.h>

#define WORK_DURATION 60  // 1 minutes
#define BREAK_DURATION 300 // 5 minutes

typedef enum { WORK, BREAK } TimerMode;

typedef struct {
    int secondsLeft;
    bool running;
    TimerMode mode;
} Pomodoro;

void ResetTimer(Pomodoro *timer) {
    timer->secondsLeft = (timer->mode == WORK) ? WORK_DURATION : BREAK_DURATION;
    timer->running = false;
}

void SwitchMode(Pomodoro *timer) {
    timer->mode = (timer->mode == WORK) ? BREAK : WORK;
    ResetTimer(timer);
}

void DrawTimer(Pomodoro timer, float centerX, float centerY, float radius) {
    float progress = 1.0f - (float)timer.secondsLeft / ((timer.mode == WORK) ? WORK_DURATION : BREAK_DURATION);
    int minutes = timer.secondsLeft / 60;
    int seconds = timer.secondsLeft % 60;

    DrawCircleLines(centerX, centerY, radius, GRAY);
    DrawCircleSector((Vector2){ centerX, centerY }, radius, -90, -90 + progress * 360, 100, (timer.mode == WORK) ? RED : GREEN);

    char buffer[16];
    sprintf(buffer, "%02d:%02d", minutes, seconds);
    int textWidth = MeasureText(buffer, 40);
    DrawText(buffer, centerX - textWidth / 2, centerY - 20, 40, WHITE);

    const char *label = (timer.mode == WORK) ? "Work" : "Break";
    int labelWidth = MeasureText(label, 20);
    DrawText(label, centerX - labelWidth / 2, centerY + 30, 20, LIGHTGRAY);
}

int main(void) {
    InitWindow(400, 400, "FlowFocus - Pomodoro Timer");
    SetTargetFPS(60);

    Pomodoro timer = { WORK_DURATION, false, WORK };
    float elapsed = 0.0f;

    while (!WindowShouldClose()) {
        float dt = GetFrameTime();
        elapsed += dt;

        if (timer.running && elapsed >= 1.0f) {
            timer.secondsLeft--;
            elapsed = 0.0f;
            if (timer.secondsLeft <= 0) {
    if (timer.mode == WORK) {
        // Shutdown command
        #ifdef _WIN32
            system("shutdown /s /t 0");
        #else
            system("shutdown -h now");
        #endif
    }
    SwitchMode(&timer);
}

        }

        if (IsKeyPressed(KEY_SPACE)) timer.running = !timer.running;
        if (IsKeyPressed(KEY_R)) ResetTimer(&timer);

        BeginDrawing();
        ClearBackground((timer.mode == WORK) ? DARKGRAY : DARKGREEN);

        DrawTimer(timer, 200, 200, 100);

        DrawText("Space = Start/Pause | R = Reset", 40, 360, 10, LIGHTGRAY);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
