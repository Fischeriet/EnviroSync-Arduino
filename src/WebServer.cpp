#include "WebServer.h"

WebServer::WebServer(NetworkManager& networkManager) : _server(PORT), _networkManager(networkManager) {

}

void WebServer::begin() {
    _server.begin();
    Serial.println("Server started on port " + String(PORT));
}

void WebServer::handleClient() {
    _client = _server.available();
    ///test
    if (_client) {
        String currentLine = "";
        String requestMethod = "";
        String path = "";
        bool requestLineComplete = false;

        while (_client.connected()) {
            if (_client.available()) {
                char c = _client.read();

                if (c == '\n') {
                    if (!requestLineComplete) {
                        int firstSpace = currentLine.indexOf(' ');
                        int secondSpace = currentLine.indexOf(' ', firstSpace + 1);
                        requestMethod = currentLine.substring(0, firstSpace);
                        path = currentLine.substring(firstSpace + 1, secondSpace);
                        requestLineComplete = true;
                    }

                    if (currentLine.length() == 0) {
                        if (path == "/loading") {
                            sendResponse(LOADING_PAGE);
                        } else if (path == "/") {
                            sendResponse(MAIN_PAGE);
                        }
                        _client.stop();
                        break;
                    }
                    currentLine = "";
                }
                else if (c != '\r') {
                    currentLine += c;
                }
            }
        }
        _client.stop();
    }
}

void WebServer::sendResponse(const char* content) {
    _client.print(content);
    _client.flush();
}