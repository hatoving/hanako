#include "g_game.h"

#include "g_keyboard.h"
#include "g_cursor.h"

#include "../m_global.h"
#include "../m_assets.h"
#include "../m_scenes.h"

#include "../engine/e_screen.h"
#include "../engine/e_math.h"
#include "../engine/e_core.h"

#include <stdio.h>
#include <raylib.h>

Music* computer_ambience = NULL;

float hdd_ambience_volume = -1.0f;
bool hdd_ambience_fade_in = false;
Music* hdd_ambience = NULL;

void G_Close() {
    StopMusicStream(*computer_ambience);
    computer_ambience = NULL;

    if (IsMusicStreamPlaying(*hdd_ambience)) {
        StopMusicStream(*hdd_ambience);
    }
    hdd_ambience = NULL;

    G_Keyboard_Close();
	G_Cursor_Close();

	M_Scenes_Close();
	M_Assets_Close();

	E_Core_Close();
}

void G_Loop() {
    while(!WindowShouldClose()) {
		E_Core_HandleMiscInputs();

		E_Core_UpdateCurrentScene();

        G_Cursor_Update();
        G_Keyboard_Update();

		UpdateMusicStream(*computer_ambience);

        if (hdd_ambience_fade_in) {
            hdd_ambience_volume += 0.1f * GetFrameTime();
        } else {
            hdd_ambience_volume -= 0.1f * GetFrameTime();
        }
        hdd_ambience_volume = E_Math_Clamp(hdd_ambience_volume, 0.0f, 1.0f);
        SetMusicVolume(*hdd_ambience, hdd_ambience_volume);

        UpdateMusicStream(*hdd_ambience);

		E_Core_StartDrawing();
			E_Core_DrawCurrentScene();
			G_Cursor_Draw();
			//DrawFPS(10, 460);
		E_Core_EndDrawing();
	}
    G_Close();
}

void G_Run() {
    E_Core_Init();
	M_Assets_Init();

	G_Cursor_Init();
    G_Keyboard_Init();

	M_Scenes_Populate();
	E_Core_SetScene(S_BOOT);

	computer_ambience = (Music*)M_Assets_GetAssetDataByLabel("preload/mus/ambience");
    hdd_ambience = (Music*)M_Assets_GetAssetDataByLabel("preload/mus/hdd");
	computer_ambience->looping = true;

	PlayMusicStream(*computer_ambience);
    G_Loop();
}

void G_HardDriveSound(bool _fade_in) {
    if (!IsMusicStreamPlaying(*hdd_ambience)) {
        SetMusicPitch(*hdd_ambience, E_Math_RandomFloat(1.2f, 1.4f));
        SetMusicPan(*hdd_ambience, E_Math_RandomFloat(0.0f, 0.3f));
        PlayMusicStream(*hdd_ambience);
    }
    hdd_ambience_fade_in = _fade_in;
}