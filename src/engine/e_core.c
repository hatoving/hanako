#include "e_core.h"
#include "e_screen.h"

#include "../m_global.h"
#include "../m_assets.h"

#include "../game/g_settings.h"

#include <stdio.h>
#include <raylib.h>

char* E_CORE_WINDOWTITLE = "Hanako";
E_Scene* E_CORE_CURRENTSCENE = NULL;

int screenshot_count = 0;

void E_Core_Init() {
	SetTraceLogLevel(LOG_WARNING);
	SetConfigFlags(FLAG_WINDOW_ALWAYS_RUN);

	InitWindow(1280, 720, E_CORE_WINDOWTITLE);
	InitAudioDevice();

	SetWindowState(FLAG_WINDOW_RESIZABLE);
	SetTargetFPS(M_BASE_FPS);

	E_Screen_SetFull(G_SETTINGS_CURRENT->fullscreen);
	HideCursor();

	E_SCREEN_TEX = LoadRenderTexture(M_BASE_WIDTH, M_BASE_HEIGHT);
	//SetTextureFilter(E_SCREEN_TEX.texture, TEXTURE_FILTER_BILINEAR);

	SetExitKey(KEY_NULL);
}

void E_Core_StartDrawing() {
	BeginTextureMode(E_SCREEN_TEX);
}

void E_Core_HandleMiscInputs() {
	if (IsKeyPressed(KEY_F11)) {
		E_Screen_SetFull(!G_SETTINGS_CURRENT->fullscreen);
	}
	if (IsKeyPressed(KEY_F12)) {
		TakeScreenshot("screenshot_.png");
		screenshot_count++;
	}
}

void E_Core_SetScene(E_Scene* scene) {
	if (E_CORE_CURRENTSCENE != NULL) {
		E_CORE_CURRENTSCENE->close();
		E_CORE_CURRENTSCENE = NULL;
	}
	if (scene != NULL) {
		E_CORE_CURRENTSCENE = scene;
		E_CORE_CURRENTSCENE->init();

		printf("E: Setting scene to : \"%s\"\n", E_CORE_CURRENTSCENE->label);
	}
	else {
		printf("E: Setting scene to nothing.\n");
	}
}

void E_Core_UpdateCurrentScene() {
	if (E_CORE_CURRENTSCENE != NULL) {
		E_CORE_CURRENTSCENE->update();
	}
}

void E_Core_DrawCurrentScene() {
	if (E_CORE_CURRENTSCENE != NULL) {
		E_CORE_CURRENTSCENE->draw();
	}
}

Texture2D* current_border = NULL;
void E_Core_EndDrawing() {
	EndTextureMode();
	
	BeginDrawing();
		ClearBackground(BLACK);
		if (G_SETTINGS_CURRENT->current_render_mode == E_SCREEN_RM_PIXEL) {
			if (G_SETTINGS_CURRENT->current_border != 0) {
				current_border = (Texture2D*)M_Assets_GetAssetDataByLabel(TextFormat("preload/gfx/borders/%i", G_SETTINGS_CURRENT->current_border));
			}
			if (current_border != NULL) {
				DrawTexturePro(
					*current_border,
					(Rectangle){
						0, 0, current_border->width, current_border->height,
					},
					(Rectangle) {
						(GetScreenWidth() / 2),
						(GetScreenHeight() / 2),
						(current_border->width * E_SCREEN_SCALE_X),
						(current_border->height * E_SCREEN_SCALE_Y)
					},
					(Vector2){(current_border->width / 2) * E_SCREEN_SCALE_X, (current_border->height / 2) * E_SCREEN_SCALE_Y},
					0.0f, WHITE
				);
			}
		}

		E_Screen_Handle();
	EndDrawing();
}

void E_Core_Close() {
	if (E_CORE_CURRENTSCENE != NULL) {
		E_CORE_CURRENTSCENE->close();
		E_CORE_CURRENTSCENE = NULL;
	}

	UnloadRenderTexture(E_SCREEN_TEX);

	CloseAudioDevice();
	CloseWindow();
}