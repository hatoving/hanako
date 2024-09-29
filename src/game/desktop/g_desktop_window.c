#include "g_desktop_window.h"
#include "../../m_assets.h"

#include <raylib.h>
#include <stdlib.h>

#include "../g_cursor.h"

G_Desktop_Window* G_Desktop_Window_Create(int x, int y, int w, int h, char* title, char* icon_title, Texture2D* tex) {
	G_Desktop_Window* window = (G_Desktop_Window*)malloc(sizeof(G_Desktop_Window));

	window->x = x;
	window->y = y;
	window->h = h;
	window->w = w;

	window->title = title;
	window->info = (NPatchInfo){ (Rectangle){ 0.0f, 0.0f, 32.0f, 32.0f }, 4, 4, 4, 4, NPATCH_NINE_PATCH };

	window->window_ptr = tex;

	window->post_update_function = NULL;
	window->post_draw_function = NULL;

	M_Assets_LoadAssetByLabel(TextFormat("desktop/gfx/icons/%s", icon_title));
	window->icon_ptr = (Texture2D*)M_Assets_GetAssetDataByLabel(TextFormat("desktop/gfx/icons/%s", icon_title));
	window->icon_title = icon_title;

	window->close_button = G_Button_Create(
		(G_ButtonFrameInfo){
			0, 0, 1,
			(Vector2){11.0f, 11.0f},
			2
		},
		(Vector2){0, 0},
		(Vector2){0, 0},
		"desktop/gfx/window/buttons/close"
	);

	return window;
}

void G_Desktop_Window_Update(G_Desktop_Window* window) {
	static bool dragging = false;
	static Vector2 drag_offset = {0};
	Vector2 mouse_position = (Vector2){G_CURSOR_X, G_CURSOR_Y};

	if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
		Rectangle title_bar = {
			window->x + 6,
			window->y + 6,
			window->w - 13,
			18
		};

		if (CheckCollisionPointRec(mouse_position, title_bar)) {
			dragging = true;
			drag_offset.x = mouse_position.x - window->x;
			drag_offset.y = mouse_position.y - window->y;
		}
	}

	if (dragging) {
		if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
			window->x = mouse_position.x - drag_offset.x;
			window->y = mouse_position.y - drag_offset.y;
		} else {
			dragging = false;
		}
	}
	G_Button_Update(window->close_button);

	if (window->post_update_function != NULL)
		window->post_update_function();
}

void G_Desktop_Window_Draw(G_Desktop_Window* window) {
	DrawTextureNPatch(
		*window->window_ptr, window->info,
		(Rectangle){
			(float)window->x,
			(float)window->y,
			(float)window->w,
			(float)window->h
		},
		(Vector2){0.0f, 0.0f}, 0.0f, WHITE
	);
	DrawRectangle(window->x + 6, window->y + 6, window->w - 13, 18, (Color){64, 64, 128, 255});

	Font* window_title_fnt = (Font*)M_Assets_GetAssetDataByLabel("preload/fnt/desktop_bi");
	DrawTextEx(*window_title_fnt, window->title, (Vector2){window->x + (window->icon_ptr == NULL ? 14 : 26), window->y + 11}, 11, 0.0f, WHITE);

	if (window->icon_ptr != NULL)
		DrawTexture(*window->icon_ptr, window->x + 10, window->y + 8, WHITE);

	window->close_button->pos = (Vector2){(window->x + window->w) - 22, window->y + 10};
	G_Button_Draw(window->close_button);

	if (window->post_draw_function != NULL)
		window->post_draw_function();

}

void G_Desktop_Window_Close(G_Desktop_Window* window) {
	G_Button_Close(window->close_button);
	M_Assets_CloseAssetByLabel(TextFormat("desktop/gfx/icons/%s", window->icon_title));
	free(window);
}