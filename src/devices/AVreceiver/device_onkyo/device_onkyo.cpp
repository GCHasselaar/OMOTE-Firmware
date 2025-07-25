#include "applicationInternal/commandHandler.h"
#include "applicationInternal/hardware/hardwarePresenter.h"
#include "device_onkyo.h"

uint16_t ONKYO_POWER;
uint16_t ONKYO_BDDVD;
uint16_t ONKYO_CBLSAT;
uint16_t ONKYO_GAME;
uint16_t ONKYO_STRMBOX;
uint16_t ONKYO_PC;
uint16_t ONKYO_AUX;
uint16_t ONKYO_CD;
uint16_t ONKYO_TV;
uint16_t ONKYO_PHONO;
uint16_t ONKYO_TUNER;
uint16_t ONKYO_NET;
uint16_t ONKYO_BT;

uint16_t ONKYO_QUICKMENU;
uint16_t ONKYO_INFO;
uint16_t ONKYO_UP;
uint16_t ONKYO_LEFT;
uint16_t ONKYO_ENTER;
uint16_t ONKYO_RIGHT;
uint16_t ONKYO_DOWN;
uint16_t ONKYO_SETTINGS;
uint16_t ONKYO_RETURN;

uint16_t ONKYO_VOLUP;
uint16_t ONKYO_VOLDOWN;
uint16_t ONKYO_MUTE;

uint16_t ONKYO_MODE_MOVIETV;
uint16_t ONKYO_MODE_MUSIC;
uint16_t ONKYO_MODE_GAME;
uint16_t ONKYO_PREV;
uint16_t ONKYO_PLAY;
uint16_t ONKYO_NEXT;
uint16_t ONKYO_SHUFFLE;
uint16_t ONKYO_MEMORY;
uint16_t ONKYO_MODE;

void register_device_onkyo()
{
    register_command(&ONKYO_POWER,        makeCommandData(IR, {std::to_string(IR_PROTOCOL_NEC),   "0x4B36D32C"}));
    register_command(&ONKYO_BDDVD,        makeCommandData(IR, {std::to_string(IR_PROTOCOL_NEC),   "0x4B3631CE"}));
    register_command(&ONKYO_CBLSAT,       makeCommandData(IR, {std::to_string(IR_PROTOCOL_NEC),   "0x4BB6708F"}));
    register_command(&ONKYO_GAME,         makeCommandData(IR, {std::to_string(IR_PROTOCOL_NEC),   "0x4BB6B04F"}));
    register_command(&ONKYO_STRMBOX,      makeCommandData(IR, {std::to_string(IR_PROTOCOL_NEC),   "0x4BB6B04F"}));
    register_command(&ONKYO_PC,           makeCommandData(IR, {std::to_string(IR_PROTOCOL_NEC),   "0x4BB639C6"}));
    register_command(&ONKYO_AUX,          makeCommandData(IR, {std::to_string(IR_PROTOCOL_NEC),   "0x4BB6F906"}));
    register_command(&ONKYO_CD,           makeCommandData(IR, {std::to_string(IR_PROTOCOL_NEC),   "0x4BB6906F"}));
    register_command(&ONKYO_TV,           makeCommandData(IR, {std::to_string(IR_PROTOCOL_NEC),   "0x4BB612ED"}));
    register_command(&ONKYO_PHONO,        makeCommandData(IR, {std::to_string(IR_PROTOCOL_NEC),   "0x4BB650AF"}));
    register_command(&ONKYO_TUNER,        makeCommandData(IR, {std::to_string(IR_PROTOCOL_NEC),   "0x4BB6D02F"}));
    register_command(&ONKYO_NET,          makeCommandData(IR, {std::to_string(IR_PROTOCOL_NEC),   "0x4B40E11E"}));
    register_command(&ONKYO_BT,           makeCommandData(IR, {std::to_string(IR_PROTOCOL_NEC),   "0x4B780A70"}));
    register_command(&ONKYO_QUICKMENU,    makeCommandData(IR, {std::to_string(IR_PROTOCOL_NEC),   "0x4B36CA35"}));
    register_command(&ONKYO_INFO,         makeCommandData(IR, {std::to_string(IR_PROTOCOL_NEC),   "0x4B36AA55"}));
    register_command(&ONKYO_UP,           makeCommandData(IR, {std::to_string(IR_PROTOCOL_NEC),   "0x4BB641BE"}));
    register_command(&ONKYO_LEFT,         makeCommandData(IR, {std::to_string(IR_PROTOCOL_NEC),   "0x4BB621DE"}));
    register_command(&ONKYO_ENTER,        makeCommandData(IR, {std::to_string(IR_PROTOCOL_NEC),   "0x4BB6E916"}));
    register_command(&ONKYO_RIGHT,        makeCommandData(IR, {std::to_string(IR_PROTOCOL_NEC),   "0x4BB6A15E"}));
    register_command(&ONKYO_DOWN,         makeCommandData(IR, {std::to_string(IR_PROTOCOL_NEC),   "0x4BB6C13E"}));
    register_command(&ONKYO_SETTINGS,     makeCommandData(IR, {std::to_string(IR_PROTOCOL_NEC),   "0x4B36DB24"}));
    register_command(&ONKYO_RETURN,       makeCommandData(IR, {std::to_string(IR_PROTOCOL_NEC),   "0x4B362AD5"}));
    register_command(&ONKYO_VOLUP,        makeCommandData(IR, {std::to_string(IR_PROTOCOL_NEC),   "0x4BB640BF"}));
    register_command(&ONKYO_VOLDOWN,      makeCommandData(IR, {std::to_string(IR_PROTOCOL_NEC),   "0x4BB6C03F"}));
    register_command(&ONKYO_MUTE,         makeCommandData(IR, {std::to_string(IR_PROTOCOL_NEC),   "0x4BB6A05F"}));
    register_command(&ONKYO_MODE_MOVIETV, makeCommandData(IR, {std::to_string(IR_PROTOCOL_NEC),   "0x4B350BF4"}));
    register_command(&ONKYO_MODE_MUSIC,   makeCommandData(IR, {std::to_string(IR_PROTOCOL_NEC),   "0x4B358B74"}));
    register_command(&ONKYO_MODE_GAME,    makeCommandData(IR, {std::to_string(IR_PROTOCOL_NEC),   "0x4B354BB4"}));
    register_command(&ONKYO_PREV,         makeCommandData(IR, {std::to_string(IR_PROTOCOL_NEC),   "0x4B4009F6"}));
    register_command(&ONKYO_PLAY,         makeCommandData(IR, {std::to_string(IR_PROTOCOL_NEC),   "0x4B983AC5"}));
    register_command(&ONKYO_NEXT,         makeCommandData(IR, {std::to_string(IR_PROTOCOL_NEC),   "0x4B40F10E"}));
    register_command(&ONKYO_SHUFFLE,      makeCommandData(IR, {std::to_string(IR_PROTOCOL_NEC),   "0x4B98FA05"}));
    register_command(&ONKYO_MEMORY,       makeCommandData(IR, {std::to_string(IR_PROTOCOL_NEC),   "0x4B404BB4"}));
    register_command(&ONKYO_MODE,         makeCommandData(IR, {std::to_string(IR_PROTOCOL_NEC),   "0x4B40CB34"}));
}

void turn_onkyo_off()
{
    if (get_userDeviceStatus("ONKYO"))
    {
        executeCommand(ONKYO_POWER);
        set_userDeviceStatus("ONKYO",false);
    }
}

void turn_onkyo_on()
{
    if (!get_userDeviceStatus("ONKYO")){
        executeCommand(ONKYO_POWER);
        set_userDeviceStatus("ONKYO",true);
    }
}

void set_source(uint16_t command)
{
    executeCommand(command);
    set_userDeviceStatus("ONKYO",true);
}

void exec_onkyo_command(uint16_t command)
{
    if (command != ONKYO_POWER && get_userDeviceStatus("ONKYO"))
    {
        executeCommand(command);
    }
}
