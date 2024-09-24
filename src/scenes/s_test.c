#include "s_test.h"
#include "../engine/e_core.h"

#include <stdio.h>
#include <raylib.h>

Texture2D loading_texture;

void S_TestInit() {
    Image loading_img = LoadImage("data/graphics/loading.png");
    loading_texture = LoadTextureFromImage(loading_img);
    UnloadImage(loading_img);
}

void S_TestUpdate() {
    if (IsKeyDown(KEY_F1)) {
        E_Core_SetScene(NULL);
    }
}

void S_TestDraw() {
    DrawTexture(loading_texture, 0, 0, WHITE);
}

void S_TestClose() {
    UnloadTexture(loading_texture);
}