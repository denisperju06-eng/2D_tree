#include "raylib.h"
#include <math.h>

const int MAX_STEPS = 14;
int currentSteps = 3;

// Funcție recursivă pentru a desena copacul
void DrawBranch(Vector2 startPos, float length, float angle, int step, int maxStep) {
    if (step == 0) return;

    Vector2 endPos;
    endPos.x = startPos.x + cos(angle) * length;
    endPos.y = startPos.y + sin(angle) * length;

    // Grosimea scade pe măsură ce avansăm în pași
    float thickness = (step > 1) ? (float)step * 0.8f : 1.0f;
    Color branchColor = { 101, 67, 33, 255 }; // Maro închis

    DrawLineEx(startPos, endPos, thickness, branchColor);

    // Adăugăm frunze la capătul ultimei crengi
    if (step == 1) {
        DrawCircleV(endPos, 4.0f, GREEN);
    }

    // Unghiul de despărțire și factorul de scurtare
    float splitAngle = 0.45f; // ~25 de grade
    float lengthScale = 0.75f;

    // Creăm 2 crengi noi (pasul următor)
    DrawBranch(endPos, length * lengthScale, angle - splitAngle, step - 1, maxStep);
    DrawBranch(endPos, length * lengthScale, angle + splitAngle, step - 1, maxStep);
}

int main(void) {
    const int screenWidth = 1000;
    const int screenHeight = 800;

    InitWindow(screenWidth, screenHeight, "Arbore 2D - Fractal");
    SetTargetFPS(120);

    while (!WindowShouldClose()) {
        // Control pași cu săgețile Sus/Jos
        if (IsKeyPressed(KEY_UP)) {
            if (currentSteps < MAX_STEPS) currentSteps++;
        }
        if (IsKeyPressed(KEY_DOWN)) {
            if (currentSteps > 1) currentSteps--;
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawText("Arbore Fractal 2D", 20, 20, 30, DARKGRAY);
        DrawText(TextFormat("Numar de pasi (niveluri): %d", currentSteps), 20, 60, 20, DARKGRAY);
        DrawText("Foloseste sagetile SUS / JOS pentru a modifica pasii", 20, 90, 20, GRAY);

        // Numărul de crengi pe ultimul nivel este 2^(pas-1) (dacă trunchiul e pas 1)
        int leafBranches = (int)pow(2, currentSteps - 1);
        DrawText(TextFormat("Crengi la ultimul pas: %d", leafBranches), 20, 120, 20, GRAY);
        
        // Total crengi = 2^pas - 1
        int totalBranches = (int)pow(2, currentSteps) - 1;
        DrawText(TextFormat("Total crengi generate: %d", totalBranches), 20, 150, 20, GRAY);

        // Poziția de start (rădăcina trunchiului)
        Vector2 startPos = { (float)screenWidth / 2, (float)screenHeight - 50 };
        float startLength = 150.0f;
        float startAngle = -PI / 2.0f; // orientat în sus

        DrawBranch(startPos, startLength, startAngle, currentSteps, currentSteps);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
