#include"GameObject.h"
#include"GLibrary/Texture.h"
#include"GLibrary/VertexArray.h"
#include"GLibrary/VertexBuffer.h"

class Sprite : public GameObject
{
	static const int VertexCount = 4;

	float pixelPerUnit;
	glm::vec2 pivot;
	VertexBufferLayout layout;
	VertexArray va;
	VertexBuffer vb;
public:
	Sprite(const Texture2D& texture, float pixelPerUnit = 1000, glm::vec2 pivot = glm::vec2(0.5f, 0.5f))
		:GameObject(), pixelPerUnit(pixelPerUnit), pivot(pivot)
	{
		float w = texture.Width() / pixelPerUnit;
		float h = texture.Height() / pixelPerUnit;
		float l = -pivot.x * w;
		float r = l + w;
		float b = -pivot.y * h;
		float t = b + h;
		std::cout << l << " " << r << " " << b << " " << t << std::endl;
		float vertices[] =
		{
			l,b,0, 0,0,
			r,b,0, 1,0,
			r,t,0, 1,1,
			l,t,0, 0,1,
		};

		layout.AddProperty<float>(0, 3);	//position
		layout.AddProperty<float>(1, 2);	//uv
		vb.SetData(vertices, VertexCount * layout.Stride(), GL_STATIC_DRAW);
		va.SetLayout(layout);
	}
	~Sprite()
	{

	}

	const VertexArray& VA() const { return va; }
	const VertexBuffer& VB() const { return vb; }
	const VertexBufferLayout& Layout() const { return layout; }
};