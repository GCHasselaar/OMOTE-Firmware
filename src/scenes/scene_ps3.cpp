#include <map>
#include "scenes/scene_ps3.h"
#include "applicationInternal/commandHandler.h"
#include "applicationInternal/keys.h"
#include "applicationInternal/scenes/sceneRegistry.h"
#include "applicationInternal/hardware/hardwarePresenter.h"

// devices
#include "devices/AVreceiver/device_onkyo/device_onkyo.h"
#include "devices/mediaPlayer/device_sonybluray/device_sonybluray.h"
#include "devices/TV/device_optoma/device_optoma.h"

uint16_t SCENE_PS3;
uint16_t SCENE_PS3_FORCE;

std::map<char, repeatModes> key_repeatModes_ps3;
std::map<char, uint16_t> key_commands_short_ps3;
std::map<char, uint16_t> key_commands_long_ps3;

void scene_setKeys_ps3() {
  key_repeatModes_ps3 = {};
  key_commands_short_ps3 = {};
  key_commands_long_ps3 = {};
}

void scene_start_sequence_ps3(void) {
  set_source(ONKYO_STRMBOX);
  delay(250);
  executeCommand(OPTOMA_ON);
}

void scene_end_sequence_ps3(void) {}

std::string scene_name_ps3 = "PS3";

void register_scene_ps3(void) {
  register_command(&SCENE_PS3      , makeCommandData(SCENE, {scene_name_ps3}));
  register_command(&SCENE_PS3_FORCE, makeCommandData(SCENE, {scene_name_ps3, "FORCE"}));

  register_scene(
    scene_name_ps3,
    & scene_setKeys_ps3,
    & scene_start_sequence_ps3,
    & scene_end_sequence_ps3,
    & key_repeatModes_ps3,
    & key_commands_short_ps3,
    & key_commands_long_ps3,
    NULL,
    SCENE_PS3);
}
