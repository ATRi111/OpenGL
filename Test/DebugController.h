#pragma once
#include"GLibrary/GLibrary.h"

static void APIENTRY DebugCallback(
    unsigned int source,
    unsigned int type,
    unsigned int id,
    unsigned int severity,
    GLsizei length,
    const GLchar* message,
    const void* userParam)
{
    switch (severity)
    {
    case GL_DEBUG_SEVERITY_NOTIFICATION:
        break;
    case GL_DEBUG_SEVERITY_LOW:
    case GL_DEBUG_SEVERITY_MEDIUM:
    case GL_DEBUG_SEVERITY_HIGH:
        std::cout << "[Warning]" << severity << message << std::endl;
    default:
        break;
    }
}

class DebugController
{
public:
	DebugController()
	{
        glEnable(GL_DEBUG_OUTPUT);
        glDebugMessageCallback(DebugCallback, nullptr);
	}
    ~DebugController()
    {
        glDisable(GL_DEBUG_OUTPUT);
    }
};