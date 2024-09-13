#pragma once
#include "GLAD/include/glad/glad.h"

namespace GLibrary
{
	class VertexArray
	{
	private:
		GLuint id;
	public:
		VertexArray()
		{
			glGenVertexArrays(1, &id);
			glBindVertexArray(id);
		}
		~VertexArray()
		{
			glDeleteVertexArrays(1, &id);
		}

		GLuint ID() const
		{
			return id;
		}

		void Bind() const
		{
			glBindVertexArray(id);
		}
		void Unbind() const
		{
			glBindVertexArray(0);
		}
	};
}