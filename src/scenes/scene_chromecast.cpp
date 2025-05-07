#include <map>
#include "scenes/scene_chromecast.h"
#include "applicationInternal/commandHandler.h"
#include "applicationInternal/keys.h"
#include "applicationInternal/scenes/sceneRegistry.h"
#include "applicationInternal/hardware/hardwarePresenter.h"

// devices
#include "devices/AVreceiver/device_onkyo/device_onkyo.h"
#include "devices/mediaPlayer/device_sonybluray/device_sonybluray.h"
#include "devices/TV/device_optoma/device_optoma.h"

uint16_t SCENE_CHROMECAST;
uint16_t SCENE_CHROMECAST_FORCE;

std::map<char, repeatModes> key_repeatModes_chromecast;
std::map<char, uint16_t> key_commands_short_chromecast;
std::map<char, uint16_t> key_commands_long_chromecast;

void scene_setKeys_chromecast() {
  key_repeatModes_chromecast = {};
  key_commands_short_chromecast = {};
  key_commands_long_chromecast = {};
}

void scene_start_sequence_chromecast(void) {
  executeCommand(BLURAY_ON);
  delay(500);
  executeCommand(ONKYO_POWER);
  delay(500);
  executeCommand(OPTOMA_OFF);
  delay(500);
}

void scene_end_sequence_chromecast(void) {}

std::string scene_name_chromecast = "Chromecast";

void register_scene_chromecast(void) {
  register_command(&SCENE_CHROMECAST      , makeCommandData(SCENE, {scene_name_chromecast}));
  register_command(&SCENE_CHROMECAST_FORCE, makeCommandData(SCENE, {scene_name_chromecast, "FORCE"}));

  register_scene(
    scene_name_chromecast,
    & scene_setKeys_chromecast,
    & scene_start_sequence_chromecast,
    & scene_end_sequence_chromecast,
    & key_repeatModes_chromecast,
    & key_commands_short_chromecast,
    & key_commands_long_chromecast,
    NULL,
    SCENE_CHROMECAST);
}
