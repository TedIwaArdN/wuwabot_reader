// CharacterInfo.h
//
// stores classes that are used to save all character details
// currently can only read echo and their set
// 
// version 1.0
// by Dropkick
// Nov 26, 2025
//
#pragma once
#include <string>
#include <vector>
#include <map>
#include <fstream>

struct Echo {
	std::string ID;
	std::string set;

	Echo(std::string id, std::string s);

	// print echo info in json format
	void PrintInfo(std::ofstream& ostr);
};

class CharacterInfo {
private:
	std::vector<Echo> echo_list;

public:
	// upload an echo to character
	void UploadEcho(std::string ID, std::string set);

	// print all stored echoes as json
	void PrintInfo(std::ofstream& ostr);
};

// map for echoset names
const static std::map<std::string, std::string> echoset_en_to_cn{
	{"UNKNOWN", "未收录声骸套装"},
	{"Freezing Frost", "凝夜白霜"},
	{"Molten Rift", "熔山裂谷"},
	{"Void Thunder", "彻空冥雷"},
	{"Sierra Gale", "啸谷长风"},
	{"Celestial Light", "浮星祛暗"},
	{"Havoc Eclipse", "沉日劫明"},
	{"Rejuvenating Glow", "隐世回光"},
	{"Moonlit Clouds", "轻云出月"},
	{"Lingering Tunes", "不绝余音"},
	{"Frosty Resolve", "凌冽决断之心"},
	{"Eternal Radiance", "此间永驻之光"},
	{"Midnight Veil", "幽夜隐匿之帷"},
	{"Empyrean Anthem", "高天共奏之曲"},
	{"Tidebreaking Courage", "无惧浪涛之勇"},
	{"Gusts of Welkin", "流云逝尽之空"},
	{"Windward Pilgrimage", "愿戴荣光之旅"},
	{"Flaming Clawprint", "奔狼燎原之焰"},
	{"Dream of the Lost", "失序彼岸之梦"},
	{"Crown of Valor", "荣斗铸锋之冠"},
	{"Law of Harmony", "息界同调之律"},
	{"Flamewing's Shadow", "焚羽猎魔之影"},
	{"Thread of Severed Fate", "命理崩毁之弦"}
};

