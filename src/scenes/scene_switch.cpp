#include <map>
#include "scenes/scene_switch.h"
#include "applicationInternal/commandHandler.h"
#include "applicationInternal/keys.h"
#include "applicationInternal/scenes/sceneRegistry.h"
#include "applicationInternal/hardware/hardwarePresenter.h"

// devices
#include "devices/AVreceiver/device_onkyo/device_onkyo.h"
#include "devices/mediaPlayer/device_sonybluray/device_sonybluray.h"
#include "devices/TV/device_optoma/device_optoma.h"

uint16_t SCENE_SWITCH;
uint16_t SCENE_SWITCH_FORCE;

std::map<char, repeatModes> key_repeatModes_switch;
std::map<char, uint16_t> key_commands_short_switch;
std::map<char, uint16_t> key_commands_long_switch;

void scene_setKeys_switch() {
  key_repeatModes_switch = {};
  key_commands_short_switch = {};
  key_commands_long_switch = {};
}

void scene_start_sequence_switch(void) {
  set_source(ONKYO_GAME);
  delay(250);
  executeCommand(OPTOMA_ON);
}

void scene_end_sequence_switch(void) {}

std::string scene_name_switch = "Switch";

void register_scene_switch(void) {
  register_command(&SCENE_SWITCH      , makeCommandData(SCENE, {scene_name_switch}));
  register_command(&SCENE_SWITCH_FORCE, makeCommandData(SCENE, {scene_name_switch, "FORCE"}));

  register_scene(
    scene_name_switch,
    & scene_setKeys_switch,
    & scene_start_sequence_switch,
    & scene_end_sequence_switch,
    & key_repeatModes_switch,
    & key_commands_short_switch,
    & key_commands_long_switch,
    NULL,
    SCENE_SWITCH);
}
