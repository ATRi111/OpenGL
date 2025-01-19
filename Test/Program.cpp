#include"DebugController.h"
#include"GameObject.h"
#include"include/glfw3.h"
#include"Camera.h"
#include"GLFWController.h"
#include"ImGuiController.h"
#include"Sprite.h"

using namespace GLibrary;
using namespace std;

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

    OrthographicCamera camera;
    camera.SetWidth(1.6f);
    camera.SetHeight(1.0f);

    Texture2D texture = Texture2D::ParseFile(texturePath);
    texture.Bind(1);

    DefaultSprite sp(texture, 1446);

    GameObject obj1;
    obj1.SetPosition(glm::vec3(0, 0, -1));

    ShaderProgram program = ShaderProgram::ParseFile(shaderPath);
    program.Link();
    program.Bind();

    program.SetUniform4f("u_Color", 1, 0, 1, 1);
    program.SetUniform1i("u_Texture", 1);
    program.SetUniformMat4f("u_modelMatrix", obj1.ModelMatrix());
    program.SetUniformMat4f("u_viewMatrix", camera.ViewMatrix());
    program.SetUniformMat4f("u_projectionMatrix", camera.ProjectionMatrix());

    Renderer renderer;
    ImGuiController windowController;

    while (!glfwWindowShouldClose(window))
    {
        renderer.Clear();

        windowController.NewFrame();

        renderer.Draw(sp.VA(), sp.IB(), program);

        windowController.ShowWindow();
       
        ImGuiController::Draw();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    ImGuiController::Shutdown();
    glfwTerminate();
    return 0;
}