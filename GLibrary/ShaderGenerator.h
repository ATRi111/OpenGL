#pragma once
#include "GLAD/include/glad/glad.h"
#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<vector>

namespace GLibrary
{
    struct ShaderSource
    {
        std::string code;
        unsigned int type;

        ShaderSource(std::string sourceCode, unsigned int type)
        {
            this->code = sourceCode;
            this->type = type;
        }
    };

    static void operator<<(std::ostream& stream, const ShaderSource& source)
    {
        stream << "shader:" << source.type << std::endl;
        stream << source.code;
    }

    class ShaderGenerator
    {
    public:
        static unsigned int GenShader(const std::string& code, unsigned int type)
        {
            unsigned int shader = glCreateShader(type);
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
                return -1;
            }
            return shader;
        }

        static unsigned int GenProgram(std::vector<ShaderSource> shaders)
        {
            unsigned int program = glCreateProgram();
            for (int i = 0; i < shaders.size(); i++)
            {
                unsigned int shader = GenShader(shaders[i].code, shaders[i].type);
                if (shader != -1)
                {
                    glAttachShader(program, shader);
                    glDeleteShader(shader);
                }
            }

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
            return program;
        }

        static std::vector<ShaderSource> ParseFile(const std::string& filepath)
        {
            std::string line;
            std::ifstream stream(filepath);
            std::stringstream currentCode;
            unsigned int currentType = GL_NONE;
            std::vector<ShaderSource> ret;

            while (getline(stream, line))
            {
                if (line.find("#shader") != std::string::npos)
                {
                    if (currentType != GL_NONE)
                    {
                        ret.emplace_back(currentCode.str(), currentType);
                        currentCode.str("");
                    }
                    if (line.find("vertex") != std::string::npos)
                        currentType = GL_VERTEX_SHADER;
                    else if (line.find("fragment") != std::string::npos)
                        currentType = GL_FRAGMENT_SHADER;
                }
                else
                    currentCode << line << '\n';
            }
            if (currentCode.str().size() > 0 && currentType != GL_NONE)
            {
                ret.emplace_back(currentCode.str(), currentType);
                currentCode.clear();
            }
            return ret;
        };
    };
}