#include "WhatsAppMessenger.h"
#include <iostream>
//#include <curl/curl.h>

WhatsAppMessenger::WhatsAppMessenger() {
   // curl_global_init(CURL_GLOBAL_ALL);
}

WhatsAppMessenger::~WhatsAppMessenger() {
    //curl_global_cleanup();
}

size_t WhatsAppMessenger::WriteCallback(void *contents, size_t size, size_t nmemb, void *userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

std::string WhatsAppMessenger::performCurlRequest(const std::string& url, const std::string& jsonData) {
    /*CURL *curl;
    CURLcode res;
    std::string readBuffer;
    curl = curl_easy_init();
    if(curl) {
        struct curl_slist *headers = NULL;
        headers = curl_slist_append(headers, "Content-Type: application/json");
        headers = curl_slist_append(headers, "apikey: 770077");

        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, jsonData.c_str());
        
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

        res = curl_easy_perform(curl);

        if(res != CURLE_OK)
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;

        curl_easy_cleanup(curl);
        curl_slist_free_all(headers);
    }*/
    return "readBuffer";
}

std::string WhatsAppMessenger::sendMessage(const std::string& numero, const std::string& texto) {    
    std::string url = "https://wsp.qtm.bo/message/sendText/Gabo";
    std::string jsonData = "{\"number\": \"" + numero + 
                           "\", \"optns\": { \"delay\": 1200, \"presence\": \"composing\", \"linkPreview\": false }, \"textMessage\": { \"text\": \"" + texto + "\" } }";
    return performCurlRequest(url, jsonData);
}