#pragma once
#include "GLAD/include/glad/glad.h"

namespace GLibrary
{
	class BufferGenerator
	{
	public:
		static GLuint GenVBO(void* vertices, GLsizeiptr size, GLenum usage)
		{
			GLuint VBO;
			glGenBuffers(1, &VBO);
			glBindBuffer(GL_ARRAY_BUFFER, VBO);
			glBufferData(GL_ARRAY_BUFFER, size, vertices, usage);
			return VBO;
		}

		static GLuint GenVAO()
		{
			GLuint VAO;
			glGenVertexArrays(1, &VAO);
			glBindVertexArray(VAO);
			return VAO;
		}

		static GLuint GenIBO(GLuint* indices, GLsizeiptr size, GLenum usage)
		{
			GLuint IBO;
			glGenBuffers(1, &IBO);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, usage);
			return IBO;
		}
	};
}