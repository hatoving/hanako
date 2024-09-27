#include "s_boot.h"

#include "../game/g_game.h"
#include "../game/g_cursor.h"

#include "../m_global.h"
#include "../m_assets.h"

#include "../engine/e_math.h"
#include "../engine/e_draw.h"
#include "../engine/e_core.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <raylib.h>

typedef enum {
	SUBSCENE_SPLASH,
	SUBSCENE_INTRO,
	SUBSCENE_LOADING
};

int current_subscene = (int)SUBSCENE_SPLASH;

int current_step = 0;
bool wait_for_timer = false;
float timer = 0.0f;

int boot1_mem_check_cap = 65536;
float boot1_mem_check = 0;

int current_letter_count = 0;
int current_index_to_add = 0;
bool done_adding_msg = false;

/* 
	77 characters to fill up one line on the screen
	38 lines to fill up the whole screen
	77 * 38 = 2926 avaialble characters + 1 for the null terminator
 */
char screen_output[2927];
void ClearScreenOutput() {
	screen_output[0] = '\0';
	current_index_to_add = 0;   
	current_letter_count = 0;
}

Sound* beep_sound;
Sound* power_button;
Font* system_font;

Texture2D* trophy_graphic;
Texture2D* hat_logo;
Texture2D* starlight_bg;

float loading_bar_x = 0;
Texture2D* starlight_loading_bar;

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
	power_button = (Sound*)M_Assets_GetAssetDataByLabel("preload/snd/power_button");

	M_Assets_LoadAssetByLabel("boot/gfx/trophy");
	trophy_graphic = (Texture2D*)M_Assets_GetAssetDataByLabel("boot/gfx/trophy");
	M_Assets_LoadAssetByLabel("boot/gfx/hat_logo");
	hat_logo = (Texture2D*)M_Assets_GetAssetDataByLabel("boot/gfx/hat_logo");

	M_Assets_LoadAssetByLabel("boot/gfx/starlight_bg");
	starlight_bg = (Texture2D*)M_Assets_GetAssetDataByLabel("boot/gfx/starlight_bg");
	M_Assets_LoadAssetByLabel("boot/gfx/starlight_loadbar");
	starlight_loading_bar = (Texture2D*)M_Assets_GetAssetDataByLabel("boot/gfx/starlight_loadbar");

	PlaySound(*power_button);
}

int intro_substep_count = 0; // we use this variable if we need to count something in the intro
float intro_substep_wait = 0.5f;
int intro_substep_done = false;
void WaitForTimer(float wait_time) {
	if (!wait_for_timer) {
		timer = wait_time;
		wait_for_timer = true;
	} else {
		if (timer <= 0.0f) {
			current_step++;

			wait_for_timer = false;
			intro_substep_done = false;
		} else {
			timer -= GetFrameTime();
		}
	}
}

void S_BootUpdate() {
	switch(current_subscene) {
		case (int)SUBSCENE_SPLASH: {
			switch(current_step) {
				case 0:
				case 2: {
					WaitForTimer(1.0f);
					break;
				}
				case 1: {
					WaitForTimer(3.0f);
					break;
				}
				case 3: {
					current_step = 0;
					wait_for_timer = false;
					current_subscene = SUBSCENE_INTRO;
					break;
				}
			}
			break;
		}
		case (int)SUBSCENE_INTRO: {
			if (IsKeyPressed(KEY_ENTER)) {
				wait_for_timer = false;
				current_step = 5;
				PlaySound(*beep_sound);
			}
			switch (current_step) {
				case 0: {
					WaitForTimer(2.0f);
					break;
				}
				case 1: {
					if (!wait_for_timer) {
						AddTextToScreenOutput("(press ENTER to skip)\n\n\t\t\t\t\t\tTrophy Personal BIOS v2.34\n\t\t\t\t\t\tCopyright (C) 1987-94 Trophy Software\n\n");
						PlaySound(*beep_sound);
					}
					WaitForTimer(1.0f);
					break;
				}
				case 2: {
					if (!wait_for_timer) {
						AddTextToScreenOutput("Initializing BOOT sequence");
						PlaySound(*beep_sound);
						wait_for_timer = true;
					}

					if (intro_substep_wait > 0.0f) {
						intro_substep_wait -= GetFrameTime();
					} else if (intro_substep_wait <= 0.0f) {
						intro_substep_count++;

						if (intro_substep_count >= 4) {
							current_step++;
							wait_for_timer = false;
							intro_substep_count = 0;
						} else {
							AddTextToScreenOutput(".");
							intro_substep_wait = 0.5f;
						}
					}
					//WaitForTimer(1.5f);
					break;
				}
				case 3: {
					if (!intro_substep_done) {
						if (!wait_for_timer) {
							AddTextToScreenOutput("\nMemory Check : \t\t");
							PlaySound(*beep_sound);
							wait_for_timer = true;
						}
						if (boot1_mem_check < (float)boot1_mem_check_cap) {
							boot1_mem_check += 100000.0f * GetFrameTime();
							boot1_mem_check = E_Math_Clamp(boot1_mem_check, 0.0f, (float)boot1_mem_check_cap);

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
						} else if (boot1_mem_check >= (float)boot1_mem_check_cap) {
							boot1_mem_check = (int)boot1_mem_check_cap;

							wait_for_timer = false;
							intro_substep_done = true;

							AddTextToScreenOutput("kb\tOK\n\n");
							PlaySound(*beep_sound);
						}
					}
					if (intro_substep_done) {
						WaitForTimer(2.0f);
					}
					break;
				}
				case 4: {
					if (!wait_for_timer) {
						AddTextToScreenOutput("Booting Starlight Personal...\n");
						PlaySound(*beep_sound);
					}
					WaitForTimer(2.0f);
					break;
				}
				case 5: {
					current_step = 0;
					wait_for_timer = false;
					current_subscene = SUBSCENE_LOADING;
					break;
				}
				default: {
					break;
				}
			}
			break;
		}
		case (int)SUBSCENE_LOADING: {
			loading_bar_x -= 200.0f * GetFrameTime();
			if (floor(loading_bar_x) <= -starlight_loading_bar->width) {
				loading_bar_x = 0;
			}

			switch(current_step) {
				case 0: {
					WaitForTimer(3.0f);
					break;
				}
				case 1: {
					if (!wait_for_timer) {
						G_HardDriveSound(true);
					}
					WaitForTimer(5.0f);
					break;
				}
				case 2: {
					G_HardDriveSound(false);
					G_Cursor_SetVisibility(true);
					E_Core_SetScene(NULL);
					break;
				}
			}
			break;
		}
	}
}

void S_BootDraw() {
	ClearBackground(BLACK);

	switch(current_subscene) {
		case (int)SUBSCENE_SPLASH: {
			if(current_step == 1) {
				DrawTexturePro(
					*hat_logo,
					(Rectangle){0, 0, hat_logo->width, hat_logo->height},
					(Rectangle){
						M_BASE_WIDTH / 2, M_BASE_HEIGHT / 2,
						hat_logo->width * 2, hat_logo->height * 2
					},
					(Vector2){hat_logo->width, hat_logo->height},
					0.0f, WHITE
				);
			}
			break;
		}
		case (int)SUBSCENE_INTRO: {
			if (current_step >= 1 && trophy_graphic != NULL) {
				DrawTexture(*trophy_graphic, 16, 43, WHITE);
			}
			DrawTextEx(system_font != NULL ? *system_font : GetFontDefault(), screen_output, (Vector2){15, 15}, 16, 0, GRAY);
			break;
		}
		case (int)SUBSCENE_LOADING: {
			/* 0, 459 */
			if (current_step == 1) {
				DrawTexture(*starlight_bg, 0, 0, WHITE);
				DrawTextureTiled(
					*starlight_loading_bar,
					(Rectangle){0, 0, starlight_loading_bar->width, starlight_loading_bar->height},
					(Rectangle){floorf(loading_bar_x), M_BASE_HEIGHT - starlight_loading_bar->height, starlight_loading_bar->width * 2, starlight_loading_bar->height},
					(Vector2){0.0f, 0.0f},
					0.0f, 1.0f, WHITE
				);
			}
			//DrawTextEx(system_font != NULL ? *system_font : GetFontDefault(), screen_output, (Vector2){15, 15}, 16, 0, GRAY);
			break;
		}
	}
	//DrawText(TextFormat("%i, %f", current_step, timer), 10, 10, 10, RED);
}

void S_BootClose() {
	beep_sound = NULL;
	system_font = NULL;

	M_Assets_CloseAssetByLabel("boot/gfx/starlight_loadbar");
	starlight_loading_bar = NULL;
	M_Assets_CloseAssetByLabel("boot/gfx/starlight_bg");
	starlight_bg = NULL;
	M_Assets_CloseAssetByLabel("boot/gfx/trophy");
	trophy_graphic = NULL;
	M_Assets_CloseAssetByLabel("boot/gfx/hat_logo");
	hat_logo = NULL;

	ClearScreenOutput();
}