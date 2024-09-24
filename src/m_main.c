#include <stdio.h>
#include <raylib.h>

#include "m_global.h"
#include "m_assets.h"
#include "m_scenes.h"

#include "game/g_cursor.h"

#include "engine/e_screen.h"
#include "engine/e_core.h"

int main(int argc, char** argv) {
	E_Core_Init();

	M_Assets_Init();
	G_Cursor_Init();

	M_Scenes_Populate();
	E_Core_SetScene(S_BOOT);

	while(!WindowShouldClose()) {
		E_Core_HandleMiscInputs();
		E_Core_UpdateCurrentScene();

		E_Core_StartDrawing();
			E_Core_DrawCurrentScene();
			G_Cursor_Draw();
			DrawFPS(10, 460);
		E_Core_EndDrawing();
	}

	G_Cursor_Close();

	M_Scenes_Close();
	M_Assets_Close();

	E_Core_Close();
	return 0;
}