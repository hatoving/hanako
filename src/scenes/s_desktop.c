#include "s_desktop.h"
#include "../m_assets.h"

#include "../game/g_button_label.h"
#include "../game/g_cursor.h"

#include "../game/desktop/g_desktop_icons.h"
#include "../game/desktop/g_desktop_assets.h"
#include "../game/desktop/g_desktop_window.h"
#include "../game/desktop/g_desktop_windowmanager.h"

#include "../game/desktop/windows/g_desktop_windows_hanakocd.h"

#include <raylib.h>
#include <stdio.h>

int current_background;
Texture2D* desktop_background;

G_Desktop_WindowManager* manager;
G_Desktop_Windows_HanakoCD* cd_launcher_window;

void S_DesktopInit() {
	G_Desktop_Assets_Init();
	G_Desktop_Icons_Init();

	desktop_background = (Texture2D*)M_Assets_GetAssetDataByLabel("desktop/gfx/bgs/0");
	manager = G_Desktop_WindowManager_Create();

	cd_launcher_window = G_Desktop_Windows_HanakoCD_Create();
	G_Desktop_WindowManager_AddWindow(cd_launcher_window->window, manager);
}

void S_DesktopUpdate() {
	G_Desktop_WindowManager_Update(manager);
}

void S_DesktopDraw() {
	ClearBackground(WHITE);
	DrawTexture(*desktop_background, 0, 0, WHITE);
	
	G_Desktop_WindowManager_Draw(manager);
}

void S_DesktopClose() {
	G_Desktop_WindowManager_Close(manager);
	M_Assets_CloseAssetByLabel("desktop/gfx/bgs/0");

	desktop_background = NULL;

	G_Desktop_Icons_Close();
	G_Desktop_Assets_Close();
}