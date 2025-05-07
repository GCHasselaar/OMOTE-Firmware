#pragma once

#include <stdint.h>

// Contains definitions for the Omote remote model L-27-5KEY

extern uint16_t OPTOMA_ON;
extern uint16_t OPTOMA_OFF;
extern uint16_t OPTOMA_USER1;
extern uint16_t OPTOMA_USER2;
extern uint16_t OPTOMA_USER3;
extern uint16_t OPTOMA_BRIGHTNESS;
extern uint16_t OPTOMA_CONTRAST;
extern uint16_t OPTOMA_MODE;
extern uint16_t OPTOMA_KEYSTONE;
extern uint16_t OPTOMA_ASPECTRATIO;
extern uint16_t OPTOMA_3D;
extern uint16_t OPTOMA_MUTE;
extern uint16_t OPTOMA_DB;
extern uint16_t OPTOMA_SLEEPTIMER;
extern uint16_t OPTOMA_UP;
extern uint16_t OPTOMA_LEFT;
extern uint16_t OPTOMA_ENTER;
extern uint16_t OPTOMA_RIGHT;
extern uint16_t OPTOMA_DOWN;
extern uint16_t OPTOMA_MENU;
extern uint16_t OPTOMA_HDMI1;
extern uint16_t OPTOMA_HDMI2;
extern uint16_t OPTOMA_VGA1;
extern uint16_t OPTOMA_VGA2;
extern uint16_t OPTOMA_VIDEO;
extern uint16_t OPTOMA_COMPONENT;

void register_device_optoma();