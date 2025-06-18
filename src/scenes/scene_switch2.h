#pragma once

#include <string>
#include <stdint.h>

extern uint16_t SCENE_SWITCH2;
// FORCE sends the start sequence again even if scene is already active
extern uint16_t SCENE_SWITCH2_FORCE;

extern std::string scene_name_switch2;
void register_scene_switch2_commands(void);
void register_scene_switch2(void);
