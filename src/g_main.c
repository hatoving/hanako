#include <stdio.h>
#include <raylib.h>

#include "g_global.h"
#include "g_assets.h"
#include "g_scenes.h"
#include "g_cursor.h"

#include "engine/e_screen.h"
#include "engine/e_core.h"

int main(int argc, char** argv) {
	E_Init();

	G_InitializeAssets();
	G_CursorInit();

	G_Scenes_Populate();
	E_SetScene(G_SCENE_BOOT);

	while(!WindowShouldClose()) {
		E_HandleMiscInputs();
		E_UpdateCurrentScene();

		E_StartDrawing();
			E_DrawCurrentScene();
			G_CursorDraw();
			DrawFPS(10, 400);
		E_EndDrawing();
	}

	G_CursorClose();
	G_Scenes_Close();
	G_CloseAssets();

	E_Close();

	return 0;
}