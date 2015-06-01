//render.h

#ifndef RENDER_H
#define RENDER_H

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cstdlib>
#include <vector>
#include "atlas.h"
#include <iostream>

class Render {
	private:
		void initVertexShader();
		void initFragmentShader();
		void initShader();
		void bindTexture(unsigned char* image_data);

		const GLchar* vertexSource;
		const GLchar* fragmentSource;
		GLuint shaderProgram, fragmentShader, vertexShader;
		GLuint vbo, ebo;
		std::vector<GLfloat> vertices;
		std::vector<GLuint> elements;
		GLFWwindow* window;
		int width, height;
	public:
		Render(int widght, int height, unsigned char* image_data, GLFWwindow* window);
		~Render();
		void addImage(int x, int y, const Coords& coords);
		void render();
};

#endif 
