#include <stdlib.h>
#include <stdio.h>
#include "e_scene.h"

E_Scene* E_Scene_Create(const char* label, void (*init_function), void (*update_function), void (*draw_function), void (*close_function)) {
	E_Scene* scene = (E_Scene*)malloc(sizeof(E_Scene));

	scene->init = init_function;
	scene->update = update_function;
	scene->draw = draw_function;
	scene->close = close_function;

	scene->label = label;
	printf("E: Creating scene with label \"%s\"\n", label);

	return scene;
}