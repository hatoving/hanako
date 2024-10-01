#ifndef G_DESKTOP_WINDOWS_HANAKOCD
#define G_DESKTOP_WINDOWS_HANAKOCD

#include <raylib.h>
#include "../g_desktop_window.h"

typedef struct {
	G_Desktop_Window* window;
	Texture2D* promo_art;
} G_Desktop_Windows_HanakoCD;
G_Desktop_Windows_HanakoCD* G_Desktop_Windows_HanakoCD_Create();

#endif