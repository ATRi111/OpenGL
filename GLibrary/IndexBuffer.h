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
		IndexBuffer()
			:Buffer(), count(-1), size(-1), dataType(-1)
		{
			
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

		void SetData(const void* data, unsigned long size, unsigned int usage) override
		{
			SetData(data, size, usage, GL_UNSIGNED_INT);
		}
		void SetData(const void* data, unsigned long size, unsigned int usage, unsigned int dataType)
		{
			this->size = size;
			this->dataType = dataType;
			count = size / Translater::SizeOfGLenum(dataType);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, usage);
		}
	};
}