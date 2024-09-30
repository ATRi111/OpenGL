#pragma once
#include"GLibrary/ImGui/imgui.h"
#include"GLibrary/ImGui/imgui_impl_glfw.h"
#include"GLibrary/ImGui/imgui_impl_opengl3.h"

class ImGuiController
{
	ImGuiIO& io = ImGui::GetIO();
	bool show_demo_window;
	bool show_another_window;
	ImVec4 clear_color;
public:
	static void Init(GLFWwindow* window)
	{
		const char* glsl_version = "#version 130";
		ImGui::CreateContext();
		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init(glsl_version);
		ImGui::StyleColorsDark();
	}
	static void NewFrame()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
	}
	static void Draw()
	{
		ImGui::Render();
		ImGui::GetDrawData();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}
	static void Shutdown()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}

	ImGuiController()
		:show_demo_window(true), show_another_window(true), clear_color(0.45f, 0.55f, 0.60f, 1.00f)
	{
		io = ImGui::GetIO();
	}


	void ShowWindow()
	{
		if (show_demo_window)
			ImGui::ShowDemoWindow(&show_demo_window);
		static float f = 0.0f;
		static int counter = 0;

		if (show_demo_window)
			ImGui::ShowDemoWindow(&show_demo_window);


		ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

		ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
		ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
		ImGui::Checkbox("Another Window", &show_another_window);

		ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
		ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

		if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
			counter++;
		ImGui::SameLine();
		ImGui::Text("counter = %d", counter);

		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
		ImGui::End();

		if (show_another_window)
		{
			ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
			ImGui::Text("Hello from another window!");
			if (ImGui::Button("Close Me"))
				show_another_window = false;
			ImGui::End();
		}
	}
};