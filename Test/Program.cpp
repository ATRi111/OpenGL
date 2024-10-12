#include"DebugController.h"
#include"GameObject.h"
#include"include/glfw3.h"
#include"Camera.h"
#include"GLFWController.h"
#include"ImGuiController.h"
#include"Sprite.h"

using namespace GLibrary;
using namespace std;

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

    OrthographicCamera camera(1.6f, 1.0f);

    Texture2D texture = Texture2D::ParseFile(texturePath);
    texture.Bind();

    Sprite sp(texture, 1446);
    Sprite sp2(texture, 1446);

    IndexBuffer ib;
    ib.SetData(indicies, sizeof(indicies), GL_STATIC_DRAW);

    ShaderProgram program = ShaderProgram::ParseFile(shaderPath);
    program.Link();
    program.Bind();

    program.SetUniform4f("u_Color", 1, 0, 1, 1);
    program.SetUniform1i("u_Texture", 0);
    program.SetUniformMat4f("u_modelMatrix", sp.ModelMatrix());
    program.SetUniformMat4f("u_viewMatrix", camera.ViewMatrix());
    program.SetUniformMat4f("u_projectionMatrix", camera.ProjectionMatrix());

    Renderer renderer;
    ImGuiController windowController;

    while (!glfwWindowShouldClose(window))
    {
        renderer.Clear();

        windowController.NewFrame();

        renderer.Draw(sp.VA(), ib, program);
        renderer.Draw(sp2.VA(), ib, program);

        windowController.ShowWindow();
       
        ImGuiController::Draw();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    ImGuiController::Shutdown();
    glfwTerminate();
    return 0;
}