#pragma once

#include <string>
#include <stdint.h>

extern uint16_t SCENE_ONKYO_SETTINGS;
// FORCE sends the start sequence again even if scene is already active
extern uint16_t SCENE_ONKYO_SETTINGS_FORCE;

extern std::string scene_name_onkyo_settings;
void register_scene_onkyo_settings_commands(void);
void register_scene_onkyo_settings(void);
