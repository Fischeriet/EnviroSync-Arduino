#include "NetworkManager.h"

NetworkManager::NetworkManager(unsigned long connectionTimeout, unsigned long dhcpTimeout) {
    _isAccessPoint = false;
    _status = WL_IDLE_STATUS;
    _connectionTimeout = connectionTimeout;
    _dhcpTimeout = dhcpTimeout;
}

bool NetworkManager::connectToWifi(const char *ssid, const char *password) {
    if (_isAccessPoint) {
        WiFi.end();
        _isAccessPoint = false;
    }

    _status = WiFi.begin(ssid, password);

    unsigned long startTime = millis();
    while (_status != WL_CONNECTED && (millis() - startTime) < _connectionTimeout) {
        delay(500);
        Serial.print(".");
        _status = WiFi.status();
    }

    if (_status != WL_CONNECTED) {
        return false;
    }

    if (!waitForDHCP()) {
        return false;
    }

    return true;
}

bool NetworkManager::waitForDHCP() {
    unsigned long startTime = millis();
    IPAddress ip;

    while ((millis() - startTime) < _dhcpTimeout) {
        ip = WiFi.localIP();
        if (ip[0] != 0) {
            return true;
        }
        delay(500);
        Serial.print(">");
    }
    return false;
}

void NetworkManager::printWiFiStatus() {
    Serial.println("-----------------------------");
    Serial.print("SSID: ");
    Serial.println(WiFi.SSID());

    IPAddress ip = WiFi.localIP();
    Serial.print("IP Adresse: ");
    Serial.println(ip);

    Serial.print("Signal styrke (RSSI): ");
    Serial.print(WiFi.RSSI());
    Serial.println(" dBm");
    Serial.println("-----------------------------");
}

bool NetworkManager::disconnect() {
    WiFi.end();
    _status = WL_IDLE_STATUS;
    return true;
}

bool NetworkManager::createAccessPoint(const char *ssid, const char *password) {
    if (!_isAccessPoint) {
        WiFi.end();
    }

    _status = WiFi.beginAP(ssid, password);
    _isAccessPoint = true;

    return _status == WL_AP_LISTENING;
}

bool NetworkManager::isConnected() {
    if (_isAccessPoint) {
        return _status == WL_AP_LISTENING;
    }

    return WiFi.status() == WL_CONNECTED;
}

String NetworkManager::getLocalIP() {
    IPAddress ip = WiFi.localIP();
    if (ip[0] == 0) {
        return "Ingen IP";
    }
    return String(ip[0]) + "." + String(ip[1]) + "." + String(ip[2]) + "." + String(ip[3]);

}

int NetworkManager::getSignalStrength() {
    if (!_isAccessPoint && isConnected()) {
        return WiFi.RSSI();
    }

    return 0;
}
