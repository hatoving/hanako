#ifndef G_DESKTOP_WINDOW_H
#define G_DESKTOP_WINDOW_H

#include "../g_button.h"
#include <raylib.h>

typedef struct {
	int x, y, w, h;

	char* title;
	char* icon_title;

	NPatchInfo info;
	bool is_closed;

	Texture2D* window_ptr;
	Texture2D* icon_ptr;

	G_Button* close_button;

	void (*post_update_function)(void* data);
	void* post_update_data;

	void (*post_draw_function)(void* data);
	void* post_draw_data;

	void (*post_close_function)(void* data);
	void* post_close_data;
} G_Desktop_Window;

G_Desktop_Window* G_Desktop_Window_Create(int x, int y, int w, int h, char* title, char* icon_name);
void G_Desktop_Window_Draw(G_Desktop_Window* window);
void G_Desktop_Window_Update(G_Desktop_Window* window);
void G_Desktop_Window_Close(G_Desktop_Window* window);

#endif