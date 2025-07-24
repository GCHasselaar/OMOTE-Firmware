// OMOTE firmware for ESP32
// 2023-2025 Maximilian Kern, Klaus Musch

#include "applicationInternal/omote_log.h"
// init hardware and hardware loop
#include "applicationInternal/hardware/hardwarePresenter.h"
// register devices and their commands
//   special
#include "devices/misc/device_specialCommands.h"
#include "applicationInternal/commandHandler.h"
//   keyboards
#if (ENABLE_KEYBOARD_MQTT == 1)
#include "devices/keyboard/device_keyboard_mqtt/device_keyboard_mqtt.h"
#endif // ENABLE_KEYBOARD_MQTT
#if (ENABLE_KEYBOARD_BLE == 1)
#include "devices/keyboard/device_keyboard_ble/device_keyboard_ble.h"
#endif // ENABLE_KEYBOARD_BLE
//   TV
#include "devices/TV/device_optoma/device_optoma.h"
//   AV receiver
#include "devices/AVreceiver/device_onkyo/device_onkyo.h"
//   media player
#include "devices/mediaPlayer/device_sonybluray/device_sonybluray.h"
//   misc
// register gui and keys
#include "applicationInternal/gui/guiBase.h"
#include "applicationInternal/gui/guiRegistry.h"
#include "guis/gui_sceneSelection.h"
#include "guis/gui_irReceiver.h"
#include "guis/gui_settings.h"
#include "guis/gui_BLEpairing.h"
#include "applicationInternal/keys.h"
#include "applicationInternal/gui/guiStatusUpdate.h"
#include "applicationInternal/scenes/sceneHandler.h"
// register scenes
#include "scenes/scene__default.h"
#include "scenes/scene_allOff.h"
#include "scenes/scene_bluray.h"
#include "scenes/scene_chromecast.h"
#include "scenes/scene_gamecube.h"
#include "scenes/scene_onkyo_settings.h"
#include "scenes/scene_optoma_settings.h"
#include "scenes/scene_pc.h"
#include "scenes/scene_ps3.h"
#include "scenes/scene_switch.h"
#include "scenes/scene_switch2.h"
#include "scenes/scene_wii.h"

#if defined(ARDUINO)
// in case of Arduino we have a setup() and a loop()
void setup() {

#elif defined(WIN32) || defined(__linux__) || defined(__APPLE__)
// in case of Windows/Linux, we have only a main() function, no setup() and loop(), so we have to simulate them
// forward declaration of loop()
void loop(unsigned long *pIMUTaskTimer, unsigned long *pUpdateStatusTimer);
// main function as usual in C
int main(int argc, char *argv[]) {
#endif

  // --- Startup ---
  Serial.begin(115200);
  // do some general hardware setup, like powering the TFT, I2C, ...
  init_hardware_general();
  // get wakeup reason
  init_sleep();
  // Restore settings from internal flash memory
  init_preferences();
  // blinking led
  init_userled();
  // startup SD card
  #if(OMOTE_HARDWARE_REV >= 5)
  // SD card is currently not used, so save some time on startup and don't init the SD card
  // init_SD_card();
  #endif

  // setup IR sender
  init_infraredSender();

  // register commands for the devices
  register_specialCommands();
  //   TV
  register_device_optoma();
  //   AV receiver
  register_device_onkyo();
  //   media player
  register_device_sonybluray();
  
  #if (ENABLE_KEYBOARD_MQTT == 1)
  register_device_keyboard_mqtt();
  #endif
  #if (ENABLE_KEYBOARD_BLE == 1)
  register_device_keyboard_ble();
  #endif
  register_keyboardCommands();

  // Register the GUIs. They will be displayed in the order they have been registered.
  register_gui_sceneSelection();
  register_gui_irReceiver();
  register_gui_settings();
  
  #if (ENABLE_KEYBOARD_BLE == 1)
  register_gui_blepairing();
  #endif
  // Only show these GUIs in the main gui list. If you don't set this explicitely, by default all registered guis are shown.
  #if (USE_SCENE_SPECIFIC_GUI_LIST != 0)
  main_gui_list =
    {tabName_sceneSelection, tabName_settings, tabName_irReceiver
    #if (ENABLE_KEYBOARD_BLE == 1)
    , tabName_blepairing
    #endif
    };
  #endif

  // register the scenes and their key_commands_*
  register_scene_defaultKeys();

  register_scene_bluray();
  register_scene_chromecast();
  register_scene_gamecube();
  register_scene_onkyo_settings();
  register_scene_optoma_settings();
  register_scene_pc();
  register_scene_ps3();
  register_scene_switch();
  register_scene_switch2();
  register_scene_wii();

  register_scene_allOff();
  // Only show these scenes on the sceneSelection gui. If you don't set this explicitely, by default all registered scenes are shown.
  set_scenes_on_sceneSelectionGUI({
    scene_name_pc, scene_name_chromecast,
    scene_name_switch, scene_name_switch2,
    scene_name_bluray, scene_name_ps3, 
    scene_name_gamecube, scene_name_wii,
    scene_name_onkyo_settings, scene_name_optoma_settings
  });

  // init GUI - will initialize tft, touch and lvgl
  init_gui(); // This has to come before any other i2c devices are initialized, otherwise the i2c bus will not be powered
  setLabelActiveScene();
  gui_loop(); // Run the LVGL UI once before the loop takes over
  
  // Power Pin and battery monitor definition
  init_battery();

  // init BLE keyboard. Has to be after init_gui (because of powered I2C) and after init_battery (because of fuel gauge init)
  #if (ENABLE_KEYBOARD_BLE == 1)
  init_keyboardBLE();
  #endif

  // setup keyboard matrix driver
  init_keys();

  // setup the Inertial Measurement Unit (IMU) for motion detection. Has to be after init_gui(), otherwise I2C will not work
  init_IMU();

  // init WiFi - needs to be after init_gui() because WifiLabel must be available
  #if (ENABLE_WIFI_AND_MQTT == 1)
  init_mqtt();
  #endif

  omote_log_i("Setup finished in %lu ms.\r\n", millis());

  #if defined(WIN32) || defined(__linux__) || defined(__APPLE__)
  // In Windows/Linux there is no loop function that is automatically being called. So we have to do this on our own infinitely here in main()
  unsigned long IMUTaskTimer = 0;
  unsigned long updateStatusTimer = 0;
  while (1)
    loop(&IMUTaskTimer, &updateStatusTimer);
  #endif

}

// Loop ------------------------------------------------------------------------------------------------------------------------------------
#if defined(ARDUINO)
unsigned long IMUTaskTimer = 0;
unsigned long updateStatusTimer = 0;
unsigned long *pIMUTaskTimer = &IMUTaskTimer;
unsigned long *pUpdateStatusTimer = &updateStatusTimer;
void loop() {
#elif defined(WIN32) || defined(__linux__) || defined(__APPLE__)
void loop(unsigned long *pIMUTaskTimer, unsigned long *pUpdateStatusTimer) {
#endif

  // --- do as often as possible --------------------------------------------------------
  // update backlight and keyboard brightness. Fade in on startup, dim before going to sleep
  update_backlightBrightness();
  #if(OMOTE_HARDWARE_REV >= 5)
    update_keyboardBrightness();
  #endif
  // keypad handling: get key states from hardware and process them
  keypad_loop();
  // process IR receiver, if activated
  if (get_irReceiverEnabled()) {
    infraredReceiver_loop();
  }
  // update LVGL UI
  gui_loop();
  // call mqtt loop to receive mqtt messages, if you are subscribed to some topics
  #if (ENABLE_WIFI_AND_MQTT == 1)
  mqtt_loop();
  #endif

  // --- every 100 ms -------------------------------------------------------------------
  // Refresh IMU data (motion detection) every 100 ms
  // If no action (key, TFT or motion), then go to sleep
  if(millis() - *pIMUTaskTimer >= 100){
    *pIMUTaskTimer = millis();

    check_activity();

    update_button_borders();
  }

  // --- every 1000 ms ------------------------------------------------------------------
  if(millis() - *pUpdateStatusTimer >= 1000) {
    *pUpdateStatusTimer = millis();

    // update user_led, battery, BLE, memoryUsage on GUI
    updateHardwareStatusAndShowOnGUI();
  }

}
