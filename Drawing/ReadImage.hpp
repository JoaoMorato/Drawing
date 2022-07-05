#pragma once
#ifndef _READ_IMAGE_
#define _READ_IMAGE_

#include <cstdio>
#include <cstdlib>

//#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

void ReadImageJPG(const char* file) {
	int channels;
	int width, height;
	unsigned char* img = stbi_load(file, &width, &height, &channels, 0);
	if (!img) {
		printf("Erro");
		return;
	}

	size_t size = width * height * channels;
	char grayChannels = channels == 4 ? 2 : 1;
	size_t sizeGray = width * height * grayChannels;
	unsigned char* grayImg = (unsigned char*)malloc(sizeGray);

	if (!grayImg) {
		printf("No gray");
		stbi_image_free(img);
		return;
	}

	for (unsigned char* p = img, *pg = grayImg; p != img + size; p += channels, pg += grayChannels) {
		*pg = (uint8_t)((*p + *(p + 1) + *(p + 2)) / 3);
		if (channels == 4) {
			*(pg + 1) = *(p + 3);
		}
	}

	stbi_write_jpg("test.jpg", width, height, grayChannels, grayImg, 100);
	

	printf_s("W: %i\nH: %i\nC: %i", width, height, channels);

	stbi_image_free(img);
}


#endif // !_READ_IMAGE_
