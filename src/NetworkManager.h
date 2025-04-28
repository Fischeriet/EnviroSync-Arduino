#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H

#include <WiFiS3.h>

class NetworkManager {
private:
    char* _ssid;
    char* _password;
    bool _isAccessPoint;
    int _status;
    unsigned long _connectionTimeout;
    unsigned long _dhcpTimeout;
    static const int AP_CHANNEL = 1;

public:
    NetworkManager(unsigned long connectionTimeout = 10000, unsigned long dhcpTimeout = 8000);

    bool connectToWifi(const char* ssid, const char* password);
    bool disconnect();

    bool createAccessPoint(const char* ssid, const char* password);
    bool stopAccessPoint();

    bool isConnected();
    String getLocalIP();
    int getSignalStrength();
    void printWiFiStatus();

private:
    bool waitForDHCP();
};

#endif //NETWORKMANAGER_H