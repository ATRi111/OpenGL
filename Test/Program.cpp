#include"GLibrary/ShaderGenerator.h"
#include"GLibrary/BufferGenerator.h"
#include "include/glfw3.h"
using namespace GLibrary;
using namespace std;

float positions[] = 
{
    -0.5f,-0.5f,
    0.5f,-0.5f,
    0.5f,0.5f,
    -0.5f,0.5f
};

GLuint indicies[] =
{
    0,1,2,
    2,3,0,
};

static void APIENTRY DebugCallback(
    GLenum source,
    GLenum type,
    GLuint id,
    GLenum severity,
    GLsizei length,
    const GLchar* message,
    const void* userParam) 
{
    std::cout << "GLDebug: " << message << std::endl;
}

static void SetContext(const string& shaderPath)
{
    GLuint VBO = BufferGenerator::GenVBO(positions, sizeof(positions), GL_STATIC_DRAW);
    GLuint VAO = BufferGenerator::GenVAO();
    GLuint IBO = BufferGenerator::GenIBO(indicies, sizeof(indicies), GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

    vector<ShaderSource> shaders = ShaderGenerator::ParseFile(shaderPath);
    GLuint program = ShaderGenerator::GenProgram(shaders);
    glUseProgram(program);
}

int main(int argc, char* argv[])
{
    string path = argv[0];
    path = path.substr(0, path.find("\\OpenGL\\")) + "\\OpenGL\\OpenGL\\Test\\TestShader.shader";

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

    SetContext(path);

    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glDrawElements(GL_TRIANGLES, sizeof(indicies) / sizeof(indicies[0]), GL_UNSIGNED_INT, 0);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}