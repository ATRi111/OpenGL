#pragma once
#include<iostream>
#include"GLAD/include/glad/glad.h"
#include"GLibrary/glm/glm.hpp"

namespace GLibrary
{
	class Translater
	{
	public:
		static void Print(glm::mat4 matrix, int width = 10)
		{
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					std::cout.width(width);
					std::cout << matrix[i][j];
				}
				std::cout << std::endl;
			}
			std::cout << std::endl;
		}

		template<typename T>
		static unsigned int TemplateToGLenum()
		{
			static_assert(0);
		}
		template<>
		static unsigned int TemplateToGLenum<char>()
		{
			return GL_BYTE;
		}
		template<>
		static unsigned int TemplateToGLenum<unsigned char>()
		{
			return GL_UNSIGNED_BYTE;
		}
		template<>
		static unsigned int TemplateToGLenum<short>()
		{
			return GL_SHORT;
		}
		template<>
		static unsigned int TemplateToGLenum<unsigned short>()
		{
			return GL_UNSIGNED_SHORT;
		}
		template<>
		static unsigned int TemplateToGLenum<int>()
		{
			return GL_INT;
		}
		template<>
		static unsigned int TemplateToGLenum<unsigned int>()
		{
			return GL_UNSIGNED_INT;
		}
		template<>
		static unsigned int TemplateToGLenum<float>()
		{
			return GL_FLOAT;
		}

		static unsigned long SizeOfGLenum(unsigned int type)
		{
			switch (type)
			{
			case GL_BYTE:
			case GL_UNSIGNED_BYTE:
				return sizeof(char);
			case GL_SHORT:
			case GL_UNSIGNED_SHORT:
				return sizeof(short);
			case GL_INT:
			case GL_UNSIGNED_INT:
				return sizeof(int);
			case GL_FLOAT:
				return sizeof(float);
			default:
				return 0;
			}
		}
	};
}