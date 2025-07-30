#include <map>
#include "scenes/scene_switch2.h"
#include "applicationInternal/commandHandler.h"
#include "applicationInternal/keys.h"
#include "applicationInternal/scenes/sceneRegistry.h"
#include "applicationInternal/hardware/hardwarePresenter.h"

// devices
#include "devices/AVreceiver/device_onkyo/device_onkyo.h"
#include "devices/mediaPlayer/device_sonybluray/device_sonybluray.h"
#include "devices/TV/device_optoma/device_optoma.h"

uint16_t SCENE_SWITCH2;
uint16_t SCENE_SWITCH2_FORCE;

std::map<char, repeatModes> key_repeatModes_switch2;
std::map<char, uint16_t> key_commands_short_switch2;
std::map<char, uint16_t> key_commands_long_switch2;

void scene_setKeys_switch2() {
  key_repeatModes_switch2 = {};
  key_commands_short_switch2 = {};
  key_commands_long_switch2 = {};
}

void scene_start_sequence_switch2(void) {
  set_source(ONKYO_PHONO);
  delay(500);
  executeCommand(OPTOMA_ON);
}

void scene_end_sequence_switch2(void) {}

std::string scene_name_switch2 = "Switch 2";

void register_scene_switch2(void) {
  register_command(&SCENE_SWITCH2      , makeCommandData(SCENE, {scene_name_switch2}));
  register_command(&SCENE_SWITCH2_FORCE, makeCommandData(SCENE, {scene_name_switch2, "FORCE"}));

  register_scene(
    scene_name_switch2,
    & scene_setKeys_switch2,
    & scene_start_sequence_switch2,
    & scene_end_sequence_switch2,
    & key_repeatModes_switch2,
    & key_commands_short_switch2,
    & key_commands_long_switch2,
    NULL,
    SCENE_SWITCH2);
}
