#include "applicationInternal/commandHandler.h"
#include "applicationInternal/hardware/hardwarePresenter.h"
#include "device_optoma.h"

uint16_t OPTOMA_ON;
uint16_t OPTOMA_OFF;
uint16_t OPTOMA_USER1;
uint16_t OPTOMA_USER2;
uint16_t OPTOMA_USER3;
uint16_t OPTOMA_BRIGHTNESS;
uint16_t OPTOMA_CONTRAST;
uint16_t OPTOMA_MODE;
uint16_t OPTOMA_KEYSTONE;
uint16_t OPTOMA_ASPECTRATIO;
uint16_t OPTOMA_3D;
uint16_t OPTOMA_MUTE;
uint16_t OPTOMA_DB;
uint16_t OPTOMA_SLEEPTIMER;

uint16_t OPTOMA_UP;
uint16_t OPTOMA_LEFT;
uint16_t OPTOMA_ENTER;
uint16_t OPTOMA_RIGHT;
uint16_t OPTOMA_DOWN;
uint16_t OPTOMA_MENU;

uint16_t OPTOMA_HDMI1;
uint16_t OPTOMA_HDMI2;
uint16_t OPTOMA_VGA1;
uint16_t OPTOMA_VGA2;
uint16_t OPTOMA_VIDEO;
uint16_t OPTOMA_COMPONENT;

void register_device_optoma(){
    register_command(&OPTOMA_ON,            makeCommandData(IR,{std::to_string(IR_PROTOCOL_NEC),"0x4CB340BF"}));
    register_command(&OPTOMA_OFF,           makeCommandData(IR,{std::to_string(IR_PROTOCOL_NEC),"0x4CB3748B"}));
    register_command(&OPTOMA_USER1,         makeCommandData(IR,{std::to_string(IR_PROTOCOL_NEC),"0x4CB36C93"}));
    register_command(&OPTOMA_USER2,         makeCommandData(IR,{std::to_string(IR_PROTOCOL_NEC),"0x4CB3A659"}));
    register_command(&OPTOMA_USER3,         makeCommandData(IR,{std::to_string(IR_PROTOCOL_NEC),"0x4CB36699"}));
    register_command(&OPTOMA_BRIGHTNESS,    makeCommandData(IR,{std::to_string(IR_PROTOCOL_NEC),"0x4CB3827D"}));
    register_command(&OPTOMA_CONTRAST,      makeCommandData(IR,{std::to_string(IR_PROTOCOL_NEC),"0x4CB342BD"}));
    register_command(&OPTOMA_MODE,          makeCommandData(IR,{std::to_string(IR_PROTOCOL_NEC),"0x4CB3A05F"}));
    register_command(&OPTOMA_KEYSTONE,      makeCommandData(IR,{std::to_string(IR_PROTOCOL_NEC),"0x4CB3E01F"}));
    register_command(&OPTOMA_ASPECTRATIO,   makeCommandData(IR,{std::to_string(IR_PROTOCOL_NEC),"0x4CB326D9"}));
    register_command(&OPTOMA_3D,            makeCommandData(IR,{std::to_string(IR_PROTOCOL_NEC),"0x4CB3916E"}));
    register_command(&OPTOMA_MUTE,          makeCommandData(IR,{std::to_string(IR_PROTOCOL_NEC),"0x4CB34AB5"}));
    register_command(&OPTOMA_DB,            makeCommandData(IR,{std::to_string(IR_PROTOCOL_NEC),"0x4CB322DD"}));
    register_command(&OPTOMA_SLEEPTIMER,    makeCommandData(IR,{std::to_string(IR_PROTOCOL_NEC),"0x4CB3C639"}));
    register_command(&OPTOMA_UP,            makeCommandData(IR,{std::to_string(IR_PROTOCOL_NEC),"0x4CB38877"}));
    register_command(&OPTOMA_LEFT,          makeCommandData(IR,{std::to_string(IR_PROTOCOL_NEC),"0x4CB308F7"}));
    register_command(&OPTOMA_ENTER,         makeCommandData(IR,{std::to_string(IR_PROTOCOL_NEC),"0x4CB3F00F"}));
    register_command(&OPTOMA_RIGHT,         makeCommandData(IR,{std::to_string(IR_PROTOCOL_NEC),"0x4CB348B7"}));
    register_command(&OPTOMA_DOWN,          makeCommandData(IR,{std::to_string(IR_PROTOCOL_NEC),"0x4CB328D7"}));
    register_command(&OPTOMA_MENU,          makeCommandData(IR,{std::to_string(IR_PROTOCOL_NEC),"0x4CB3708F"}));
    register_command(&OPTOMA_HDMI1,         makeCommandData(IR,{std::to_string(IR_PROTOCOL_NEC),"0x4CB36897"}));
    register_command(&OPTOMA_HDMI2,         makeCommandData(IR,{std::to_string(IR_PROTOCOL_NEC),"0x4CB30CF3"}));
    register_command(&OPTOMA_VGA1,          makeCommandData(IR,{std::to_string(IR_PROTOCOL_NEC),"0x4CB3D827"}));
    register_command(&OPTOMA_VGA2,          makeCommandData(IR,{std::to_string(IR_PROTOCOL_NEC),"0x4CB37887"}));
    register_command(&OPTOMA_VIDEO,         makeCommandData(IR,{std::to_string(IR_PROTOCOL_NEC),"0x4CB338C7"}));
    register_command(&OPTOMA_COMPONENT,     makeCommandData(IR,{std::to_string(IR_PROTOCOL_NEC),"0x4CB3E817"}));
}

void turn_optoma_off()
{
    executeCommand(OPTOMA_OFF);
    delay(250);
    executeCommand(OPTOMA_OFF);
}
