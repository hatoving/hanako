#include "g_desktop_windows_hanakocd.h"

#include "../../../m_assets.h"
#include "../../../m_global.h"

#include <stdio.h>
#include <stdlib.h>

void G_Desktop_Windows_HanakoCD_Draw(void* window) {
	G_Desktop_Windows_HanakoCD* cast_window = (G_Desktop_Windows_HanakoCD*)window;
	DrawTexture(*cast_window->promo_art, cast_window->window->x + 3, 24 + cast_window->window->y, WHITE);
}

void G_Desktop_Windows_HanakoCD_Close(void* window) {
	G_Desktop_Windows_HanakoCD* cast_window = (G_Desktop_Windows_HanakoCD*)window;
	M_Assets_CloseAssetByLabel("desktop/gfx/windows/hanakocd/promo");
	cast_window->promo_art = NULL;
	free(window);
}

G_Desktop_Windows_HanakoCD* G_Desktop_Windows_HanakoCD_Create() {
	G_Desktop_Windows_HanakoCD* window = (G_Desktop_Windows_HanakoCD*)malloc(sizeof(G_Desktop_Windows_HanakoCD));
	
	M_Assets_LoadAssetByLabel("desktop/gfx/windows/hanakocd/promo");
	window->promo_art = (Texture2D*)M_Assets_GetAssetDataByLabel("desktop/gfx/windows/hanakocd/promo");

	window->window = G_Desktop_Window_Create(
		(M_BASE_WIDTH - 206) / 2,
		(M_BASE_HEIGHT - 240) / 2,
		206, 240,
		"HANAKO BETA RELEASE", "h_installer"
	);
	window->window->post_draw_function = G_Desktop_Windows_HanakoCD_Draw;
	window->window->post_draw_data = window;
	window->window->post_close_function = G_Desktop_Windows_HanakoCD_Close;
	window->window->post_close_data = window;

	return window;
}