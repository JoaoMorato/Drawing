#pragma once
#ifndef _DRAWGL_
#define _DRAWGL_

void DrawRectPixel(int x, int y, int width, int height);
void DrawRectPercent(float x, float y, float width, float height);

void DrawColorRGB(unsigned char R, unsigned char G, unsigned char B);

unsigned int CreateShader(const char* data);

#endif // !_DRAWGL_
