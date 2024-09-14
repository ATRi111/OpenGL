#pragma once
#include "Buffer.h"

namespace GLibrary
{
	class VertexBuffer : public Buffer
	{
	public:
		VertexBuffer(const void* data, unsigned long size, unsigned int usage)
			:Buffer(data, size, usage)
		{
			glBindBuffer(GL_ARRAY_BUFFER, id);
			glBufferData(GL_ARRAY_BUFFER, size, data, usage);
		}

		unsigned int GetType() const override
		{
			return GL_ARRAY_BUFFER;
		}
	};
}