#pragma once
#include"GLAD/include/glad/glad.h"
#include"stb_image.h"
#include <string>

namespace GLibrary
{
	class Texture2D
	{
		unsigned int id;
		unsigned char* buffer;
		unsigned int width, height, bytePerPixel;
	public:
		static Texture2D ParseFile(const std::string& filepath);
		Texture2D(unsigned int width, unsigned int height, unsigned int bytePerPixel, unsigned char* buffer)
			:width(width), height(height), bytePerPixel(bytePerPixel), buffer(buffer)
		{
			glGenTextures(1, &id);
			glBindTexture(GL_TEXTURE_2D, id);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, buffer);
		}
		~Texture2D()
		{
			if (buffer)
				free(buffer);
			glDeleteTextures(1, &id);
		}

		void Bind(unsigned int slot = 0) const
		{
			glActiveTexture(slot);
			glBindTexture(GL_TEXTURE_2D, id);
		}
		void UnBind() const
		{
			glBindTexture(GL_TEXTURE_2D, 0);
		}

		unsigned int ID() const
		{
			return id;
		}
		unsigned int Width() const
		{
			return width;
		}
		unsigned int Height() const
		{
			return height;
		}
	};

	inline Texture2D Texture2D::ParseFile(const std::string& filepath)
	{
		stbi_set_flip_vertically_on_load(1);	//从底部开始扫描图像
		int width, height, bytePerPixel;
		unsigned char* buffer = stbi_load(filepath.c_str(), &width, &height, &bytePerPixel, 4);
		return Texture2D(width, height, bytePerPixel, buffer);
	}
}