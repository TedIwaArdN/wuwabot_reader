// CharacterInfo.cpp: implementation of CharacterInfo.h
//
// stores classes that are used to save all character details
// currently can only read echo and their set
// 
// version 1.0
// by Dropkick
// Nov 26, 2025
//
#pragma execution_character_set("utf-8")
#include "CharacterInfo.h"
#include <iostream>

// print echo info in json format
void Echo::PrintInfo(std::ofstream& ostr) {
	if (ID == "EMPTY" || set == "EMPTY") {
		ostr << "\t{}," << std::endl;
	}
	ostr << "\t{" << std::endl;
	ostr << "\t\t\"id\": \"" << ID << "\"," << std::endl;
	ostr << "\t\t\"set\": \"" << echoset_en_to_cn.at(set) << "\"," << std::endl;
	ostr << "\t}," << std::endl;
}

// upload an echo to character
void CharacterInfo::UploadEcho(std::string ID, std::string set) {
	echo_list.push_back(Echo(ID, set));
}

// print all stored echoes as json
void CharacterInfo::PrintInfo(std::ofstream& ostr) {
	ostr << "[" << std::endl;
	for (Echo echo : echo_list) {
		echo.PrintInfo(ostr);
	}
	ostr << "]" << std::endl;
}

Echo::Echo(std::string id, std::string s) {
	ID = id;
	set = s;
}
