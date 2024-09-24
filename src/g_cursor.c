#include <raylib.h>

#include "engine/e_screen.h"
#include "engine/e_math.h"

#include "g_assets.h"
#include "g_global.h"
#include "g_cursor.h"

bool show = true;

void G_CursorInit() {
}

void G_CursorDraw() {
    if (show) {
        float offsetX = (GetScreenWidth() - G_BASE_WIDTH * E_SCREEN_SCALE_X) / 2;
        float offsetY = (GetScreenHeight() - G_BASE_HEIGHT * E_SCREEN_SCALE_Y) / 2;
        float mouseX = (GetMouseX() - offsetX) / E_SCREEN_SCALE_X;
        float mouseY = (GetMouseY() - offsetY) / E_SCREEN_SCALE_Y;

        mouseX = E_Math_Clamp(mouseX, 0, 640);
        mouseY = E_Math_Clamp(mouseY, 0, 480);

        Texture2D* tex = (Texture2D*)G_GetAssetDataByLabel("preload/gfx/cursor");
        DrawTextureEx(*tex, (Vector2){(int)mouseX, (int)mouseY}, 0.0f, 1.0f, WHITE);
    }
}

void G_CursorSetVisibility(bool value) {
    show = value;
}

void G_CursorToggleVisibility() {
    show = !show;
}

void G_CursorClose() {
}