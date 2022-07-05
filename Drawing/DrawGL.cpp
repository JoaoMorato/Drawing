#include "DrawGL.h"
#include "GL/glew.h"

#include <cstdio>
#include <cstdlib>

void DrawRectPixel(int x, int y, int width, int height) {
	int size[4];
	glGetIntegerv(GL_VIEWPORT, size);

	double tamX = 2.0 / ((long long)size[2] - size[0]);
	double tamY = 2.0 / ((long long)size[3] - size[1]);

	double comecoX = -1 + x * tamX;
	double comecoY = 1 - y * tamY;
	double fimX = comecoX + width * tamX;
	double fimY = comecoY - height * tamY;

	glBegin(GL_QUADS);
	
	glVertex2d(comecoX, fimY);
	glVertex2d(fimX, fimY);
	glVertex2d(fimX, comecoY);
	glVertex2d(comecoX, comecoY);

	glEnd();
}

void DrawRectPercent(float x, float y, float width, float height) {
	int size[4];
	glGetIntegerv(GL_VIEWPORT, size);

	double tamX = 2.0 / ((long long)size[2] - size[0]);
	double tamY = 2.0 / ((long long)size[3] - size[1]);

	double pX = ((long long)size[2] - size[0]) / 100.0;
	double pY = ((long long)size[3] - size[1]) / 100.0;


	double comecoX = -1 + x * tamX * pX;
	double comecoY = 1 - y * tamY * pY;
	double fimX = comecoX + width * tamX * pX;
	double fimY = comecoY - height * tamY * pY;

	glBegin(GL_QUADS);

	glVertex2d(comecoX, fimY);
	glVertex2d(fimX, fimY);
	glVertex2d(fimX, comecoY);
	glVertex2d(comecoX, comecoY);

	glEnd();
}

void DrawColorRGB(unsigned char R, unsigned char G, unsigned char B) {
	glColor3b(R, G, B);
}

unsigned int CompileShader(const char* data, GLenum _e) {
	unsigned int shader = glCreateShader(_e);
	glShaderSource(shader, 1, &data, NULL);
	glCompileShader(shader);

	int result;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
	if (!result) {
		int length;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*)malloc(length);
		glGetShaderInfoLog(shader, length, &length, message);
		printf("Failed to compile shader(%i)!\n%s\n", (int)_e,message);
		glDeleteShader(shader);
		return 0;
	}

	return shader;
}

unsigned int CreateShader(const char* data) {
	unsigned int program = glCreateProgram();
	unsigned int vs = CompileShader(data, GL_VERTEX_SHADER);
	unsigned int fs = CompileShader(data, GL_FRAGMENT_SHADER);

	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vs);
	glDeleteShader(fs);

	return program;
}