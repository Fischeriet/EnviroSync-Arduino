#pragma once

#include <Arduino.h>
#include <EEPROM.h>

class Settings {
private:
    static const int MAX_SSID_LENGTH = 32;
    static const int MAX_PASSWORD_LENGTH = 64;
    static const int EEPROM_SIZE = 512;

    struct Config {
        char ssid[MAX_SSID_LENGTH];
        char password[MAX_PASSWORD_LENGTH];
        bool isConfigured;
    };

    Config config;

public:
    Settings();
    void saveWifiCredentials(const String& ssid, const String& password);
    bool loadSettings();
    String getSSID();
    String getPassword();
    void clearSettings();
};