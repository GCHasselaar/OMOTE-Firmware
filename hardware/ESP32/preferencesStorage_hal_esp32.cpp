#include <Preferences.h>
#include "sleep_hal_esp32.h"
#include "tft_hal_esp32.h"
#include "keypad_keys_hal_esp32.h"
#include "applicationInternal/omote_log.h"
#include <map>

Preferences preferences;

std::string activeScene;
std::string activeGUIname;
int activeGUIlist;
int lastActiveGUIlistIndex;
std::map<std::string, bool> userDevicesStatus;

//Simple serialization of string/bool maps. key/value separator is ":", pair separator is ","
//So don't use either in your key names!
static std::string serializeMap(std::map<std::string, bool> map)
{
  std::string serialized = "";
  for (auto it = map.begin(); it != map.cend(); it++)
  {
    serialized += (it->first) + ":" + std::to_string(it->second) + ",";
  }
  serialized = serialized.substr(0, serialized.size() - 1);

  return serialized;
}

//Simple deserialization to a string/bool map
static std::map<std::string, bool> deserializeMap(std::string serialized)
{
  std::map<std::string, bool> deserialized;
  std::string::size_type kpos = 0, kend, vpos, vend;

  while ((kend = serialized.find(':', kpos)) != std::string::npos)
  {
    if ((vpos = serialized.find_first_not_of(':', kend)) == std::string::npos)
    {
      break;
    }
    if ((vend = serialized.find(',', vpos)) == std::string::npos)
    {
      vend = serialized.size();
    }

    deserialized.emplace(
        serialized.substr(kpos, kend - kpos),
        serialized.substr(vpos, vend - vpos) != "0");
    kpos = vend + 1;
    if (vend == serialized.size())
    {
      break;
    }
  }

  return deserialized;
}

void init_preferences_HAL(void)
{
  // Restore settings from internal flash memory
  preferences.begin("settings", false);
  if (preferences.getBool("alreadySetUp"))
  {
    // from sleep.h
    set_wakeupByIMUEnabled_HAL(preferences.getBool("wkpByIMU"));
    set_sleepTimeout_HAL(preferences.getUInt("slpTimeout", DEFAULT_SLEEP_TIMEOUT));
    set_motionThreshold_HAL(preferences.getUInt("motionThreshold", DEFAULT_MOTION_THRESHOLD));
    // from tft.h
    set_backlightBrightness_HAL(preferences.getUInt("blBrightness", 255));
// from keyboard.h
#if (OMOTE_HARDWARE_REV >= 5)
    set_keyboardBrightness_HAL(preferences.getUInt("kbBrightness", 255));
#endif
    // from here
    activeScene = std::string(preferences.getString("currentScene").c_str());
    activeGUIname = std::string(preferences.getString("currentGUIname").c_str());
    activeGUIlist = (preferences.getInt("currentGUIlist"));
    lastActiveGUIlistIndex = (preferences.getInt("lastActiveIndex"));

    userDevicesStatus = deserializeMap(preferences.getString("userDevicesStatus").c_str());

    // Serial.printf("Preferences restored: blBrightness %d, kbBrightness %d, GUI %s, scene %s\r\n", get_backlightBrightness_HAL(), get_keyboardBrightness_HAL(), activeGUIname.c_str(), activeScene.c_str());
  }
  else
  {
    // Serial.printf("No preferences to restore\r\n");
  }
  preferences.end();
}

void save_preferences_HAL(void)
{
  preferences.begin("settings", false);
  // from sleep.h
  preferences.putBool("wkpByIMU", get_wakeupByIMUEnabled_HAL());
  // from tft.h
  preferences.putUInt("slpTimeout", get_sleepTimeout_HAL());
  preferences.putUInt("motionThreshold", get_motionThreshold_HAL());
  preferences.putUInt("blBrightness", get_backlightBrightness_HAL());
// from keyboard.h
#if (OMOTE_HARDWARE_REV >= 5)
  preferences.putUInt("kbBrightness", get_keyboardBrightness_HAL());
// Serial.printf("Preferences saved: blBrightness %d, kbBrightness %d, GUI %s, scene %s\r\n", get_backlightBrightness_HAL(), get_keyboardBrightness_HAL(), activeGUIname.c_str(), activeScene.c_str());
#endif
  // from here
  preferences.putString("currentScene", activeScene.c_str());
  preferences.putString("currentGUIname", activeGUIname.c_str());
  preferences.putInt("currentGUIlist", activeGUIlist);
  preferences.putInt("lastActiveIndex", lastActiveGUIlistIndex);
  if (!preferences.getBool("alreadySetUp"))
  {
    preferences.putBool("alreadySetUp", true);
  }

  preferences.putString("userDevicesStatus", serializeMap(userDevicesStatus).c_str());
  preferences.end();
}

std::string get_activeScene_HAL()
{
  return activeScene;
}
void set_activeScene_HAL(std::string anActiveScene)
{
  activeScene = anActiveScene;
}
std::string get_activeGUIname_HAL()
{
  return activeGUIname;
}
void set_activeGUIname_HAL(std::string anActiveGUIname)
{
  activeGUIname = anActiveGUIname;
}
int get_activeGUIlist_HAL()
{
  return activeGUIlist;
}
void set_activeGUIlist_HAL(int anActiveGUIlist)
{
  activeGUIlist = anActiveGUIlist;
}
int get_lastActiveGUIlistIndex_HAL()
{
  return lastActiveGUIlistIndex;
}
void set_lastActiveGUIlistIndex_HAL(int aGUIlistIndex)
{
  lastActiveGUIlistIndex = aGUIlistIndex;
}
bool get_userDeviceStatus_HAL(std::string deviceName)
{
  return userDevicesStatus[deviceName];
}
void set_userDeviceStatus_HAL(std::string deviceName, bool newStatus)
{
  userDevicesStatus[deviceName] = newStatus;
}
