#include "g_desktop_windows_hanakocd.h"

#include "../../../m_assets.h"
#include "../../../m_global.h"

#include "../../g_button_label.h"

#include <stdio.h>
#include <stdlib.h>

void G_Desktop_Windows_HanakoCD_Draw(void* window) {
	G_Desktop_Windows_HanakoCD* cast_window = (G_Desktop_Windows_HanakoCD*)window;

	DrawTexture(
		*cast_window->promo_art,
		((cast_window->window->w - cast_window->promo_art->width) / 2) + cast_window->window->x,
		24 + cast_window->window->y,
		WHITE
	);

	cast_window->install_button->base->pos = (Vector2){
		cast_window->window->x + 16,
		(cast_window->window->h - 33) + cast_window->window->y
	};
	G_Button_Label_Draw(cast_window->install_button);

	cast_window->configure_button->base->pos = (Vector2){
		(cast_window->window->x + cast_window->window->w) - cast_window->configure_button->w - 16,
		(cast_window->window->h - 33) + cast_window->window->y
	};
	G_Button_Label_Draw(cast_window->configure_button);

	cast_window->play_button->base->pos = (Vector2){
		((cast_window->install_button->base->pos.x + cast_window->install_button->w) +
		(cast_window->configure_button->base->pos.x - cast_window->play_button->w)) / 2.0f,
		(cast_window->window->h - 33) + cast_window->window->y
	};
	G_Button_Label_Draw(cast_window->play_button);
}

void G_Desktop_Windows_HanakoCD_Update(void* window) {
	G_Desktop_Windows_HanakoCD* cast_window = (G_Desktop_Windows_HanakoCD*)window;

	G_Button_Label_Update(cast_window->play_button);
	G_Button_Label_Update(cast_window->install_button);
	G_Button_Label_Update(cast_window->configure_button);
}

void G_Desktop_Windows_HanakoCD_Close(void* window) {
	G_Desktop_Windows_HanakoCD* cast_window = (G_Desktop_Windows_HanakoCD*)window;
	
	G_Button_Label_Close(cast_window->play_button);
	G_Button_Label_Close(cast_window->install_button);
	G_Button_Label_Close(cast_window->configure_button);

	M_Assets_CloseAssetByLabel("desktop/gfx/windows/hanakocd/promo");
	cast_window->promo_art = NULL;

	free(window);
}

G_Desktop_Windows_HanakoCD* G_Desktop_Windows_HanakoCD_Create() {
	G_Desktop_Windows_HanakoCD* window = (G_Desktop_Windows_HanakoCD*)malloc(sizeof(G_Desktop_Windows_HanakoCD));

	window->install_button = G_Button_Label_Create(
		(G_Button_LabelInfo){
			"Install",
			(Font*)M_Assets_GetAssetDataByLabel("preload/fnt/desktop_i"),
			11, (Color){64, 64, 128, 255}
		},
		(G_ButtonFrameInfo){
			0, 0, 1,
			(Vector2){11.0f, 11.0f},
			2
		},
		(Vector2){40, 40},
		(Texture2D*)M_Assets_GetAssetDataByLabel("desktop/gfx/window/buttons/generic")
	);
	window->play_button = G_Button_Label_Create(
		(G_Button_LabelInfo){
			"Play",
			(Font*)M_Assets_GetAssetDataByLabel("preload/fnt/desktop_i"),
			11, (Color){64, 64, 128, 255}
		},
		(G_ButtonFrameInfo){
			0, 0, 1,
			(Vector2){11.0f, 11.0f},
			2
		},
		(Vector2){40, 40},
		(Texture2D*)M_Assets_GetAssetDataByLabel("desktop/gfx/window/buttons/generic")
	);
	window->configure_button = G_Button_Label_Create(
		(G_Button_LabelInfo){
			"Configure",
			(Font*)M_Assets_GetAssetDataByLabel("preload/fnt/desktop_i"),
			11, (Color){64, 64, 128, 255}
		},
		(G_ButtonFrameInfo){
			0, 0, 1,
			(Vector2){11.0f, 11.0f},
			2
		},
		(Vector2){40, 40},
		(Texture2D*)M_Assets_GetAssetDataByLabel("desktop/gfx/window/buttons/generic")
	);
	
	M_Assets_LoadAssetByLabel("desktop/gfx/windows/hanakocd/promo");
	window->promo_art = (Texture2D*)M_Assets_GetAssetDataByLabel("desktop/gfx/windows/hanakocd/promo");

	window->window = G_Desktop_Window_Create(
		(M_BASE_WIDTH - 250) / 2,
		(M_BASE_HEIGHT - 240) / 2,
		235, 240,
		"HANAKO BETA RELEASE", "cd"
	);

	window->window->post_draw_function = G_Desktop_Windows_HanakoCD_Draw;
	window->window->post_draw_data = window;

	window->window->post_update_function = G_Desktop_Windows_HanakoCD_Update;
	window->window->post_update_data = window;

	window->window->post_close_function = G_Desktop_Windows_HanakoCD_Close;
	window->window->post_close_data = window;

	return window;
}