//render.h

#ifndef RENDER_H
#define RENDER_H

#define GLEW_STATIC
#define BACK_TEX_WIDTH 128
#define BACK_TEX_HEIGHT 128

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cstdlib>
#include <vector>
#include "atlas.h"
#include <iostream>

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods); 

class Render {
	private:
		void initVertexShader();
		void initFragmentShader();
		void initShader();
		void bindTexture(unsigned char* image_data);
		void shiftImage(float offX, float offY, int objOffset);

		const GLchar* vertexSource;
		const GLchar* fragmentSource;
		GLuint shaderProgram, fragmentShader, vertexShader;
		GLuint vbo, ebo, vao;
		std::vector<GLfloat> vertices;
		std::vector<GLfloat> move;
		std::vector<GLuint> elements;
		GLFWwindow* window;
		int width, height, frames;
		double lastTime;
	public:
		Render(int widght, int height, unsigned char* image_data, GLFWwindow* window);
		~Render();
		void addImage(int x, int y, const Coords& coords, int offX, int offY);
		void addImage(int x, int y, const Coords& coords);
		void setMovement(float offX, float offY, int objOffset);
		void render(int fps, int scroll = 180);
};

#endif 
