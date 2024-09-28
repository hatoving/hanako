#ifndef G_DESKTOP_WINDOW_H
#define G_DESKTOP_WINDOW_H

#include <raylib.h>

typedef struct {
	int x, y, w, h;

	char* title;
	char* icon_title;

	NPatchInfo info;

	Texture2D* window_ptr;
	Texture2D* icon_ptr;

	void (*post_update_function)();
	void (*post_draw_function)();
} G_Desktop_Window;

G_Desktop_Window* G_Desktop_Window_Create(int x, int y, int w, int h, char* title, char* icon_name, Texture2D* tex);
void G_Desktop_Window_Draw(G_Desktop_Window* window);
void G_Desktop_Window_Update(G_Desktop_Window* window);
void G_Desktop_Window_Close(G_Desktop_Window* window);


#endif