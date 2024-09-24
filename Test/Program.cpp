#include"GLibrary/GLibrary.h"
#include"include/glfw3.h"
#include"GLibrary/ImGui/imgui.h"
#include"GLibrary/ImGui/imgui_impl_glfw.h"
#include"GLibrary/glm/glm.hpp"
#include"GLibrary/glm/ext/matrix_clip_space.hpp"
#include"GLibrary/glm/ext/matrix_transform.hpp"
#include"GLibrary/ImGui/imgui_impl_opengl3.h"

using namespace GLibrary;
using namespace std;

float vertices[] = 
{
    -0.8f,-0.5f,0,0,
    0.8f,-0.5f,1,0,
    0.8f,0.5f,1,1,
    -0.8f,0.5f,0,1,
};

unsigned int indicies[] =
{
    0,1,2,
    2,3,0,
};

static void APIENTRY DebugCallback(
    unsigned int source,
    unsigned int type,
    unsigned int id,
    unsigned int severity,
    GLsizei length,
    const GLchar* message,
    const void* userParam) 
{
    std::cout << "GLDebug: " << message << std::endl;
}

int main(int argc, char* argv[])
{
    string solutionDir = argv[0];
    solutionDir = solutionDir.substr(0, solutionDir.find("\\OpenGL\\")) + "\\OpenGL\\OpenGL\\";
    string shaderPath = solutionDir + "Test\\TestShader.shader";
    string texturePath = solutionDir + "Test\\Haruhi Kyousou.png";

    GLFWwindow* window;

    if (!glfwInit())
        return -1;

    window = glfwCreateWindow(1920, 1080, "Window", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        glfwTerminate();
        return -1;
    }

    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(DebugCallback, nullptr);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_CONSTANT_ALPHA);

    VertexArray va;
    VertexBuffer vb(vertices, sizeof(vertices), GL_STATIC_DRAW);
    IndexBuffer ib(indicies, sizeof(indicies), GL_STATIC_DRAW);
    
    VertexBufferLayout layout;
    layout.AddProperty<float>(0, 2);
    layout.AddProperty<float>(1, 2);
    va.SetLayout(layout);

    ShaderProgram program = ShaderProgram::ParseFile(shaderPath);
    program.Link();
    program.Bind();

    program.SetUniform4f("u_Color", 1, 0, 1, 1);
    program.SetUniform1i("u_Texture", 0);
    glm::mat4 Mproj = glm::ortho(-0.8f, 0.8f, -0.5f, 0.5f, -1.0f, 1.0f);
    glm::mat4 Mview = glm::translate(glm::mat4(1.0f), glm::vec3(-0.1f, 0, 0));
    glm::mat4 Mmodel = glm::mat4(1.0f);

    program.SetUniformMat4f("u_Mproj", Mproj);
    program.SetUniformMat4f("u_Mview", Mview);
    program.SetUniformMat4f("u_Mmodel", Mmodel);

    Texture2D texture = Texture2D::ParseFile(texturePath);

    Renderer renderer;

    const char* glsl_version = "#version 130";
    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);
    ImGui::StyleColorsDark();

    ImGuiIO& io = ImGui::GetIO();
    bool show_demo_window = true;
    bool show_another_window = false;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    while (!glfwWindowShouldClose(window))
    {
        renderer.Clear();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        renderer.Draw(va, ib, program);

        // 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
        if (show_demo_window)
            ImGui::ShowDemoWindow(&show_demo_window);

        // 2. Show a simple window that we create ourselves. We use a Begin/End pair to create a named window.
        {
            static float f = 0.0f;
            static int counter = 0;

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
        }

        // 3. Show another simple window.
        if (show_another_window)
        {
            ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
            ImGui::Text("Hello from another window!");
            if (ImGui::Button("Close Me"))
                show_another_window = false;
            ImGui::End();
        }

        ImGui::Render();
        ImGui::GetDrawData();
        
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();
    return 0;
}