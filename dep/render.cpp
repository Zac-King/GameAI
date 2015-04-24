#include "render.h"
#include <iostream>
#include <GL\glew.h>
#include <GL\wglew.h>
#include <GLFW\glfw3.h>

Window openContext(int width, int height, char *name)
{
	Window r = {nullptr, width, height};
	glfwInit();
	r.handle = glfwCreateWindow(width, height, name, NULL, NULL);
	glfwMakeContextCurrent(r.handle);
	if (glewInit() != GLEW_OK) glfwTerminate();	
	return r;
}

bool updateContext(const Window &w)
{
	glfwSwapBuffers(w.handle);
	glfwPollEvents();
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	return !glfwWindowShouldClose(w.handle);

}

void closeContext(const Window &w)
{
	glfwDestroyWindow(w.handle);
	glfwTerminate();
}