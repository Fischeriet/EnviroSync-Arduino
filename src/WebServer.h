#ifndef WEBSERVER_H
#define WEBSERVER_H

#include <WiFiS3.h>
#include "HTMLPages.h"
#include "NetworkManager.h"



class WebServer {
private:
    WiFiServer _server;
    WiFiClient _client;
    static const int PORT = 80;

    void sendResponse(const char* content);

public:
    WebServer();
    void begin();
    void handleClient();

};

#endif //WEBSERVER_H
