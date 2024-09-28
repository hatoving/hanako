#ifndef G_STATE_H
#define G_STATE_H

#include <stdbool.h>
#include <stdint.h>

typedef struct {
	uint8_t first_time;
	float time_played; // in seconds
} G_State;
extern G_State* G_STATE_CURRENT;

void G_State_Load(uint8_t slot);
void G_State_Save(uint8_t slot);

G_State* G_State_CreateDefault();

#endif