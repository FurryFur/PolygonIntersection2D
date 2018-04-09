#include "Triangle.h"
#include "Point.h"
#include "ShapeFactory.h"
#include "Shape.h"

#include <glm\glm.hpp>
#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include <nanovg.h>
#define NANOVG_GL3_IMPLEMENTATION
#include <nanovg_gl.h>

#include <iostream>

using namespace glm;

void errorcb(int error, const char* desc)
{
	printf("GLFW error %d: %s\n", error, desc);
}

void key(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

void mouseBtnCallback(GLFWwindow* window, int button, int action, int mods) 
{
	double mousex, mousey;
	glfwGetCursorPos(window, &mousex, &mousey);
	ShapeFactory::instance().onClick(button, action, mousex, mousey);
}

int main()
{
	GLFWwindow* window;
	NVGcontext* vg = NULL;


	if (!glfwInit()) {
		printf("Failed to init GLFW.");
		return -1;
	}

	glfwSetErrorCallback(errorcb);
#ifndef _WIN32 // don't require this on win32, and works with more cards
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#endif
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, 1);

	window = glfwCreateWindow(1000, 600, "NanoVG", NULL, NULL);
	//	window = glfwCreateWindow(1000, 600, "NanoVG", glfwGetPrimaryMonitor(), NULL);
	if (!window) {
		glfwTerminate();
		return -1;
	}

	glfwSetMouseButtonCallback(window, mouseBtnCallback);
	glfwSetKeyCallback(window, key);

	glfwMakeContextCurrent(window);
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	glfwSwapInterval(1);

	vg = nvgCreateGL3(NVG_ANTIALIAS | NVG_STENCIL_STROKES | NVG_DEBUG);
	if (vg == NULL) {
		printf("Could not init nanovg.\n");
		return -1;
	}

	ShapeFactory& shapeFactory = ShapeFactory::instance();
	while (!glfwWindowShouldClose(window)) {
		int winWidth, winHeight;
		int fbWidth, fbHeight;
		float pxRatio;

		glfwGetWindowSize(window, &winWidth, &winHeight);
		glfwGetFramebufferSize(window, &fbWidth, &fbHeight);
		// Calculate pixel ration for hi-dpi devices.
		pxRatio = (float)fbWidth / (float)winWidth;

		// Update and render
		glViewport(0, 0, fbWidth, fbHeight);
		glClearColor(0.3f, 0.3f, 0.32f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

		nvgBeginFrame(vg, winWidth, winHeight, pxRatio);

		const std::vector<std::unique_ptr<Shape>>& shapeList = shapeFactory.getShapeList();
		for (auto& shape : shapeList) {
			shape->draw(vg);
		}

		const Triangle* triangle = shapeFactory.getTriangle();
		const Point* point = shapeFactory.getPoint();
		if (triangle && point) {
			if (point->inside(*triangle))
				std::cout << "Point inside triangle" << std::endl;
			else
				std::cout << "Point outside triangle" << std::endl;
		}

		nvgEndFrame(vg);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	nvgDeleteGL3(vg);

	glfwTerminate();
	return 0;
}