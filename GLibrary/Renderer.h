#pragma once
#include"Shader.h"
#include"VertexBuffer.h"
#include"IndexBuffer.h"
#include"VertexArray.h"

namespace GLibrary
{
	class Renderer
	{
	public:
		Renderer()
		{
		}
		~Renderer()
		{
		}
		void Clear()
		{
			glClear(GL_COLOR_BUFFER_BIT);
		}
		void Draw(const VertexArray& va, const IndexBuffer& ib, const ShaderProgram& program)
		{
			va.Bind();
			ib.Bind();
			program.Bind();
			glDrawElements(GL_TRIANGLES, ib.Count(), ib.DataType(), 0);
		}
	};
}