#include <map>
#include "scenes/scene_optoma_settings.h"
#include "applicationInternal/commandHandler.h"
#include "applicationInternal/keys.h"
#include "applicationInternal/scenes/sceneRegistry.h"
#include "applicationInternal/hardware/hardwarePresenter.h"

// devices
#include "devices/TV/device_optoma/device_optoma.h"

uint16_t SCENE_OPTOMA_SETTINGS;
uint16_t SCENE_OPTOMA_SETTINGS_FORCE;

std::map<char, repeatModes> key_repeatModes_optoma_settings;
std::map<char, uint16_t> key_commands_short_optoma_settings;
std::map<char, uint16_t> key_commands_long_optoma_settings;

void scene_setKeys_optoma_settings() {
  key_repeatModes_optoma_settings = {
    {KEY_UP, SHORT},
    {KEY_LEFT, SHORT},
    {KEY_OK, SHORT},
    {KEY_RIGHT, SHORT},
    {KEY_DOWN, SHORT},
    {KEY_BACK, SHORT}
  };

  key_commands_short_optoma_settings = {
    {KEY_UP, OPTOMA_UP},
    {KEY_LEFT, OPTOMA_LEFT},
    {KEY_OK, OPTOMA_ENTER},
    {KEY_RIGHT, OPTOMA_RIGHT},
    {KEY_DOWN, OPTOMA_DOWN},
    {KEY_BACK, OPTOMA_MENU}
  };
  key_commands_long_optoma_settings = {};
}

void scene_start_sequence_optoma_settings(void) {
  executeCommand(OPTOMA_ON);
}

void scene_end_sequence_optoma_settings(void) {}

std::string scene_name_optoma_settings = "(Optoma)";

void register_scene_optoma_settings(void) {
  register_command(&SCENE_OPTOMA_SETTINGS      , makeCommandData(SCENE, {scene_name_optoma_settings}));
  register_command(&SCENE_OPTOMA_SETTINGS_FORCE, makeCommandData(SCENE, {scene_name_optoma_settings, "FORCE"}));

  register_scene(
    scene_name_optoma_settings,
    & scene_setKeys_optoma_settings,
    & scene_start_sequence_optoma_settings,
    & scene_end_sequence_optoma_settings,
    & key_repeatModes_optoma_settings,
    & key_commands_short_optoma_settings,
    & key_commands_long_optoma_settings,
    NULL,
    SCENE_OPTOMA_SETTINGS);
}
