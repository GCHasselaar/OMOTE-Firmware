#include <map>
#include "scenes/scene_pc.h"
#include "applicationInternal/commandHandler.h"
#include "applicationInternal/keys.h"
#include "applicationInternal/scenes/sceneRegistry.h"
#include "applicationInternal/hardware/hardwarePresenter.h"

// devices
#include "devices/AVreceiver/device_onkyo/device_onkyo.h"
#include "devices/TV/device_optoma/device_optoma.h"

uint16_t SCENE_PC;
uint16_t SCENE_PC_FORCE;

std::map<char, repeatModes> key_repeatModes_pc;
std::map<char, uint16_t> key_commands_short_pc;
std::map<char, uint16_t> key_commands_long_pc;

void scene_setKeys_pc() {
  key_repeatModes_pc = {};
  key_commands_short_pc = {};
  key_commands_long_pc = {};
}

void scene_start_sequence_pc(void) {
  set_source(ONKYO_PC);
  delay(500);
  executeCommand(OPTOMA_ON);
}

void scene_end_sequence_pc(void) {}

std::string scene_name_pc = "PC";

void register_scene_pc(void) {
  register_command(&SCENE_PC      , makeCommandData(SCENE, {scene_name_pc}));
  register_command(&SCENE_PC_FORCE, makeCommandData(SCENE, {scene_name_pc, "FORCE"}));

  register_scene(
    scene_name_pc,
    & scene_setKeys_pc,
    & scene_start_sequence_pc,
    & scene_end_sequence_pc,
    & key_repeatModes_pc,
    & key_commands_short_pc,
    & key_commands_long_pc,
    NULL,
    SCENE_PC);
}
