#pragma once
#include "GLAD/include/glad/glad.h"

namespace GLibrary
{
	class Buffer
	{
	protected:
		GLuint id;
	public:
		Buffer(const void* data, GLsizeiptr size, GLenum usage)
		{
			glGenBuffers(1, &id);
		}
		virtual ~Buffer()
		{
			glDeleteBuffers(1, &id);
		}

		virtual GLenum GetType() const
		{
			return 0;
		}
		GLuint ID() const
		{
			return id;
		}

		virtual void Bind() const
		{
			glBindBuffer(GetType(), id);
		}
		virtual void Unbind() const
		{
			glBindBuffer(GetType(), 0);
		}
	};
}
