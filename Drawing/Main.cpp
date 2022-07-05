#define GLEW_STATIC
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <list>
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "ReadImage.hpp"
#include "InputKey.hpp"
#include "Button.hpp"
#include "DrawGL.h"
#include "ConfigFile.hpp"

GLFWwindow* mainWindow;

const int xMin = 1280;
const int yMin = 720;

int xActual = 0;
int yActual = 0;

std::list<Tab> tabs = std::list<Tab>();
char* fileOpenned = 0;

void Resize(GLFWwindow* win, int x, int y) {
	if (win == mainWindow) {
		xActual = x;
		yActual = y;
		glViewport(0, 0, x, y);
	}
}

bool InitOpenGL() {
	mainWindow = glfwCreateWindow(xMin, yMin, "DrawDrawing", NULL, NULL);

	xActual = xMin;
	yActual = yMin;

	if (mainWindow == NULL)
		return 0;

	glfwSetWindowSizeCallback(mainWindow, Resize);
	glfwSetWindowSizeLimits(mainWindow, xMin, yMin, GLFW_DONT_CARE, GLFW_DONT_CARE);

	glfwMakeContextCurrent(mainWindow);
	return 1;
}

void DrawGrid(int sizeX, int sizeY, unsigned char* buffer) {
	
}

void ChageBufferSize(int newX, int newY, unsigned char* buffer) {
	buffer = (unsigned char*)malloc(newX * newY);
}

void ShowProjects() {
	GLFWwindow* view;
	view = glfwCreateWindow(300, 200, "Explorer", NULL, NULL);
	if (!view) {
		glfwMakeContextCurrent(mainWindow);
		return;
	}
	glfwMakeContextCurrent(view);
	while (!glfwWindowShouldClose(view)) {
		glClear(GL_COLOR_BUFFER_BIT);

		if (Input::GetKeyUp(Key::ESCAPE)) {
			glfwSetWindowShouldClose(view, 1);
		}
		glfwSwapBuffers(view);
		Input::ClearKeys();
		glfwPollEvents();
	}
	glfwDestroyWindow(view);
	glfwMakeContextCurrent(mainWindow);
}

void CreateImage(const char* data, std::list<Tab>::iterator tab) {
	if (tab->id) return;
	tab->id = CreateShader(data);
}

void DestroyImage(std::list<Tab>::iterator tab) {
	glDeleteProgram(tab->id);
	tabs.erase(tab);
}

bool Exit() {
	GLFWwindow* win = glfwCreateWindow(200, 70, "Exit", NULL, NULL);
	if (!win) {
		glfwMakeContextCurrent(mainWindow);
		return 1;
	}
	glfwMakeContextCurrent(win);
	glViewport(0, 0, 200, 70);
	Button ok("Fechar", 10, 20, 80, 30);
	ok.SetRGB(50, 50, 50);
	Button nao("Cancelar", 110, 20, 80, 30);
	nao.SetRGB(50, 50, 50);
	bool fechar = false;

	while (!glfwWindowShouldClose(win)) {
		glClear(GL_COLOR_BUFFER_BIT);
		if (ok.Update()) {
			fechar = true;
			glfwSetWindowShouldClose(win, 1);
		}
		if (nao.Update() || Input::GetKeyDown(Key::ESCAPE)) {
			glfwSetWindowShouldClose(win, 1);
		}
		glfwSwapBuffers(win);
		Input::ClearKeys();
		glfwPollEvents();
	}
	glfwDestroyWindow(win);
	glfwMakeContextCurrent(mainWindow);
	return fechar;
}

void MainUpdate() {
	bool fechar = false;
	while (!fechar) {
		//glViewport(0, 0, width, height);
		if (glfwWindowShouldClose(mainWindow)) {
			fechar = Exit();
			if (!fechar)
				glfwSetWindowShouldClose(mainWindow, 0);
		}
		glClear(GL_COLOR_BUFFER_BIT);

		if (Input::GetKeyUp(Key::ESCAPE)) 
			glfwSetWindowShouldClose(mainWindow, 1);

		if (Input::GetKey(Key::LEFT_CTRL) && Input::GetKeyDown(Key::O))
			ShowProjects();

		glfwSwapBuffers(mainWindow);
		Input::ClearKeys();
		glfwPollEvents();
	}
	for (auto it = tabs.begin(); it != tabs.end(); it++) {
		DestroyImage(it);
	}
}

int main(int argc, char* argv[]) {
	if (!glfwInit())
		return -1;
	if (!InitOpenGL()) {
		glfwTerminate();
		return -5;
	}
	if (glewInit()) {
		glfwDestroyWindow(mainWindow);
		glfwTerminate();
		return -1;
	}

	if (argc > 1) fileOpenned = argv[1];

	MainUpdate();

	glfwDestroyWindow(mainWindow);
	glfwTerminate();
	return 0;
}