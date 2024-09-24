#include"GLibrary/GLibrary.h"
#include"include/glfw3.h"
#include"GLibrary/glm/glm.hpp"
#include"GLibrary/glm/ext/matrix_clip_space.hpp"
#include"GLibrary/glm/ext/matrix_transform.hpp"

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

    while (!glfwWindowShouldClose(window))
    {
        renderer.Clear();
        renderer.Draw(va, ib, program);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}