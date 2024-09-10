#include "GLAD/include/glad/glad.h"
#include "include/glfw3.h"
#include<iostream>
#include"ShaderGenerator.h"


static void SetContext(const std::string& shaderPath)
{
    float positions[] = {
        -0.5f,-0.5f,
        0.5f,-0.5f,
        0.0f,0.5f
    };

    GLuint VBO, VAO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6, positions, GL_STATIC_DRAW);

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

    std::vector<ShaderSource> shaders = ShaderGenerator::ParseFile(shaderPath);
    GLuint program = ShaderGenerator::CreateProgram(shaders);
    glUseProgram(program);
}

int main(int argc, char* argv[])
{
    std::string path = argv[0];
    path = path.substr(0, path.find("\\OpenGL\\")) + "\\OpenGL\\OpenGL\\Test\\TestShader.shader";
    std::cout << path << std::endl;
    
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

    SetContext(path);

    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}