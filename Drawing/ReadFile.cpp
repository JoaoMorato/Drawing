#include "ReadFile.hpp"
#include <fstream>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

std::string UperCase(std::string s) {
	for (size_t i = 0; i < s.size(); i++) {
		if (s[i] < 'a' || s[i] > 'z') continue;
		char diff = s[i] - 'a';
		s[i] = 'A' + diff;
	}
	return s;
}

std::string LowerCase(std::string s) {
	for (size_t i = 0; i < s.size(); i++) {
		if (s[i] < 'A' || s[i] > 'Z') continue;
		char diff = s[i] - 'A';
		s[i] = 'a' + diff;
	}
	return s;
}


int JumpFile(std::string file) {
	file = LowerCase(file);
	if (file == "png") return 0;
	if (file == "jpg" || file == "jpeg" || file == "jpe" || file == "jfif" || file == "jfi") return 0;
	if (file == "bmp") return 0;
}

int GetFile(const char* file, unsigned char* buffer, unsigned int *size) {
	std::string fim = "";
	int cont = 0;
	while (file[cont++]);
	cont--;
	while (cont) {
		if (file[cont] == '.')
			break;
		fim = file[cont--] + fim;
	}
	int width, height, comp;
	unsigned char* data = NULL;
	fim = LowerCase(fim);
	if(fim == "png")
		data = stbi_load(file, &width, &height, &comp, STBI_rgb_alpha);
	else if(fim == "jpg" || fim == "jpeg")
		data = stbi_load(file, &width, &height, &comp, STBI_rgb);

	if (data) {

	}
	else return 0;


	return 1;
}