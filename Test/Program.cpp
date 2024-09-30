#include"DebugController.h"
#include"GameObject.h"
#include"include/glfw3.h"
#include"Camera.h"
#include"GLFWController.h"
#include"ImGuiController.h"

using namespace GLibrary;
using namespace std;

float vertices[] = 
{
    -0.8f,-0.5f,0.0f,0,0,
    0.8f,-0.5f,0.0f,1,0,
    0.8f,0.5f,0.0f,1,1,
    -0.8f,0.5f,0.0f,0,1,
};

unsigned int indicies[] =
{
    0,1,2,
    2,3,0,
};

int main(int argc, char* argv[])
{
    string solutionDir = argv[0];
    solutionDir = solutionDir.substr(0, solutionDir.find("\\OpenGL\\")) + "\\OpenGL\\OpenGL\\";
    string shaderPath = solutionDir + "Test\\TestShader.shader";
    string texturePath = solutionDir + "Test\\Haruhi Kyousou.png";

    GLFWwindow* window = GLFWController::Init();
    ImGuiController::Init(window);
    DebugController debugController;
    GLFWController::EnableBlend();


    VertexArray va;
    VertexBuffer vb(vertices, sizeof(vertices), GL_STATIC_DRAW);
    IndexBuffer ib(indicies, sizeof(indicies), GL_STATIC_DRAW);
    
    VertexBufferLayout layout;
    layout.AddProperty<float>(0, 3);
    layout.AddProperty<float>(1, 2);
    va.SetLayout(layout);

    ShaderProgram program = ShaderProgram::ParseFile(shaderPath);
    program.Link();
    program.Bind();

    program.SetUniform4f("u_Color", 1, 0, 1, 1);
    program.SetUniform1i("u_Texture", 0);

    OrthographicCamera camera(1.6f, 1.0f);
    GameObject obj;
    obj.SetRotation(glm::vec3(45.0f, 0, 0));
    Translater::Print(obj.ModelMatrix());
    program.SetUniformMat4f("u_modelMatrix", obj.ModelMatrix());
    program.SetUniformMat4f("u_viewMatrix", camera.ViewMatrix());
    program.SetUniformMat4f("u_projectionMatrix", camera.ProjectionMatrix());

    Texture2D texture = Texture2D::ParseFile(texturePath);
    Renderer renderer;
    ImGuiController windowController;

    while (!glfwWindowShouldClose(window))
    {
        renderer.Clear();

        windowController.NewFrame();

        renderer.Draw(va, ib, program);

        windowController.ShowWindow();
       
        ImGuiController::Draw();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    ImGuiController::Shutdown();
    glfwTerminate();
    return 0;
}