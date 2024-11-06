#include"GameObject.h"
#include"GLibrary/IndexBuffer.h"
#include"GLibrary/Texture.h"
#include"GLibrary/VertexArray.h"
#include"GLibrary/VertexBuffer.h"

class SpriteBase
{
protected:
	static const int VertexCount = 4;
	float w, h;
	float pixelPerUnit;
	glm::vec2 pivot;
	VertexBufferLayout layout;
	VertexArray va;
	VertexBuffer vb;
	IndexBuffer ib;
public:
	SpriteBase(const Texture2D& texture, float pixelPerUnit = 1000, glm::vec2 pivot = glm::vec2(0.5f, 0.5f), unsigned int usage = GL_STATIC_DRAW)
		:pixelPerUnit(pixelPerUnit), pivot(pivot)
	{
		w = texture.Width() / pixelPerUnit;
		h = texture.Height() / pixelPerUnit;
	}
	virtual ~SpriteBase()
	{

	}

	const VertexArray& VA() const { return va; }
	const VertexBuffer& VB() const { return vb; }
	const IndexBuffer& IB() const { return ib; }
	const VertexBufferLayout& Layout() const { return layout; }
};

class DefaultSprite : public SpriteBase
{
public:
	DefaultSprite(const Texture2D& texture, float pixelPerUnit = 1000, glm::vec2 pivot = glm::vec2(0.5f, 0.5f), unsigned int usage = GL_STATIC_DRAW)
		:SpriteBase(texture, pixelPerUnit, pivot, usage)
	{
		float l = -pivot.x * w;
		float r = l + w;
		float b = -pivot.y * h;
		float t = b + h;

		float vertices[] =
		{
			l,b,0, 0,0,
			r,b,0, 1,0,
			r,t,0, 1,1,
			l,t,0, 0,1,
		};

		layout.AddProperty<float>(0, 3);	//position
		layout.AddProperty<float>(1, 2);	//uv
		vb.SetData(vertices, VertexCount * layout.Stride(), usage);
		va.SetLayout(layout);

		unsigned int indicies[] =
		{
			0,1,2,
			2,3,0,
		};
		ib.SetData(indicies, sizeof(indicies), usage);
	}
};