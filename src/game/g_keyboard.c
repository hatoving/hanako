#include <raylib.h>
#include <stdio.h>

#include "../engine/e_math.h"
#include "../m_assets.h"

#include "g_keyboard.h"
#include "g_settings.h"

Sound* keyboard_click = NULL;

void G_Keyboard_Init() {
	keyboard_click = (Sound*)M_Assets_GetAssetDataByLabel("preload/snd/keyboard_click");
}

void G_Keyboard_Update() {
	// Loop through all possible keys
	for (int i = 32; i < 350; i++) {
		if (IsKeyPressed(i)) {
			SetSoundPitch(*keyboard_click, E_Math_RandomFloat(0.9f, 1.2f));
			SetSoundVolume(*keyboard_click, G_SETTINGS_CURRENT->sfx_volume);
			PlaySound(*keyboard_click);
		}
	}
}

void G_Keyboard_Close() {
	keyboard_click = NULL;
}