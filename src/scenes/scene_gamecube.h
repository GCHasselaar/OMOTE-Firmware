#pragma once

#include <string>
#include <stdint.h>

extern uint16_t SCENE_GAMECUBE;
// FORCE sends the start sequence again even if scene is already active
extern uint16_t SCENE_GAMECUBE_FORCE;

extern std::string scene_name_gamecube;
void register_scene_gamecube_commands(void);
void register_scene_gamecube(void);
