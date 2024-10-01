#include "g_desktop_windowmanager.h"
#include "../g_cursor.h"

#include <stdio.h>
#include <stdlib.h>

#define WINDOW_LIMIT 4

G_Desktop_WindowManager* G_Desktop_WindowManager_Create() {
	G_Desktop_WindowManager* manager = (G_Desktop_WindowManager*)malloc(sizeof(G_Desktop_WindowManager));
    manager->windows = (G_Desktop_Window**)malloc(sizeof(G_Desktop_Window*) * WINDOW_LIMIT);
    manager->window_count = 0;
    manager->active_window = NULL;
    return manager;
}

void G_Desktop_WindowManager_AddWindow(G_Desktop_Window* window, G_Desktop_WindowManager* manager) {
	manager->windows[manager->window_count++] = window;
}

void G_Desktop_WindowManager_BringToFront(G_Desktop_WindowManager* manager, int index) {
    G_Desktop_Window* window = manager->windows[index];

    for (int i = index; i < manager->window_count - 1; i++) {
        manager->windows[i] = manager->windows[i + 1];
    }
    manager->windows[manager->window_count - 1] = window;
}

void G_Window_Manager_RemoveWindow(G_Desktop_WindowManager* manager, int index) {
    G_Desktop_Window* window = manager->windows[index];
    G_Desktop_Window_Close(window);

    for (int i = index; i < manager->window_count - 1; i++) {
        manager->windows[i] = manager->windows[i + 1];
    }
    manager->window_count--;
}

void G_Desktop_WindowManager_Update(G_Desktop_WindowManager* manager) {
    Vector2 mouse_position = (Vector2){G_CURSOR_X, G_CURSOR_Y};
    bool window_clicked = false;

    for (int i = manager->window_count - 1; i >= 0; i--) {
        G_Desktop_Window* window = manager->windows[i];

		if (window->is_closed) {
            G_Window_Manager_RemoveWindow(manager, i);
            continue;
        }

        Rectangle window_rect = {
            window->x,
            window->y,
            window->w,
            window->h
        };

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && !window_clicked) {
            if (CheckCollisionPointRec(mouse_position, window_rect)) {
                manager->active_window = window;
                G_Desktop_WindowManager_BringToFront(manager, i);
                window_clicked = true;
            }
        }
    }

    if (manager->active_window != NULL) {
        G_Desktop_Window_Update(manager->active_window);
    }
}

void G_Desktop_WindowManager_Draw(G_Desktop_WindowManager* manager) {
	for (int i = 0; i < manager->window_count; i++) {
        G_Desktop_Window* window = manager->windows[i];
		G_Desktop_Window_Draw(window);
    }
}

void G_Desktop_WindowManager_Close(G_Desktop_WindowManager* manager) {
	for (int i = 0; i < manager->window_count; i++) {
		G_Desktop_Window_Close(manager->windows[i]);
	}
	
	free(manager);
}