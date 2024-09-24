#ifndef G_SCENES_H
#define G_SCENES_H

#include "engine/e_scene.h"

extern E_Scene* G_SCENE_TEST;
extern E_Scene* G_SCENE_BOOT;

void G_Scenes_Populate();
void G_Scenes_Close();

#endif