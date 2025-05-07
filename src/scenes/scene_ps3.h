#pragma once

#include <string>
#include <stdint.h>

extern uint16_t SCENE_PS3;
// FORCE sends the start sequence again even if scene is already active
extern uint16_t SCENE_PS3_FORCE;

extern std::string scene_name_ps3;
void register_scene_ps3_commands(void);
void register_scene_ps3(void);
