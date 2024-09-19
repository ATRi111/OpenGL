#pragma once
#include"Buffer.h"
#include"General.h"

namespace GLibrary
{
	class IndexBuffer : public Buffer
	{
		unsigned int dataType;
		unsigned int count;
		unsigned int size;
	public:
		IndexBuffer(const void* data, unsigned long size, unsigned int usage, unsigned int dataType = GL_UNSIGNED_INT)
			:Buffer(data, size, usage), size(size), count(size / Translater::SizeOfGLenum(dataType)), dataType(dataType)
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, usage);
		}

		unsigned int BufferType() const override
		{
			return GL_ELEMENT_ARRAY_BUFFER;
		}
		unsigned int DataType() const
		{
			return dataType;
		}
		unsigned long Count() const
		{
			return count;
		}
		unsigned long Size() const
		{
			return size;
		}
	};
}