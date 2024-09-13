#pragma once
#include "Buffer.h"

namespace GLibrary
{
	class IndexBuffer : public Buffer
	{
	public:
		IndexBuffer(const void* data, GLsizeiptr size, GLenum usage)
			:Buffer(data, size, usage)
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, usage);
		}

		GLenum GetType() const override
		{
			return GL_ELEMENT_ARRAY_BUFFER;
		}
	};
}