#pragma once

#include <string>
//#include <curl/curl.h>

class WhatsAppMessenger {
public:
    WhatsAppMessenger();
    ~WhatsAppMessenger();
    std::string sendMessage(const std::string& numero, const std::string& texto);    

private:
    static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp);
    std::string performCurlRequest(const std::string& url, const std::string& jsonData);
};