#pragma once
#include"GLibrary/GLibrary.h"

class Initializer
{
public:
	static GLFWwindow* window;
	static void EnableBlend()
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_CONSTANT_ALPHA);
	}

	static GLFWwindow* InitGLFW()
	{
		glfwInit();
		window = glfwCreateWindow(1920, 1080, "Window", NULL, NULL);
		glfwMakeContextCurrent(window);
		gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		return window;
	}

	static void InitImGui()
	{
		const char* glsl_version = "#version 130";
		ImGui::CreateContext();
		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init(glsl_version);
		ImGui::StyleColorsDark();
	}

	static void ShutDownImGui()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}
};

GLFWwindow* Initializer::window = nullptr;