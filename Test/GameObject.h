#pragma once
#include"GLibrary/General.h"
#include"GLibrary/glm/glm.hpp"
#include"GLibrary/glm/ext/matrix_clip_space.hpp"
#include"GLibrary/glm/ext/matrix_transform.hpp"
#include"GLibrary/ImGui/imgui_impl_opengl3.h"
using namespace GLibrary;

class GameObject
{
protected:
	glm::vec3 position;
	glm::vec3 rotation;	//eulerAngles in degree
	glm::vec3 scale;
	glm::mat4 T, R, S;
	glm::mat4 modelMatrix;
	void UpdateModelMatrix()
	{
		modelMatrix = S * R * T;
	}
public:
	GameObject()
		:position(0, 0, 0), rotation(0, 0, 0), scale(1, 1, 1), T(1), R(1), S(1), modelMatrix(1)
	{

	}
	~GameObject()
	{

	}

	glm::vec3 Position() const { return position; }
	glm::vec3 Rotation() const { return rotation; }
	glm::vec3 Scale() const { return scale; }
	glm::mat4 ModelMatrix() const { return modelMatrix; }

	void SetPosition(glm::vec3 position)
	{
		this->position = position;
		T = glm::translate(glm::mat4(1), position);
		UpdateModelMatrix();
	}
	void SetRotation(glm::vec3 rotation)
	{
		this->rotation = rotation;
		R = glm::rotate(glm::mat4(1), glm::radians(rotation.x), glm::vec3(1, 0, 0));
		R = glm::rotate(R, glm::radians(rotation.y), glm::vec3(0, 1, 0));
		R = glm::rotate(R, glm::radians(rotation.z), glm::vec3(0, 0, 1));
		UpdateModelMatrix();
	}
	void SetScale(glm::vec3 scale)
	{
		this->scale = scale;
		S = glm::scale(glm::mat4(1), scale);
		UpdateModelMatrix();
	}
};