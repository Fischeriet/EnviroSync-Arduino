#include <Arduino.h>

#include "Settings.h"
#include "NetworkManager.h"
#include "WebServer.h"

Settings settings;
NetworkManager networkManager;
WebServer webServer;


void setup() {
    Serial.begin(9600);
    while (!Serial) {
        ;
    }

    /*if (networkManager.connectToWifi("OnePlus Nord CE 3 Lite 5G", "j4jy6nui")) {
        Serial.println("Connected to wifi! IP: " + networkManager.getLocalIP());
    } else {
        Serial.println("Failed to connect to Wifi!");
    }*/

    if (networkManager.createAccessPoint("ArduinoAP", "password123")) {
        Serial.println("Access point created! IP: " + networkManager.getLocalIP());
        webServer.begin();

        Serial.println("Besøg http://" + networkManager.getLocalIP() + " for at konfigurere WiFi");

    } else {
        Serial.println("Failed to create access point!");
    }
}

void loop() {
    webServer.handleClient();
}