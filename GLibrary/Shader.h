#pragma once
#include "GLAD/include/glad/glad.h"
#include <iostream>
#include <string>
#include <vector>
#include<fstream>
#include<string>
#include<sstream>
#include<unordered_map>

namespace GLibrary
{
	class Shader
	{
		unsigned int id;
	public:

		Shader(std::string code, int type)
		{
            id = glCreateShader(type);
            const char* code_ = code.c_str();
            glShaderSource(id, 1, &code_, nullptr);
            glCompileShader(id);

            int success;
            glGetShaderiv(id, GL_COMPILE_STATUS, &success);
            if (!success)
            {
                char infoLog[512];
                glGetShaderInfoLog(id, 512, nullptr, infoLog);
                std::cout << "[Shader Compilation Error]" << infoLog << std::endl;
            }
		}
        ~Shader()
        {
            glDeleteShader(id);
        }

        unsigned int ID() const
        {
            return id;
        }
	};

    class ShaderProgram
    {
        unsigned int id;
        std::vector<Shader> shaders;
        mutable std::unordered_map<std::string, int> locaionCache;
    public:
        static ShaderProgram Parse(const std::string& filepath);
        ShaderProgram()
        {
            id = glCreateProgram();
        }
        ~ShaderProgram()
        {

        }

        void AttachShader(Shader shader)
        {
            shaders.push_back(shader);
            glAttachShader(id, shader.ID());
        }

        int Link() const
        {
            glLinkProgram(id);
            glValidateProgram(id);

            int success;
            glGetProgramiv(id, GL_LINK_STATUS, &success);
            if (!success)
            {
                char infoLog[512];
                glGetProgramInfoLog(id, 512, nullptr, infoLog);
                std::cout << "[Program Linking Error]" << infoLog << std::endl;
            }
            return success;
        }

        void Bind() const
        {
            glUseProgram(id);
        }
        void Unbind() const
        {
            glUseProgram(0);
        }

        int GetUniformLocation(const char* name) const
        {
            auto it = locaionCache.find(name);
            if (it != locaionCache.end())
            {
                return it->second;
            }
            int location = glGetUniformLocation(id, name);
            locaionCache.emplace(name, location);
            return location;
        }

        void SetUniform1f(const char* name, float f) const
        {
            Bind();
            int location = GetUniformLocation(name);
            glUniform1f(location, f);
        }
        void SetUniform4f(const char* name, float f1, float f2, float f3, float f4) const
        {
            Bind(); 
            int location = GetUniformLocation(name);
            glUniform4f(location, f1, f2, f3, f4);
        }

        unsigned int ID() const
        {
            return id;
        }
        const std::vector<Shader>& Shaders() const
        {
            return shaders;
        }
    };

    ShaderProgram ShaderProgram::Parse(const std::string& filepath)
    {
        std::string line;
        std::ifstream stream(filepath);
        std::stringstream currentCode;
        unsigned int currentType = GL_NONE;
        ShaderProgram ret;

        while (getline(stream, line))
        {
            if (line.find("#shader") != std::string::npos)
            {
                if (currentType != GL_NONE)
                {
                    ret.AttachShader(Shader(currentCode.str(), currentType));
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
            ret.AttachShader(Shader(currentCode.str(), currentType));
            currentCode.clear();
        }
        return ret;
    }
}
