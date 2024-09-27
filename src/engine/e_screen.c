#include <stdio.h>
#include <stdlib.h>

#include "../m_global.h"
#include "e_screen.h"

E_SCREEN_RM E_SCREEN_CURRENT_RM = E_SCREEN_RM_PIXEL;
RenderTexture2D E_SCREEN_TEX;

bool E_SCREEN_FULLSCREEN = false;

float E_SCREEN_SCALE_X = .0f;
float E_SCREEN_SCALE_Y = .0f;

void E_Screen_SetFull(bool on) {
    E_SCREEN_FULLSCREEN = on;

    if (E_SCREEN_FULLSCREEN) {
        SetWindowState(FLAG_BORDERLESS_WINDOWED_MODE);
    } else {
        SetWindowState(FLAG_BORDERLESS_WINDOWED_MODE);
        ClearWindowState(FLAG_BORDERLESS_WINDOWED_MODE);
    }

    printf("E: Setting fullscreen... %i\n", (int)E_SCREEN_FULLSCREEN);
}

void E_Screen_Handle() {
    switch (E_SCREEN_CURRENT_RM) {
        case E_SCREEN_RM_PIXEL: {
            int scale_x = GetScreenWidth() / M_BASE_WIDTH;
            int scale_y = GetScreenHeight() / M_BASE_HEIGHT;

            // Choose the smaller scale factor to maintain aspect ratio
            E_SCREEN_SCALE_X = E_SCREEN_SCALE_Y = (scale_x < scale_y) ? scale_x : scale_y;
            
            DrawTexturePro(
                E_SCREEN_TEX.texture,
                (Rectangle){0, 0, E_SCREEN_TEX.texture.width, -E_SCREEN_TEX.texture.height, },
                (Rectangle){(GetScreenWidth() - (M_BASE_WIDTH * E_SCREEN_SCALE_X)) / 2,
                            (GetScreenHeight() - (M_BASE_HEIGHT * E_SCREEN_SCALE_Y)) / 2,
                            E_SCREEN_TEX.texture.width * E_SCREEN_SCALE_X,
                            E_SCREEN_TEX.texture.height * E_SCREEN_SCALE_Y, },
                (Vector2){ 0, 0 },
                0,
                WHITE
            );
            break;
        }
        case E_SCREEN_RM_FIT: {
            float texture_aspect_ratio = (float)M_BASE_WIDTH / (float)M_BASE_HEIGHT;
            float window_aspect_ratio = (float)GetScreenWidth() / (float)GetScreenHeight();

            float scale_x, scale_y;
            if (texture_aspect_ratio > window_aspect_ratio) {
                scale_x = (float)GetScreenWidth() / (float)M_BASE_WIDTH;
                scale_y = scale_x;
            } else {
                scale_y = (float)GetScreenHeight() / (float)M_BASE_HEIGHT;
                scale_x = scale_y;
            }
            E_SCREEN_SCALE_X = scale_x;
            E_SCREEN_SCALE_Y = scale_y;
            
            //DrawTexture(E_SCREEN_TEX.texture, 0, 0, WHITE);
            DrawTexturePro(
                E_SCREEN_TEX.texture,
                (Rectangle){0, 0, E_SCREEN_TEX.texture.width, -E_SCREEN_TEX.texture.height, },
                (Rectangle){(GetScreenWidth() - (M_BASE_WIDTH * scale_x)) / 2,
                            (GetScreenHeight() - (M_BASE_HEIGHT * scale_y)) / 2,
                            E_SCREEN_TEX.texture.width * scale_x,
                            E_SCREEN_TEX.texture.height * scale_y, },
                (Vector2){ 0, 0 },
                0,
                WHITE
            );
            break;
        };
        case E_SCREEN_RM_STRETCH: {
            E_SCREEN_SCALE_X = (float)GetScreenWidth() / M_BASE_WIDTH;
            E_SCREEN_SCALE_Y = (float)GetScreenHeight() / M_BASE_HEIGHT;

            DrawTexturePro(
                E_SCREEN_TEX.texture,
                (Rectangle){0, 0, E_SCREEN_TEX.texture.width, -E_SCREEN_TEX.texture.height, },
                (Rectangle){0, 0, GetScreenWidth(), GetScreenHeight()},
                (Vector2){ 0, 0 },
                0,
                WHITE
            );
            break;
        }
    }
}