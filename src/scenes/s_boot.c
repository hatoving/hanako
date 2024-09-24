#include "s_boot.h"

#include "../game/g_cursor.h"
#include "../m_assets.h"

#include "../engine/e_core.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <raylib.h>

typedef enum {
    SUBSCENE_INTRO,
    SUBSCENE_LOAD,
};

int current_subscene = (int)SUBSCENE_INTRO;
int intro_step = 0;
bool intro_wait = false;
float intro_wait_time = 0.0f;

int boot1_current_index = 0;
float boot1_mem_check = 0;

int current_letter_count = 0;
int current_index_to_add = 0;
bool done_adding_msg = false;

/* 
    77 characters to fill up one line on the screen
    38 lines to fill up the whole screen
    77 * 38 = 2926 avaialble characters + 1 for the null terminator
 */
char screen_output[(77 * 38) + 1];
void ClearScreenOutput() {
    screen_output[0] = '\0';
    current_index_to_add = 0;   
    current_letter_count = 0;
}

Sound* beep_sound;
Font* system_font;

Texture2D* trophy_graphic;

void AddTextToScreenOutput(char* text) {
    size_t len = strlen(text);
    for (int i = 0; i < len; i++) {
        screen_output[current_letter_count] = text[i];
        screen_output[current_letter_count + 1] = '\0';
        current_letter_count++;
    }   
}

void S_BootInit() {
    G_Cursor_SetVisibility(false);
    ClearScreenOutput();

    system_font = (Font*)M_Assets_GetAssetDataByLabel("preload/fnt/system");
    beep_sound = (Sound*)M_Assets_GetAssetDataByLabel("preload/snd/beep");

    M_Assets_LoadAssetByLabel("boot/gfx/trophy");
    trophy_graphic = (Texture2D*)M_Assets_GetAssetDataByLabel("boot/gfx/trophy");
}

int intro_substep_count = 0; // we use this variable if we need to count something
float intro_substep_wait = 0.5f;
int intro_substep_done = false;
void IntroWait(float wait_time) {
    if (!intro_wait) {
        intro_wait_time = wait_time;
        intro_wait = true;
    } else {
        if (intro_wait_time <= 0.0f) {
            intro_step++;

            intro_wait = false;
            intro_substep_done = false;
        } else {
            intro_wait_time -= GetFrameTime();
        }
    }
}

void S_BootUpdate() {
    switch(current_subscene) {
        case (int)SUBSCENE_INTRO: {
            switch (intro_step) {
                case 0: {
                    IntroWait(2.0f);
                    break;
                }
                case 1: {
                    if (!intro_wait) {
                        AddTextToScreenOutput("(press ENTER to skip)\n\n\t\t\t\t\t\tTrophy Personal BIOS v2.34\n\t\t\t\t\t\tCopyright (C) 1987-94 Trophy Software\n\n");
                        PlaySound(*beep_sound);
                    }
                    IntroWait(1.0f);
                    break;
                }
                case 2: {
                    if (!intro_wait) {
                        AddTextToScreenOutput("Initializing BOOT sequence");
                        PlaySound(*beep_sound);
                        intro_wait = true;
                    }

                    if (intro_substep_wait > 0.0f) {
                        intro_substep_wait -= GetFrameTime();
                    } else if (intro_substep_wait <= 0.0f) {
                        intro_substep_count++;

                        if (intro_substep_count >= 4) {
                            intro_step++;
                            intro_wait = false;
                            intro_substep_count = 0;
                        } else {
                            AddTextToScreenOutput(".");
                            intro_substep_wait = 0.5f;
                        }
                    }
                    //IntroWait(1.5f);
                    break;
                }
                case 3: {
                    if (!intro_substep_done) {
                        if (!intro_wait) {
                            AddTextToScreenOutput("\n\nMemory Check : \t\t");
                            PlaySound(*beep_sound);
                            intro_wait = true;
                        }
                        if (boot1_mem_check < 8192) {
                            boot1_mem_check += 10000.0f * GetFrameTime();
                            char* mem_check_str = TextFormat("%i", (int)floor(boot1_mem_check));
                            int mem_check_strlen = strlen(mem_check_str);

                            if (intro_substep_count == 0) {
                                AddTextToScreenOutput(mem_check_str);
                            } else {
                                int index = strlen(screen_output) - intro_substep_count;

                                screen_output[index] = '\0';
                                current_letter_count -= intro_substep_count;

                                AddTextToScreenOutput(mem_check_str);
                            }

                            intro_substep_count = mem_check_strlen;
                        } else if (boot1_mem_check >= 8192) {
                            boot1_mem_check = 8192;

                            intro_wait = false;
                            intro_substep_done = true;

                            AddTextToScreenOutput("kb\tOK\n");
                            PlaySound(*beep_sound);
                        }
                    }
                    if (intro_substep_done) {
                        IntroWait(2.0f);
                    }
                    break;
                }
                case 4: {
                    if (!intro_wait) {
                        AddTextToScreenOutput("dumbass\n");
                        PlaySound(*beep_sound);
                    }
                    IntroWait(1.0f);
                    break;
                }
                default: {
                    break;
                }
            }
            break;
        }
    }

    /*if (msg_char_countdown <= 0.0f) {
        if (current_index_to_add < strlen(step1_messages[step1_current_index]) && !done_adding_msg) {
            char to_add = (step1_messages[step1_current_index])[current_index_to_add];

            screen_output[current_letter_count] = to_add;
            screen_output[current_letter_count + 1] = '\0';
            current_letter_count++;
            current_index_to_add++;

            if (to_add != '\n' || to_add != '\t') {
                PlaySound(text_sfx);
            }
            msg_char_countdown = msg_speed;
        } else {
            done_adding_msg = true;
        }
    } else {
        msg_char_countdown -= GetFrameTime();
    }

    if (IsKeyPressed(KEY_ENTER) && done_adding_msg) {
        step1_current_index++;
        done_adding_msg = false;
        current_index_to_add = 0;

        if (step1_current_index >= sizeof(step1_messages) / sizeof(step1_messages[0])) {
            ClearScreenOutput();
            step1_current_index = 0;
        }
    }
        Commenting this out and leaving it in, in case I need it later
    */
}

void S_BootDraw() {
    ClearBackground(BLACK);

    if (intro_step >= 1 && trophy_graphic != NULL) {
        DrawTexture(*trophy_graphic, 16, 43, WHITE);
    }
    DrawTextEx(system_font != NULL ? *system_font : GetFontDefault(), screen_output, (Vector2){15, 15}, 16, 0, GRAY);
}

void S_BootClose() {
    beep_sound = NULL;
    system_font = NULL;

    M_Assets_CloseAssetByLabel("boot/gfx/trophy");
    trophy_graphic = NULL;

    ClearScreenOutput();
}