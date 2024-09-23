#pragma once
#include"GLAD/include/glad/glad.h"
#include"VertexBufferLayout.h"

namespace GLibrary
{
	class VertexArray
	{
	private:
		unsigned int id;
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

		unsigned int ID() const
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

		void SetLayout(const VertexBufferLayout& layout) const
		{
			Bind();
			const std::vector<VertexPropertyLayout>& properties = layout.Properties();
			unsigned long offset = 0;
			for (int i = 0; i < properties.size(); i++)
			{
				const VertexPropertyLayout& p = properties[i];
				glEnableVertexAttribArray(p.index);
				glVertexAttribPointer(p.index, p.count, p.type, p.normalized, layout.Stride(), reinterpret_cast<const void*>(offset));
				offset += p.Size();
			}
		}
	};
}