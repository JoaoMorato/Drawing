#include "Button.hpp"
#include "InputKey.hpp"
#include "DrawGL.h"

Button::Button(const char* c, int x, int y, unsigned int x1, unsigned int y1) {
	SetText(c);
	SetPosition(x, y);
	SetSize(x1, y1);
	//red = 0, green = 0, blue = 0;
	SetRGB(0, 255, 255);
}

Button::Button() {
	SetPosition(0, 0);
	SetSize(10, 10);
	SetRGB(255, 255, 255);
}

void Button::SetPosition(int x, int y) {
	posX = x;
	posY = y;
}

void Button::SetSize(unsigned int x, unsigned int y) {
	sizeX = x;
	sizeY = y;
}

void Button::SetText(const char* c) {
	frase = c;
}

void Button::SetRGB(unsigned char r, unsigned char g, unsigned char b) {
	red = r, green = g, blue = b;
}

bool Button::Update() {
	if (!enable) return 0;

	DrawColorRGB(red, green, blue);
	DrawRectPixel(posX, posY, sizeX, sizeY);
	bool click = false;

	COORD posi = Input::GetMousePosition();
	if (posi.x >= posX && posi.x <= (posX + (long long)sizeX) &&
		posi.y >= posY && posi.y <= (posY + (long long)sizeY))
	{
		if (Input::GetMouseDown(0)) {
			for (auto it = func.begin(); it != func.end(); it++) {
				it->operator()();
			}
			click = true;
		}
	}
	return click;
}

void Button::AddAction(std::function<void(void)> a) {
	func.push_back(a);
}

bool Button::RemoveAction(unsigned int pos) {
	int n = 0;
	for (auto it = func.begin(); it != func.end(); it++, n++) {
		if (n < pos) continue;
		func.erase(it);
		return true;
	}
	return 0;
}