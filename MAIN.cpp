// MAIN.cpp : This file contains the 'main' function. Program execution begins and ends there.
// 
// wuwabot_reader, reads Character Profile Image URL generated from wuwa-bot in Discord Channel, 
// your character information will be stored in result.json (will be disappear after each upload)
//
//*************************************************************************************************
//*************************************************************************************************
//
// To use this: 
//   1. Download curl by running:
//          sudo apt install libcurl4-openssl-dev
//   2. Compile the program in main folder by:
//          g++ *.cpp -o NAMEYOUR.EXECUTABLE -lcurl
//   3. Run program with or without your Image URL
//          ./NAMEYOUR.EXECUTABLE YOUR.URL/of_image
//      or if you want error log printed in error.log,
//          ./NAMEYOUR.EXECUTABLE YOUR.URL/of_image 2> error.log
//   4. To run the program again, just Repeat Step 3
//
//------------------------------------------------------------------------
//
// Check your Result: 
//   find result.json generated in the same directory as MAIN.cpp
//
//*************************************************************************************************
//*************************************************************************************************
//
// DISCLAIMER:
// 
// This project implements stb and curl for several core features, their source code are open via
//   https://github.com/nothings/stb
//   https://curl.se/
//
// This project is created in a fan-based purpose to improve the gaming experience of Wuthering 
// Waves. It is not eligible to use in finincial purpose
// DO NOT USE THIS PROJECT FOR YOUR OWN FINANCIAL INTEREST
//
// This project will download images from the Internet, and will read & write some files stored 
// locally. The creator of the project limits those file access only to the sub-folders in 
// ./SourceImage. But still, the risk of getting unidentified downloads still exists. Please use
// this project at your own risk. 
// 
//*************************************************************************************************
//
// version 1.0
// By Dropkick
// Nov 26, 2025
//
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#include <string>
#include <stdio.h>
#include <fstream>

#include "WuwaImage.h"
#include "FileHandler.h"
#include "CharacterInfo.h"


int main(int argc, char** argv)
{
    // paths for image source folder
    std::string folderpath_echo("SourceImage/echo_pics");
    std::string folderpath_echoset("SourceImage/echoset_pics");
    std::string newpicspath("SourceImage");

    // grab names of all recorded echo & echo set
    std::vector<std::string> echoList = GetListOfFilesInFolder(folderpath_echo);
    std::vector<std::string> echosetList = GetListOfFilesInFolder(folderpath_echoset);

    // ostream for result printing
    std::string savefilepath("result.json");
    std::ofstream ostr(savefilepath);

    // uncomment this path to read from url
    std::string playerCardPath("SourceImage/player_card.jpeg");

    // uncommment this path to read from a local file
    //std::string playerCardPath("SourceImage/50cf78c199eb517a20d8f3f51d4422ae.png");

    // read image from the url
    std::string url;
    if (playerCardPath == "SourceImage/player_card.jpeg") {
        if (argc > 1) {
            url = argv[1];
        }
        else {
            std::cout << "Input Image URL: ";
            std::cin >> url;
        }
        
        // download character card from url
        ReadPicFromURL(url);
    }
    
    // read character card
    WuwaImage playerCard(playerCardPath);

    // make sure the character card is legal
    if (playerCard.IsWuwaImage() == false) {
        std::cerr << "Image is not legal!" << std::endl;
        return 0;
    }

    // the class for character card information
    CharacterInfo playerInfo;

    for (int slot = 1; slot <= 5; slot++) {
        // detect empty echo slot
        if (playerCard.IsEmptySlot(slot)) {
            playerInfo.UploadEcho("EMPTY", "EMPTY");
            std::cout << "No echo at slot " << slot << std::endl;
            continue;
        }
        std::string echo_id = "UNKNOWN";
        std::string echo_set = "UNKNOWN";

        // match echo in current slot with every single known echo
        bool know_this_echo = false;
        for (auto iter : echoList) {
            if (playerCard.CompareWithEcho(folderpath_echo + "/" + iter, slot)) {
                echo_id = iter.substr(8, iter.length() - 5 - 8);
                //std::cout << "Slot " << slot << " is " << iter.substr(8, iter.length() - 5 - 8);
                know_this_echo = true;
                break;
            }
        }
        // haven't recorded this echo before, create the profile of the new one
        if (!know_this_echo) {
            playerCard.GenerateNewEcho("SourceImage", slot);
        }

        // match echo set in current slot with every single known echo set
        bool know_this_echoset = false;
        for (auto iter : echosetList) {
            if (playerCard.CompareWithEchoSet(folderpath_echoset + "/" + iter, slot)) {
                echo_set = iter.substr(0, iter.length() - 5);
                //std::cout << ", " << iter.substr(0, iter.length() - 5) << std::endl;
                know_this_echoset = true;
                break;
            }
        }
        // haven't recorded this echo set before, create the profile of the new one
        if (!know_this_echoset) {
            playerCard.GenerateNewEchoSet("SourceImage", slot);
        }

        // Upload Echo information to CharacterInfo class
        playerInfo.UploadEcho(echo_id, echo_set);
    }

    // Save CharacterInfo as json
    playerInfo.PrintInfo(ostr);

    // mark of complete progress
    std::cout << "Echo information upload complete" << std::endl;
    return 0;
}
