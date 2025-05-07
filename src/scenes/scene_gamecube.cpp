#include <map>
#include "scenes/scene_gamecube.h"
#include "applicationInternal/commandHandler.h"
#include "applicationInternal/keys.h"
#include "applicationInternal/scenes/sceneRegistry.h"
#include "applicationInternal/hardware/hardwarePresenter.h"

// devices
#include "devices/AVreceiver/device_onkyo/device_onkyo.h"
#include "devices/mediaPlayer/device_sonybluray/device_sonybluray.h"
#include "devices/TV/device_optoma/device_optoma.h"

uint16_t SCENE_GAMECUBE;
uint16_t SCENE_GAMECUBE_FORCE;

std::map<char, repeatModes> key_repeatModes_gamecube;
std::map<char, uint16_t> key_commands_short_gamecube;
std::map<char, uint16_t> key_commands_long_gamecube;

void scene_setKeys_gamecube() {
  key_repeatModes_gamecube = {};
  key_commands_short_gamecube = {};
  key_commands_long_gamecube = {};
}

void scene_start_sequence_gamecube(void) {
  executeCommand(BLURAY_ON);
  delay(500);
  executeCommand(ONKYO_POWER);
  delay(500);
  executeCommand(OPTOMA_OFF);
  delay(500);
}

void scene_end_sequence_gamecube(void) {}

std::string scene_name_gamecube = "Gamecube";

void register_scene_gamecube(void) {
  register_command(&SCENE_GAMECUBE      , makeCommandData(SCENE, {scene_name_gamecube}));
  register_command(&SCENE_GAMECUBE_FORCE, makeCommandData(SCENE, {scene_name_gamecube, "FORCE"}));

  register_scene(
    scene_name_gamecube,
    & scene_setKeys_gamecube,
    & scene_start_sequence_gamecube,
    & scene_end_sequence_gamecube,
    & key_repeatModes_gamecube,
    & key_commands_short_gamecube,
    & key_commands_long_gamecube,
    NULL,
    SCENE_GAMECUBE);
}
