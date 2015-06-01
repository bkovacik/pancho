//window.h

#ifndef WINDOW_H
#define WINDOW_H

#include <GLFW/glfw3.h>
#include <chrono>
#include <thread>

enum wType {WINDOWED, BORDERLESS, FULLSCREEN};

GLFWwindow* createWindow(int width, int height, wType type);

#endif
