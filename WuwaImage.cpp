// WuwaImage.cpp: implementation of WuwaImage.h
//
// handles image recognition with stb_image, stb_image_write
//
// link to Git Repository of stb: https://github.com/nothings/stb
// 
// version 1.0
// by Dropkick
// Nov 25, 2025
//
#include "WuwaImage.h"
#include "stb_image.h"
#include "stb_image_resize2.h"
#include "stb_image_write.h"

WuwaImage::WuwaImage(const std::string& filepath) {
	img = stbi_load(filepath.c_str(), &width, &height, &channels, 0);
	if (img == NULL) {
		std::cerr << "Cannot Load Image" << std::endl;
		exit(1);
	}
}

WuwaImage::~WuwaImage() {
	stbi_image_free(img);
}

// confirm the image is legal
bool WuwaImage::IsWuwaImage() {
	// resolution not correct
	if (width != 1920 || height != 1080) {
		std::cerr << "resolution of image not correct!" << std::endl;
		return false;
	}

	return true;
}

// get pixel at (x,y)
int WuwaImage::GetPixelIndex(int x, int y) {
	return (y * width + x) * channels;
}

// for debugging: show resolution and some pixels
void WuwaImage::PrintInfo() {
	std::cout << width << ", " << height << std::endl;
	for (int i = 0; i < 100; i++) {
		size_t pixel_index = (0 * width + i) * channels;

		unsigned int r = img[pixel_index];
		unsigned int g = img[pixel_index + 1];
		unsigned int b = img[pixel_index + 2];
		unsigned int a = img[pixel_index + 3];
		std::cout << r << " " << g << " " << b << " " << a << std::endl;
	}
}

bool WuwaImage::CompareWithEcho(const std::string& filepath, int slot) {
	// load echo image
	int echo_h, echo_w, echo_ch;
	unsigned char* echo = stbi_load(filepath.c_str(), &echo_w, &echo_h, &echo_ch, 0);
	if (echo == NULL) {
		std::cerr << "Cannot Load Echo Image" << std::endl;
		exit(1);
	}

	int similar_pixels = 0;
	int total_pixels = 0;
	int start_height;
	int start_width;
	// start position of echo picture at slot
	switch (slot) {
	case 1:
		start_height = 22;
		start_width = 651;
		break;
	case 2:
		start_height = 397;
		start_width = 651;
		break;
	case 3:
		start_height = 771;
		start_width = 651;
		break;
	case 4:
		start_height = 1145;
		start_width = 651;
		break;
	case 5:
		start_height = 1518;
		start_width = 651;
		break;
	}
	// compare each non-black pixel
	for (int j = 0; j < 180; j++) {
		for (int i = 0; i < 190; i++) {
			// ignore black pixel (treat as background)
			if (DiffVal(echo[(j * echo_w + i) * echo_ch], 0) < 50 || (echo_ch >=3 && DiffVal(echo[(j * echo_w + i) * echo_ch+3], 0) < 10)) {
				//std::cout << ' ';
				continue;
			}
			// compare RGB value of each pixel
			if (DiffVal(img[GetPixelIndex(start_height + i, start_width + j)], echo[(j * echo_w + i) * echo_ch]) < 20)
			if (DiffVal(img[GetPixelIndex(start_height + i, start_width + j)+1], echo[(j * echo_w + i) * echo_ch+1]) < 20)
			if (DiffVal(img[GetPixelIndex(start_height + i, start_width + j)+2], echo[(j * echo_w + i) * echo_ch+2]) < 20) {
				similar_pixels++;
				total_pixels++;
				//std::cout << 1;
				continue;
			}
			total_pixels++;
			//std::cout << 0;
			
				
		}
		//std::cout << std::endl;
	}
	//std::cout << similar_pixels << " / " << total_pixels << " = " << (float)similar_pixels/total_pixels << std::endl;
	stbi_image_free(echo);
	// prevent divide_by_zero issue & prevent empty slot pollute the data base
	if (total_pixels == 0)
		return false;
	// if more than 80% pixels are similar, we treat it as the same image
	return (float)similar_pixels / total_pixels > 0.80f;
}

// compare the echo set at slot with the known echo set at file path
bool WuwaImage::CompareWithEchoSet(const std::string& filepath, int slot) {
	// load echo set image
	int echoset_h, echoset_w, echoset_ch;
	unsigned char* echoset = stbi_load(filepath.c_str(), &echoset_w, &echoset_h, &echoset_ch, 0);
	if (echoset == NULL) {
		std::cerr << "Cannot Load Echo Set Image" << std::endl;
		exit(1);
	}

	int similar_pixels = 0;
	int total_pixels = 0;
	int start_height;
	int start_width;
	// start position of echo set mark at slot
	switch (slot) {
	case 1:
		start_height = 267;
		start_width = 662;
		break;
	case 2:
		start_height = 640;
		start_width = 662;
		break;
	case 3:
		start_height = 1014;
		start_width = 662;
		break;
	case 4:
		start_height = 1389;
		start_width = 662;
		break;
	case 5:
		start_height = 1763;
		start_width = 662;
		break;
	}
	// compare each non-black pixel
	for (int j = 0; j < 50; j++) {
		for (int i = 0; i < 50; i++) {
			// ignore black pixel (treat as background)
			if (DiffVal(echoset[(j * echoset_w + i) * echoset_ch], 0) < 200 || (echoset_ch >= 3 && DiffVal(echoset[(j * echoset_w + i) * echoset_ch + 3], 0) < 10)) {
				//std::cout << ' ';
				continue;
			}
			// compare RGB value of each pixel
			if (DiffVal(img[GetPixelIndex(start_height + i, start_width + j)], echoset[(j * echoset_w + i) * echoset_ch]) < 25)
			if (DiffVal(img[GetPixelIndex(start_height + i, start_width + j) + 1], echoset[(j * echoset_w + i) * echoset_ch + 1]) < 25)
			if (DiffVal(img[GetPixelIndex(start_height + i, start_width + j) + 2], echoset[(j * echoset_w + i) * echoset_ch + 2]) < 25) {
				similar_pixels++;
				total_pixels++;
				//std::cout << 1;
				continue;
			}
			total_pixels++;
			//std::cout << 0;


		}
		//std::cout << std::endl;
	}
	//std::cout << similar_pixels << " / " << total_pixels << " = " << (float)similar_pixels/total_pixels << std::endl;
	stbi_image_free(echoset);
	// prevent divide_by_zero issue & prevent empty slot pollute the data base
	if (total_pixels == 0)
		return true;
	// if more than 80% pixels are similar, we treat it as the same image
	return (float)similar_pixels / total_pixels > 0.80f;
}

// create a new echo picture
void WuwaImage::GenerateNewEcho(const std::string& savepath, int slot)
{
	int start_height;
	int start_width;
	// start position of echo at slot
	switch (slot) {
	case 1:
		start_height = 22;
		start_width = 651;
		break;
	case 2:
		start_height = 397;
		start_width = 651;
		break;
	case 3:
		start_height = 771;
		start_width = 651;
		break;
	case 4:
		start_height = 1145;
		start_width = 651;
		break;
	case 5:
		start_height = 1518;
		start_width = 651;
		break;
	}
	
	// copy slot pixels to a new image
	unsigned char* new_img = new unsigned char[180 * 190 * channels];
	for (int j = 0; j < 180; j++) {
		for (int i = 0; i < 190; i++) {
			for (int k = 0; k < channels; k++) {
				new_img[(j * 190 + i) * channels + k] = img[GetPixelIndex(start_height + i, start_width + j) + k];
			}
		}
	}

	// record this new echo
	stbi_write_jpg((savepath + "/echo" + std::to_string(slot) + ".jpeg").c_str(), 190, 180, channels, new_img, 100);
	std::cerr << "New echo found at slot " << slot << ", saved to " << savepath + "/echo" + std::to_string(slot) + ".jpeg" << std::endl;
	stbi_image_free(new_img);
}

// create a new echo set picture
void WuwaImage::GenerateNewEchoSet(const std::string& savepath, int slot)
{
	int start_height;
	int start_width;
	// start position of echo set at slot
	switch (slot) {
	case 1:
		start_height = 267;
		start_width = 662;
		break;
	case 2:
		start_height = 640;
		start_width = 662;
		break;
	case 3:
		start_height = 1014;
		start_width = 662;
		break;
	case 4:
		start_height = 1389;
		start_width = 662;
		break;
	case 5:
		start_height = 1763;
		start_width = 662;
		break;
	}

	// copy slot pixels to a new image
	unsigned char* new_img = new unsigned char[50 * 50 * channels];
	for (int j = 0; j < 50; j++) {
		for (int i = 0; i < 50; i++) {
			for (int k = 0; k < channels; k++) {
				new_img[(j * 50 + i) * channels + k] = img[GetPixelIndex(start_height + i, start_width + j) + k];
			}
		}
	}

	// record this new echo set
	stbi_write_jpg((savepath + "/echoset" + std::to_string(slot) + ".jpeg").c_str(), 50, 50, channels, new_img, 100);
	std::cerr << "\nNew echo set found at slot " << slot << ", saved to " << savepath + "/echoset" + std::to_string(slot) + ".jpeg" << std::endl;
	stbi_image_free(new_img);
}

// confirm the slot is not empty
bool WuwaImage::IsEmptySlot(int slot) {
	int start_height;
	int start_width;
	// start position of the slot
	switch (slot) {
	case 1:
		start_height = 22;
		start_width = 651;
		break;
	case 2:
		start_height = 397;
		start_width = 651;
		break;
	case 3:
		start_height = 771;
		start_width = 651;
		break;
	case 4:
		start_height = 1145;
		start_width = 651;
		break;
	case 5:
		start_height = 1518;
		start_width = 651;
		break;
	}

	// count non-black pixels
	int non_empty_count = 0;
	for (int j = 0; j < 180; j++) {
		for (int i = 0; i < 190; i++) {
			if (img[GetPixelIndex(start_height + i, start_width + j)] > 50) {
				non_empty_count++;
			}
		}
	}
	// we treat echo with < 1% information as empty
	return non_empty_count < 342;
}

// abs of difference
int DiffVal(int a, int b) {
	if (a > b)
		return a - b;
	else
		return b - a;
}