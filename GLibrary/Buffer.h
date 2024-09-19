#pragma once
#include "GLAD/include/glad/glad.h"

namespace GLibrary
{
	class Buffer
	{
	protected:
		unsigned int id;
	public:
		Buffer(const void* data, unsigned long size, unsigned int usage)
		{
			glGenBuffers(1, &id);
		}
		virtual ~Buffer()
		{
			glDeleteBuffers(1, &id);
		}

		virtual unsigned int BufferType() const = 0;

		unsigned int ID() const
		{
			return id;
		}

		virtual void Bind() const
		{
			glBindBuffer(BufferType(), id);
		}
		virtual void Unbind() const
		{
			glBindBuffer(BufferType(), 0);
		}
	};
}
