#pragma once

#include <string>
#include <stdint.h>

extern uint16_t SCENE_PC;
// FORCE sends the start sequence again even if scene is already active
extern uint16_t SCENE_PC_FORCE;

extern std::string scene_name_pc;
void register_scene_pc_commands(void);
void register_scene_pc(void);
