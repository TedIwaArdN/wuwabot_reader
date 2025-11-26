// FileHandler.h
//
// read list of images in certain directories
// use curl to download image from link
// need to run
//     sudo apt install libcurl4-openssl-dev
// to use the lib
//
// website of curl: https://curl.se/
//
// version 1.0
// implemented by Dropkick
// Nov 25, 2025
//
#pragma once
#define CURL_STATICLIB
#include <vector>
#include <string>
#include <filesystem>
#include <iostream>

#include "curl/curl.h"

size_t callbackfunction(void* ptr, size_t size, size_t nmemb, void* userdata)
{
    FILE* stream = (FILE*)userdata;
    if (!stream)
    {
        std::cerr << "!!! No stream" << std::endl;
        return 0;
    }

    size_t written = fwrite((FILE*)ptr, size, nmemb, stream);
    return written;
}

std::vector<std::string> GetListOfFilesInFolder(const std::string& folderPath) {
    std::vector<std::string> fileNames;
    try {
        for (const auto& entry : std::filesystem::directory_iterator(folderPath)) {
            if (std::filesystem::is_regular_file(entry.status())) {
                fileNames.push_back(entry.path().filename().string());
            }
        }
    }
    catch (const std::filesystem::filesystem_error& e) {
        std::cerr << "Filesystem error: " << e.what() << std::endl;
    }
    return fileNames;
}

void ReadPicFromURL(std::string URL) {
    CURL* curl;
    CURLcode res;
    FILE* fp;
    curl = curl_easy_init();
    if (curl) {
        fp = fopen("SourceImage/player_card.jpeg", "wb");
        curl_easy_setopt(curl, CURLOPT_URL, URL.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callbackfunction);
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1);
        res = curl_easy_perform(curl);
        if (CURLE_OK != res) {
            std::cerr << "CURL error: " << res << std::endl;
        }
        curl_easy_cleanup(curl);
        fclose(fp);
    }
    curl_global_cleanup();
}

