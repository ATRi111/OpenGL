#pragma once
#include"GLAD/include/glad/glad.h"
#include"General.h"
#include<vector>

namespace GLibrary
{
	struct VertexPropertyLayout
	{
		unsigned int index;
		unsigned int type;
		unsigned int count;
		unsigned char normalized;

		VertexPropertyLayout(unsigned int index, unsigned int type, unsigned int count, unsigned char normalized)
			:index(index), type(type), count(count), normalized(normalized)
		{

		}

		unsigned long Size() const
		{
			return Translater::SizeOfGLenum(type) * count;
		}
	};

	class VertexBufferLayout
	{
		std::vector<VertexPropertyLayout> properties;
		unsigned int stride;
	public:
		VertexBufferLayout()
			:stride(0)
		{

		}
		~VertexBufferLayout()
		{

		}

		unsigned int Stride() const
		{
			return stride;
		}
		const std::vector<VertexPropertyLayout>& Properties() const
		{
			return properties;
		}

		template<typename T>
		void AddProperty(unsigned int index, unsigned int count, unsigned char normalized = false)
		{
			properties.emplace_back(index, Translater::TemplateToGLenum<T>(), count, normalized);
			stride += count * sizeof(T);
		}
	};
}