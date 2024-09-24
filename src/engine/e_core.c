#include "e_core.h"
#include "e_screen.h"

#include "../m_global.h"

#include <stdio.h>
#include <raylib.h>

char* E_CORE_WINDOWTITLE = "Hanako";
E_Scene* E_CORE_CURRENTSCENE = NULL;

int screenshot_count = 0;

void E_Core_Init() {
    InitWindow(1280, 720, E_CORE_WINDOWTITLE);
    InitAudioDevice();

    SetWindowState(FLAG_WINDOW_RESIZABLE);
    SetTargetFPS(M_BASE_FPS);

    HideCursor();
    E_SCREEN_TEX = LoadRenderTexture(M_BASE_WIDTH, M_BASE_HEIGHT);

    SetExitKey(KEY_NULL);
}

void E_Core_StartDrawing() {
    BeginTextureMode(E_SCREEN_TEX);
}

void E_Core_HandleMiscInputs() {
    if (IsKeyPressed(KEY_F11)) {
        E_Screen_SetFull(!E_SCREEN_FULLSCREEN);
    }
    if (IsKeyPressed(KEY_F12)) {
        TakeScreenshot(TextFormat("screenshot_%i.png", screenshot_count));
        screenshot_count++;
    }
}

void E_Core_SetScene(E_Scene* scene) {
    if (E_CORE_CURRENTSCENE != NULL) {
        E_CORE_CURRENTSCENE->close();
        E_CORE_CURRENTSCENE = NULL;
    }
    if (scene != NULL) {
        E_CORE_CURRENTSCENE = scene;
        E_CORE_CURRENTSCENE->init();

        printf("E: Setting scene to : \"%s\"\n", E_CORE_CURRENTSCENE->label);
    }
    else {
        printf("E: Setting scene to nothing.\n");
    }
}

void E_Core_UpdateCurrentScene() {
    if (E_CORE_CURRENTSCENE != NULL) {
        E_CORE_CURRENTSCENE->update();
    }
}

void E_Core_DrawCurrentScene() {
    if (E_CORE_CURRENTSCENE != NULL) {
        E_CORE_CURRENTSCENE->draw();
    }
}

void E_Core_EndDrawing() {
    EndTextureMode();
    
    BeginDrawing();
        ClearBackground(BLACK);
        E_Screen_Handle();
    EndDrawing();
}

void E_Core_Close() {
    if (E_CORE_CURRENTSCENE != NULL) {
        E_CORE_CURRENTSCENE->close();
        E_CORE_CURRENTSCENE = NULL;
    }

    UnloadRenderTexture(E_SCREEN_TEX);

    CloseAudioDevice();
    CloseWindow();
}