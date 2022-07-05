#pragma once
#ifndef _BUTTON_
#define _BUTTON_

#include <sstream>
#include <functional>
#include <vector>

class Button {
private:
	unsigned int sizeX;
	unsigned int sizeY;
	int posX;
	int posY;
	std::string frase;
	std::vector <std::function<void(void)>> func;
	unsigned char red, green, blue;
public:
	bool enable = true;
	Button(const char*, int posX = 0, int posY = 0, unsigned int width = 1, unsigned int heigth = 1);
	Button();

	void SetText(const char*);
	void SetPosition(int x, int y);
	void SetSize(unsigned int width, unsigned int heigth);
	void SetRGB(unsigned char r, unsigned char g, unsigned char b);
	void AddAction(std::function<void(void)>);
	bool RemoveAction(unsigned int posi);

	bool Update();
};

#endif // !_BUTTON_