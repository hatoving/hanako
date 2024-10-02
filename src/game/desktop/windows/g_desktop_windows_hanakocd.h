#ifndef G_DESKTOP_WINDOWS_HANAKOCD
#define G_DESKTOP_WINDOWS_HANAKOCD

#include <raylib.h>

#include "../g_desktop_window.h"
#include "../../g_button_label.h"

typedef struct {
	G_Desktop_Window* window;
	Texture2D* promo_art;

	G_Button_Label* install_button;
	G_Button_Label* play_button;
	G_Button_Label* configure_button;
} G_Desktop_Windows_HanakoCD;
G_Desktop_Windows_HanakoCD* G_Desktop_Windows_HanakoCD_Create();

#endif