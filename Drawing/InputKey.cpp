#include "InputKey.hpp"
#include "GLFW/glfw3.h"
#include <vector>
#include <iostream>

#define MAX_KEY  5

std::vector<Key> keys;
std::vector<Key> keyDown;
std::vector<Key> keyUp;
std::vector<int> mouse;
std::vector<int> mouseDown;
std::vector<int> mouseUp;
double mouseX = 0;
double mouseY = 0;

bool init = false;
GLFWwindow* lastWin;

void InputKey(GLFWwindow* w, int key, int scan, int action, int special) {
	switch (action) {
	case GLFW_PRESS:
		if (keys.size() < MAX_KEY) {
			keys.push_back(Key(key));
		}
		if (keyDown.size() < MAX_KEY) {
			keyDown.push_back(Key(key));
		}
		break;
	case GLFW_RELEASE:
		if (keyUp.size() < MAX_KEY) {
			keyUp.push_back(Key(key));
		}
		for (auto it = keys.begin(); it != keys.end(); it++) {
			if (*it != Key(key)) continue;
			keys.erase(it);
			break;
		}
	}
}

bool Input::GetKey(Key k) {
	for (int i = 0; i < keys.size(); i++) {
		if (keys[i] == k)
			return 1;
	}
	return 0;
}

bool Input::GetKeyDown(Key k) {
	for (int i = 0; i < keyDown.size(); i++) {
		if (keyDown[i] == k)
			return 1;
	}
	return 0;
}

bool Input::GetKeyUp(Key k) {
	for (int i = 0; i < keyUp.size(); i++) {
		if (keyUp[i] == k)
			return 1;
	}
	return 0;
}

COORD Input::GetMousePosition() {
	return { mouseX, mouseY };
}

bool Input::GetMouse(int b) {
	for (int i = 0; i < mouse.size(); i++) {
		if (mouse[i] == b)
			return 1;
	}
	return 0;
}

bool Input::GetMouseDown(int b) {
	for (int i = 0; i < mouseDown.size(); i++) {
		if (mouseDown[i] == b)
			return 1;
	}
	return 0;
}

bool Input::GetMouseUp(int b) {
	for (int i = 0; i < mouseUp.size(); i++) {
		if (mouseUp[i] == b)
			return 1;
	}
	return 0;
}

void CursorPosition(GLFWwindow* win, double x, double y) {
	mouseX = x;
	mouseY = y;
}

void MouseClick(GLFWwindow* w, int button, int action, int mode) {
	switch (action) {
	case GLFW_PRESS:
		if (mouse.size() < MAX_KEY) {
			mouse.push_back(button);
		}
		if (mouseDown.size() < MAX_KEY) {
			mouseDown.push_back(button);
		}
		break;
	case GLFW_RELEASE:
		if (mouseUp.size() < MAX_KEY) {
			mouseUp.push_back(button);
		}
		for (auto it = mouse.begin(); it != mouse.end(); it++) {
			if (*it != button) continue;
			mouse.erase(it);
			break;
		}
	}
}

void Input::ClearKeys() {
	if (!init || glfwGetCurrentContext() != lastWin) {
		lastWin = glfwGetCurrentContext();
		if (lastWin == NULL) {
			init = false;
			return;
		}
		glfwSetKeyCallback(lastWin, InputKey);
		glfwSetCursorPosCallback(lastWin, CursorPosition);
		glfwSetMouseButtonCallback(lastWin, MouseClick);
		init = true;
	}
	keyDown.clear();
	keyUp.clear();
	mouseDown.clear();
	mouseUp.clear();
}