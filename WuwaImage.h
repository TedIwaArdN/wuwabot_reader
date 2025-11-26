// WuwaImage.h
//
// handles image recognition with stb_image, stb_image_write
//
// link to Git Repository of stb: https://github.com/nothings/stb
// 
// version 1.0
// by Dropkick
// Nov 25, 2025
//
#pragma once
#include <string>
#include <iostream>

class WuwaImage
{
private:
	unsigned char* img;
	int width;
	int height;
	int channels;

public:
	WuwaImage(const std::string& filepath);
	~WuwaImage();

	// confirm the image is legal
	bool IsWuwaImage();
	// get pixel at (x,y)
	int GetPixelIndex(int x, int y);
	// for debugging: show resolution and some pixels
	void PrintInfo();

	// confirm the slot is not empty
	bool IsEmptySlot(int slot);

	// compare the echo at slot with the known echo at file path
	bool CompareWithEcho(const std::string& filepath, int slot);
	// create a new echo picture
	void GenerateNewEcho(const std::string& savepath, int slot);

	// compare the echo set at slot with the known echo set at file path
	bool CompareWithEchoSet(const std::string& filepath, int slot);
	// create a new echo set picture
	void GenerateNewEchoSet(const std::string& savepath, int slot);
};

// abs of difference
int DiffVal(int a, int b);
