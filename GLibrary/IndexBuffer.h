#pragma once
#include "Buffer.h"

namespace GLibrary
{
	class IndexBuffer : public Buffer
	{
	public:
		IndexBuffer(const void* data, unsigned long size, unsigned int usage)
			:Buffer(data, size, usage)
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, usage);
		}

		unsigned int GetType() const override
		{
			return GL_ELEMENT_ARRAY_BUFFER;
		}
	};
}