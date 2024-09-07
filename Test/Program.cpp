#include "GLAD/include/glad/glad.h"
#include "include/glfw3.h"
#include<iostream>

static GLuint CreateShader(const std::string& code, GLenum type)
{
    GLuint shader = glCreateShader(type);
    const char* code_ = code.c_str();
    glShaderSource(shader, 1, &code_, nullptr);
    glCompileShader(shader);

    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) 
    {
        GLchar infoLog[512];
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        std::cout << "[Shader Compilation Error]" << infoLog << std::endl;
    }
    return shader;
}

static GLuint CreateProgram(const std::string& vertexShaderCode, const std::string fragmentShaderCode)
{
    GLuint program = glCreateProgram();
    GLuint vertexShader = CreateShader(vertexShaderCode, GL_VERTEX_SHADER);
    GLuint fragmentShader = CreateShader(fragmentShaderCode, GL_FRAGMENT_SHADER);
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);
    glValidateProgram(program);

    GLint success;
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) 
    {
        GLchar infoLog[512];
        glGetProgramInfoLog(program, 512, nullptr, infoLog);
        std::cout << "[Program Linking Error]" << infoLog << std::endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    return program;
}

static void SetContext()
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

    std::string vertexShaderCode =
        "#version 330 core\n"
        "layout(location = 0) in vec4 position;"
        "void main()\n"
        "{\n"
        "   gl_Position = position;\n"
        "}\n";
    std::string fragmentShaderCode =
        "#version 330 core\n"
        "out vec4 color;"
        "void main()\n"
        "{\n"
        "   color = vec4(1,0.4,0.4,1);\n"
        "}\n";

    GLuint program = CreateProgram(vertexShaderCode, fragmentShaderCode);
    glUseProgram(program);
}

int main(void)
{
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

    SetContext();

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