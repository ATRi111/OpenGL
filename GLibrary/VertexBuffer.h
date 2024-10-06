#pragma once
#include "Buffer.h"

namespace GLibrary
{
	class VertexBuffer : public Buffer
	{
	public:
		VertexBuffer()
			:Buffer()
		{

		}
		unsigned int BufferType() const override
		{
			return GL_ARRAY_BUFFER;
		}

		void SetData(const void* data, unsigned long size, unsigned int usage) override
		{
			glBindBuffer(GL_ARRAY_BUFFER, id);
			glBufferData(GL_ARRAY_BUFFER, size, data, usage);
		}
	};
}