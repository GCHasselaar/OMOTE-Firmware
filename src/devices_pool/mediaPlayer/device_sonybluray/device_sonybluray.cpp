#include "applicationInternal/commandHandler.h"
#include "applicationInternal/hardware/hardwarePresenter.h"
#include "device_sonybluray.h"

uint16_t BLURAY_EJECT;
uint16_t BLURAY_SOURCE;
uint16_t BLURAY_TV_POWER;
uint16_t BLURAY_POWER;
uint16_t BLURAY_RED;
uint16_t BLURAY_GREEN;
uint16_t BLURAY_YELLOW;
uint16_t BLURAY_BLUE;
uint16_t BLURAY_TOP_MENU;
uint16_t BLURAY_POP_UP;
uint16_t BLURAY_UP;
uint16_t BLURAY_LEFT;
uint16_t BLURAY_CENTER;
uint16_t BLURAY_RIGHT;
uint16_t BLURAY_DOWN;
uint16_t BLURAY_RETURN;
uint16_t BLURAY_OPTIONS;
uint16_t BLURAY_HOME;
uint16_t BLURAY_LIKE;
uint16_t BLURAY_NETFLIX;
uint16_t BLURAY_REWIND;
uint16_t BLURAY_PLAY;
uint16_t BLURAY_FORWARD;
uint16_t BLURAY_PREVIOUS;
uint16_t BLURAY_PAUSE;
uint16_t BLURAY_STOP;
uint16_t BLURAY_NEXT;
uint16_t BLURAY_SUBTITLE;
uint16_t BLURAY_AUDIO;
uint16_t BLURAY_MUTE;
uint16_t BLURAY_VOLUME_UP;
uint16_t BLURAY_VOLUME_DOWN;
uint16_t BLURAY_DISPLAY;

bool BLURAY_IS_ON = false;

void register_device_sonybluray()
{
    register_command(&BLURAY_EJECT,       makeCommandData(IR,{std::to_string(IR_PROTOCOL_SONY),"0x68B47"}));
    register_command(&BLURAY_SOURCE,      makeCommandData(IR,{std::to_string(IR_PROTOCOL_SONY),"0xA50"}));
    register_command(&BLURAY_TV_POWER,    makeCommandData(IR,{std::to_string(IR_PROTOCOL_SONY),"0xA90"}));
    register_command(&BLURAY_POWER,       makeCommandData(IR,{std::to_string(IR_PROTOCOL_SONY),"0xA8B47"}));
    register_command(&BLURAY_RED,         makeCommandData(IR,{std::to_string(IR_PROTOCOL_SONY),"0xE6B47"}));
    register_command(&BLURAY_GREEN,       makeCommandData(IR,{std::to_string(IR_PROTOCOL_SONY),"0x16B47"}));
    register_command(&BLURAY_YELLOW,      makeCommandData(IR,{std::to_string(IR_PROTOCOL_SONY),"0x96B47"}));
    register_command(&BLURAY_BLUE,        makeCommandData(IR,{std::to_string(IR_PROTOCOL_SONY),"0x66B47"}));
    register_command(&BLURAY_TOP_MENU,    makeCommandData(IR,{std::to_string(IR_PROTOCOL_SONY),"0x34B47"}));
    register_command(&BLURAY_POP_UP,      makeCommandData(IR,{std::to_string(IR_PROTOCOL_SONY),"0x94B47"}));
    register_command(&BLURAY_UP,          makeCommandData(IR,{std::to_string(IR_PROTOCOL_SONY),"0x9CB47"}));
    register_command(&BLURAY_LEFT,        makeCommandData(IR,{std::to_string(IR_PROTOCOL_SONY),"0xDCB47"}));
    register_command(&BLURAY_CENTER,      makeCommandData(IR,{std::to_string(IR_PROTOCOL_SONY),"0xBCB47"}));
    register_command(&BLURAY_RIGHT,       makeCommandData(IR,{std::to_string(IR_PROTOCOL_SONY),"0x3CB47"}));
    register_command(&BLURAY_DOWN,        makeCommandData(IR,{std::to_string(IR_PROTOCOL_SONY),"0x5CB47"}));
    register_command(&BLURAY_RETURN,      makeCommandData(IR,{std::to_string(IR_PROTOCOL_SONY),"0xC2B47"}));
    register_command(&BLURAY_OPTIONS,     makeCommandData(IR,{std::to_string(IR_PROTOCOL_SONY),"0xFCB47"}));
    register_command(&BLURAY_HOME,        makeCommandData(IR,{std::to_string(IR_PROTOCOL_SONY),"0x42B47"}));
    register_command(&BLURAY_LIKE,        makeCommandData(IR,{std::to_string(IR_PROTOCOL_SONY),"0x7AB47"}));
    register_command(&BLURAY_NETFLIX,     makeCommandData(IR,{std::to_string(IR_PROTOCOL_SONY),"0xD2B47"}));
    register_command(&BLURAY_REWIND,      makeCommandData(IR,{std::to_string(IR_PROTOCOL_SONY),"0xD8B47"}));
    register_command(&BLURAY_PLAY,        makeCommandData(IR,{std::to_string(IR_PROTOCOL_SONY),"0x58B47"}));
    register_command(&BLURAY_FORWARD,     makeCommandData(IR,{std::to_string(IR_PROTOCOL_SONY),"0x38B47"}));
    register_command(&BLURAY_PREVIOUS,    makeCommandData(IR,{std::to_string(IR_PROTOCOL_SONY),"0xEAB47"}));
    register_command(&BLURAY_PAUSE,       makeCommandData(IR,{std::to_string(IR_PROTOCOL_SONY),"0x98B47"}));
    register_command(&BLURAY_STOP,        makeCommandData(IR,{std::to_string(IR_PROTOCOL_SONY),"0x18B47"}));
    register_command(&BLURAY_NEXT,        makeCommandData(IR,{std::to_string(IR_PROTOCOL_SONY),"0x6AB47"}));
    register_command(&BLURAY_SUBTITLE,    makeCommandData(IR,{std::to_string(IR_PROTOCOL_SONY),"0xC6B47"}));
    register_command(&BLURAY_AUDIO,       makeCommandData(IR,{std::to_string(IR_PROTOCOL_SONY),"0x26B47"}));
    register_command(&BLURAY_MUTE,        makeCommandData(IR,{std::to_string(IR_PROTOCOL_SONY),"0x290"}));
    register_command(&BLURAY_VOLUME_UP,   makeCommandData(IR,{std::to_string(IR_PROTOCOL_SONY),"0x490"}));
    register_command(&BLURAY_VOLUME_DOWN, makeCommandData(IR,{std::to_string(IR_PROTOCOL_SONY),"0xC90"}));
    register_command(&BLURAY_DISPLAY,     makeCommandData(IR,{std::to_string(IR_PROTOCOL_SONY),"0x82B47"}));
}

void turn_bluray_off()
{
    if (BLURAY_IS_ON)
    {
        executeCommand(BLURAY_POWER);
        BLURAY_IS_ON = false;
    }
}

void turn_bluray_on()
{
    if (!BLURAY_IS_ON){
        executeCommand(BLURAY_POWER);
        BLURAY_IS_ON = true;
    }
}

void exec_sony_bluray_command(uint16_t command)
{
    if (command != BLURAY_POWER && BLURAY_IS_ON)
    {
        executeCommand(command);
    }
}
