#ifndef G_DESKTOP_WINDOWMANAGER_H
#define G_DESKTOP_WINDOWMANAGER_H

#include "g_desktop_window.h"
#include <raylib.h>

typedef struct {
	G_Desktop_Window** windows;
	int window_count;
	G_Desktop_Window* active_window;
} G_Desktop_WindowManager;
G_Desktop_WindowManager* G_Desktop_WindowManager_Create();

void G_Desktop_WindowManager_AddWindow(G_Desktop_Window* window, G_Desktop_WindowManager* manager);

void G_Desktop_WindowManager_Update(G_Desktop_WindowManager* manager);
void G_Desktop_WindowManager_Draw(G_Desktop_WindowManager* manager);

void G_Desktop_WindowManager_Close(G_Desktop_WindowManager* manager);


#endif