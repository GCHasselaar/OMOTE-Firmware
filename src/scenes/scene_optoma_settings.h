#pragma once

#include <string>
#include <stdint.h>

extern uint16_t SCENE_OPTOMA_SETTINGS;
// FORCE sends the start sequence again even if scene is already active
extern uint16_t SCENE_OPTOMA_SETTINGS_FORCE;

extern std::string scene_name_optoma_settings;
void register_scene_optoma_settings_commands(void);
void register_scene_optoma_settings(void);
