#pragma once
#ifndef _WINDOW_UTILS_H_
#define _WINDOW_UTILS_H_

struct Window { struct GLFWwindow *handle; int width, height; };
Window openContext(int width = 640, int height = 480, char *name = "Default");
bool updateContext(const Window &w);
void closeContext(const Window &w);

float getDeltaTime();


#endif