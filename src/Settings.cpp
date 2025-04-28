#include "Settings.h"

Settings::Settings() : config{} {
    memset(&config, 0, sizeof(Config));
    config.isConfigured = false;
}

void Settings::saveWifiCredentials(const String& ssid, const String& password) {
    memset(&config, 0, sizeof(Config));
    ssid.toCharArray(config.ssid, MAX_SSID_LENGTH);
    password.toCharArray(config.password, MAX_PASSWORD_LENGTH);
    config.isConfigured = true;

    EEPROM.put(0, config);
}

bool Settings::loadSettings() {
    EEPROM.get(0, config);
    return config.isConfigured;
}

String Settings::getSSID() {
    return String(config.ssid);
}

String Settings::getPassword() {
    return String(config.password);
}

void Settings::clearSettings() {
    memset(&config, 0, sizeof(Config));
    config.isConfigured = false;
    EEPROM.put(0, config);
}