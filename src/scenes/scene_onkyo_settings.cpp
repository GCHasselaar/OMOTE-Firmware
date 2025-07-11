#include <map>
#include "scenes/scene_onkyo_settings.h"
#include "applicationInternal/commandHandler.h"
#include "applicationInternal/keys.h"
#include "applicationInternal/scenes/sceneRegistry.h"
#include "applicationInternal/hardware/hardwarePresenter.h"

// devices
#include "devices/AVreceiver/device_onkyo/device_onkyo.h"
#include "devices/TV/device_optoma/device_optoma.h"

uint16_t SCENE_ONKYO_SETTINGS;
uint16_t SCENE_ONKYO_SETTINGS_FORCE;

std::map<char, repeatModes> key_repeatModes_onkyo_settings;
std::map<char, uint16_t> key_commands_short_onkyo_settings;
std::map<char, uint16_t> key_commands_long_onkyo_settings;

void scene_setKeys_onkyo_settings() {
  key_repeatModes_onkyo_settings = {
    {KEY_CONF, SHORT},
    {KEY_INFO, SHORT},
    {KEY_UP, SHORT},
    {KEY_LEFT, SHORT},
    {KEY_OK, SHORT},
    {KEY_RIGHT, SHORT},
    {KEY_DOWN, SHORT},
    {KEY_BACK, SHORT},
    {KEY_SRC, SHORT}
  };

  key_commands_short_onkyo_settings = {
    {KEY_CONF, ONKYO_QUICKMENU},
    {KEY_INFO, ONKYO_INFO},
    {KEY_UP, ONKYO_UP},
    {KEY_LEFT, ONKYO_LEFT},
    {KEY_OK, ONKYO_ENTER},
    {KEY_RIGHT, ONKYO_RIGHT},
    {KEY_DOWN, ONKYO_DOWN},
    {KEY_BACK, ONKYO_SETTINGS},
    {KEY_SRC, ONKYO_RETURN}
  };
  key_commands_long_onkyo_settings = {};
}

void scene_start_sequence_onkyo_settings(void) {
  turn_onkyo_on();
  delay(1000);
  executeCommand(ONKYO_SETTINGS);
  delay(1000);
  executeCommand(OPTOMA_ON);
}

void scene_end_sequence_onkyo_settings(void) {}

std::string scene_name_onkyo_settings = "(Onkyo)";

void register_scene_onkyo_settings(void) {
  register_command(&SCENE_ONKYO_SETTINGS      , makeCommandData(SCENE, {scene_name_onkyo_settings}));
  register_command(&SCENE_ONKYO_SETTINGS_FORCE, makeCommandData(SCENE, {scene_name_onkyo_settings, "FORCE"}));

  register_scene(
    scene_name_onkyo_settings,
    & scene_setKeys_onkyo_settings,
    & scene_start_sequence_onkyo_settings,
    & scene_end_sequence_onkyo_settings,
    & key_repeatModes_onkyo_settings,
    & key_commands_short_onkyo_settings,
    & key_commands_long_onkyo_settings,
    NULL,
    SCENE_ONKYO_SETTINGS);
}
