#include <map>
#include "scenes/scene_bluray.h"
#include "applicationInternal/commandHandler.h"
#include "applicationInternal/keys.h"
#include "applicationInternal/scenes/sceneRegistry.h"
#include "applicationInternal/hardware/hardwarePresenter.h"

// devices
#include "devices/AVreceiver/device_onkyo/device_onkyo.h"
#include "devices/mediaPlayer/device_sonybluray/device_sonybluray.h"
#include "devices/TV/device_optoma/device_optoma.h"

uint16_t SCENE_BLURAY;
uint16_t SCENE_BLURAY_FORCE;

std::map<char, repeatModes> key_repeatModes_bluray;
std::map<char, uint16_t> key_commands_short_bluray;
std::map<char, uint16_t> key_commands_long_bluray;

void scene_setKeys_bluray() {
  key_repeatModes_bluray = {};
  key_commands_short_bluray = {};
  key_commands_long_bluray = {};
}

void scene_start_sequence_bluray(void) {
  executeCommand(BLURAY_ON);
  delay(500);
  executeCommand(ONKYO_POWER);
  delay(500);
  executeCommand(OPTOMA_OFF);
  delay(500);
}

void scene_end_sequence_bluray(void) {}

std::string scene_name_bluray = "Bluray";

void register_scene_bluray(void) {
  register_command(&SCENE_BLURAY      , makeCommandData(SCENE, {scene_name_bluray}));
  register_command(&SCENE_BLURAY_FORCE, makeCommandData(SCENE, {scene_name_bluray, "FORCE"}));

  register_scene(
    scene_name_bluray,
    & scene_setKeys_bluray,
    & scene_start_sequence_bluray,
    & scene_end_sequence_bluray,
    & key_repeatModes_bluray,
    & key_commands_short_bluray,
    & key_commands_long_bluray,
    NULL,
    SCENE_BLURAY);
}
