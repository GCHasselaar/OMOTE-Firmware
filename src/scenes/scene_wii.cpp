#include <map>
#include "scenes/scene_wii.h"
#include "applicationInternal/commandHandler.h"
#include "applicationInternal/keys.h"
#include "applicationInternal/scenes/sceneRegistry.h"
#include "applicationInternal/hardware/hardwarePresenter.h"

// devices
#include "devices/AVreceiver/device_onkyo/device_onkyo.h"
#include "devices/mediaPlayer/device_sonybluray/device_sonybluray.h"
#include "devices/TV/device_optoma/device_optoma.h"

uint16_t SCENE_WII;
uint16_t SCENE_WII_FORCE;

std::map<char, repeatModes> key_repeatModes_wii;
std::map<char, uint16_t> key_commands_short_wii;
std::map<char, uint16_t> key_commands_long_wii;

void scene_setKeys_wii() {
  key_repeatModes_wii = {};
  key_commands_short_wii = {};
  key_commands_long_wii = {};
}

void scene_start_sequence_wii(void) {
  set_source(ONKYO_TV);
  delay(1000);
  executeCommand(OPTOMA_ON);
}

void scene_end_sequence_wii(void) {}

std::string scene_name_wii = "WII";

void register_scene_wii(void) {
  register_command(&SCENE_WII      , makeCommandData(SCENE, {scene_name_wii}));
  register_command(&SCENE_WII_FORCE, makeCommandData(SCENE, {scene_name_wii, "FORCE"}));

  register_scene(
    scene_name_wii,
    & scene_setKeys_wii,
    & scene_start_sequence_wii,
    & scene_end_sequence_wii,
    & key_repeatModes_wii,
    & key_commands_short_wii,
    & key_commands_long_wii,
    NULL,
    SCENE_WII);
}
