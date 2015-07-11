//window.h

#ifndef WINDOW_H
#define WINDOW_H

#include <GLFW/glfw3.h>
#include <chrono>
#include <thread>

enum wType {WINDOWED, BORDERLESS, FULLSCREEN};

class Window {
	static GLFWwindow* window_;
	static int width_, height_;

	static class InitWindow {
		public:
			InitWindow();
			~InitWindow() {glfwTerminate();}
	} init;

	public:
		static GLFWwindow* getWindow() {return window_;}
		static int getWidth() {return width_;}
		static int getHeight() {return height_;}
		static void setWidth(int width) {width_ = width;glViewport(0, 0, width_, height_);glfwSetWindowSize(window_, width_, height_);}
		static void setHeight(int height) {height_ = height;glViewport(0, 0, width_, height_);glfwSetWindowSize(window_, width_, height_);}
};

#endif
