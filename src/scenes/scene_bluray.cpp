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
  key_repeatModes_bluray = {
    {KEY_STOP, SHORT},
    {KEY_REWI, SHORTorLONG},
    {KEY_PLAY, SHORT},
    {KEY_FORW, SHORTorLONG},

    {KEY_CONF, SHORT},
    {KEY_INFO, SHORT},
    {KEY_UP, SHORT},
    {KEY_LEFT, SHORT},
    {KEY_OK, SHORTorLONG},
    {KEY_RIGHT, SHORT},
    {KEY_DOWN, SHORT},
    {KEY_BACK, SHORT},
    {KEY_SRC, SHORT},

    {KEY_REC, SHORT},

    {KEY_RED, SHORT},
    {KEY_GREEN, SHORT},
    {KEY_YELLO, SHORT},
    {KEY_BLUE, SHORT}
  };

  key_commands_short_bluray = {
    {KEY_STOP, BLURAY_STOP},
    {KEY_REWI, BLURAY_REWIND},
    {KEY_PLAY, BLURAY_PLAY},
    {KEY_FORW, BLURAY_FORWARD},

    {KEY_CONF, BLURAY_TOP_MENU},
    {KEY_INFO, BLURAY_POP_UP},
    {KEY_UP, BLURAY_UP},
    {KEY_LEFT, BLURAY_LEFT},
    {KEY_OK, BLURAY_CENTER},
    {KEY_RIGHT, BLURAY_RIGHT},
    {KEY_DOWN, BLURAY_DOWN},
    {KEY_BACK, BLURAY_RETURN},
    {KEY_SRC, BLURAY_OPTIONS},

    {KEY_REC, BLURAY_EJECT},

    {KEY_RED, BLURAY_RED},
    {KEY_GREEN, BLURAY_GREEN},
    {KEY_YELLO, BLURAY_YELLOW},
    {KEY_BLUE, BLURAY_BLUE}
  };
  key_commands_long_bluray = {
    {KEY_OK, BLURAY_HOME},
    {KEY_REWI, BLURAY_PREVIOUS},
    {KEY_FORW, BLURAY_NEXT},
  };
}

void scene_start_sequence_bluray(void) {
  set_source(ONKYO_BDDVD);
  delay(500);
  executeCommand(OPTOMA_ON);
  delay(500);
  turn_bluray_on();
}

void scene_end_sequence_bluray(void) {
  turn_bluray_off();
}

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
