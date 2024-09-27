#include <raylib.h>
#include <stdio.h>

#include "../engine/e_screen.h"
#include "../engine/e_math.h"

#include "../m_assets.h"
#include "../m_global.h"

#include "g_cursor.h"

bool show = true;

float G_CURSOR_X = 0.0f;
float G_CURSOR_Y = 0.0f;

Texture2D* mouse_tex = NULL;
Sound* mouse_click = NULL;

void G_Cursor_Init() {
	mouse_tex = (Texture2D*)M_Assets_GetAssetDataByLabel("preload/gfx/cursor");
	mouse_click = (Sound*)M_Assets_GetAssetDataByLabel("preload/snd/mouse_click");
}

void G_Cursor_Update() {
	for (int i = 0; i < MOUSE_BUTTON_BACK; i++) {
		if (IsMouseButtonPressed(i)) {
			SetSoundPitch(*mouse_click, E_Math_RandomFloat(0.9f, 1.2f));
			PlaySound(*mouse_click);
		}
	}
}

void G_Cursor_Draw() {
	if (show) {
		float offsetX = (GetScreenWidth() - M_BASE_WIDTH * E_SCREEN_SCALE_X) / 2;
		float offsetY = (GetScreenHeight() - M_BASE_HEIGHT * E_SCREEN_SCALE_Y) / 2;
		G_CURSOR_X = (GetMouseX() - offsetX) / E_SCREEN_SCALE_X;
		G_CURSOR_Y = (GetMouseY() - offsetY) / E_SCREEN_SCALE_Y;

		G_CURSOR_X = E_Math_Clamp(G_CURSOR_X, 0, 640);
		G_CURSOR_Y = E_Math_Clamp(G_CURSOR_Y, 0, 480);

		DrawTextureEx(*mouse_tex, (Vector2){(int)G_CURSOR_X, (int)G_CURSOR_Y}, 0.0f, 1.0f, WHITE);
	}
}

void G_Cursor_SetVisibility(bool value) {
	show = value;
}

void G_Cursor_ToggleVisibility() {
	show = !show;
}

void G_Cursor_Close() {
	mouse_click = NULL;
}