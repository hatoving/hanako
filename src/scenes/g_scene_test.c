#include "g_scene_test.h"
#include "../engine/e_core.h"

#include <stdio.h>
#include <raylib.h>

Texture2D loading_texture;

void G_Scene_TestInit() {
    Image loading_img = LoadImage("data/graphics/loading.png");
    loading_texture = LoadTextureFromImage(loading_img);
    UnloadImage(loading_img);
}

void G_Scene_TestUpdate() {
    if (IsKeyDown(KEY_F1)) {
        E_SetScene(NULL);
    }
}

void G_Scene_TestDraw() {
    DrawTexture(loading_texture, 0, 0, WHITE);
}

void G_Scene_TestClose() {
    UnloadTexture(loading_texture);
}