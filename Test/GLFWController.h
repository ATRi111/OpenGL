#pragma once
#include"GLibrary/GLibrary.h"

class GLFWController
{
public:
	static GLFWwindow* window;
	static void EnableBlend()
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_CONSTANT_ALPHA);
	}

	static GLFWwindow* Init()
	{
		glfwInit();
		GLFWwindow* window = glfwCreateWindow(1920, 1080, "Window", NULL, NULL);
		glfwMakeContextCurrent(window);
		gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		return window;
	}
};