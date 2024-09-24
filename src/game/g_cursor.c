#include <raylib.h>

#include "../engine/e_screen.h"
#include "../engine/e_math.h"

#include "../m_assets.h"
#include "../m_global.h"

#include "g_cursor.h"

bool show = true;

void G_Cursor_Init() {
}

void G_Cursor_Draw() {
    if (show) {
        float offsetX = (GetScreenWidth() - M_BASE_WIDTH * E_SCREEN_SCALE_X) / 2;
        float offsetY = (GetScreenHeight() - M_BASE_HEIGHT * E_SCREEN_SCALE_Y) / 2;
        float mouseX = (GetMouseX() - offsetX) / E_SCREEN_SCALE_X;
        float mouseY = (GetMouseY() - offsetY) / E_SCREEN_SCALE_Y;

        mouseX = E_Math_Clamp(mouseX, 0, 640);
        mouseY = E_Math_Clamp(mouseY, 0, 480);

        Texture2D* tex = (Texture2D*)M_Assets_GetAssetDataByLabel("preload/gfx/cursor");
        DrawTextureEx(*tex, (Vector2){(int)mouseX, (int)mouseY}, 0.0f, 1.0f, WHITE);
    }
}

void G_Cursor_SetVisibility(bool value) {
    show = value;
}

void G_Cursor_ToggleVisibility() {
    show = !show;
}

void G_Cursor_Close() {
}