#include "GLibrary/GLibrary.h"
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

    VertexArray VAO;
    VertexBuffer VBO(positions, sizeof(positions), GL_STATIC_DRAW);
    IndexBuffer IBO(indicies, sizeof(indicies), GL_STATIC_DRAW);
    
    VertexBufferLayout layout;
    layout.AddProperty<float>(0, 2);
    VAO.SetLayout(layout);

    ShaderProgram program = ShaderProgram::Parse(path);
    program.Link();
    program.Bind();

    program.SetUniform4f("u_Color", 1, 0, 1, 1);

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