#include "s_desktop.h"
#include "../m_assets.h"

#include "../game/g_cursor.h"
#include "../game/desktop/g_desktop_window.h"
#include "../game/desktop/g_desktop_windowmanager.h"

#include <raylib.h>
#include <stdio.h>

Texture2D* window_background;

int current_background;
Texture2D* desktop_background;

G_Desktop_Window* installer_window, *window;
G_Desktop_WindowManager* manager;

void S_DesktopInit() {
	M_Assets_LoadAssetByLabel("desktop/gfx/window");
	window_background = (Texture2D*)M_Assets_GetAssetDataByLabel("desktop/gfx/window");

	M_Assets_LoadAssetByLabel("desktop/gfx/bgs/0");
	desktop_background = (Texture2D*)M_Assets_GetAssetDataByLabel("desktop/gfx/bgs/0");

	manager = G_Desktop_WindowManager_Create();

	installer_window = G_Desktop_Window_Create(40, 40, 280, 180, "Hanako v. b. 98.0.1.", "h_installer", window_background);
	window = G_Desktop_Window_Create(60, 70, 100, 100, "lol", "h_installer", window_background);

	G_Desktop_WindowManager_AddWindow(installer_window, manager);
	G_Desktop_WindowManager_AddWindow(window, manager);
}

void S_DesktopUpdate() {
	//G_Desktop_Window_Update(window);
	G_Desktop_WindowManager_Update(manager);
}

void S_DesktopDraw() {
	ClearBackground(BLACK);
	DrawTexture(*desktop_background, 0, 0, WHITE);
	G_Desktop_WindowManager_Draw(manager);
}

void S_DesktopClose() {
	G_Desktop_Window_Close(installer_window);

	M_Assets_CloseAssetByLabel("desktop/gfx/window");
	window_background = NULL;

	M_Assets_CloseAssetByLabel("desktop/gfx/bgs/0");
	desktop_background = NULL;
}