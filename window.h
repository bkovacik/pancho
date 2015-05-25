//window.h

#include "GLFW/glfw3.h"
#include <chrono>
#include <thread>
#include <iostream>

#ifndef WINDOW_H
#define WINDOW_H

enum wType {WINDOWED, BORDERLESS, FULLSCREEN};

GLFWwindow* createWindow(int width, int height, wType type);

#endif
