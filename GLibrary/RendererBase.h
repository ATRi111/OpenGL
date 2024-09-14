#pragma once
#include"VertexBuffer.h"
#include"IndexBuffer.h"
#include"VertexArray.h"

namespace GLibrary
{
	class RendererBase
	{
	protected:
		unsigned int id;
	public:
		VertexBuffer* VBO;
		IndexBuffer* IBO;
		VertexArray* VAO;

		RendererBase()
			:VBO(nullptr), IBO(nullptr), VAO(nullptr)
		{
			id = 0;
		}
		virtual ~RendererBase()
		{

		}

		virtual void Bind()
		{
			
		}
		virtual void Unbind()
		{
			
		}
	};
}