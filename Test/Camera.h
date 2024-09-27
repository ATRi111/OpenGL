#pragma once
#include"GLibrary/glm/glm.hpp"
#include"GLibrary/glm/ext/matrix_clip_space.hpp"
#include"GLibrary/glm/ext/matrix_transform.hpp"
#include"GLibrary/ImGui/imgui_impl_opengl3.h"

class Camera
{
protected:
	glm::mat4 viewMatrix;
	glm::mat4 projectionMatrix;
	glm::mat4 viewportMatrix;
	glm::vec3 position;

	virtual void UpdateViewMatrix() = 0;
	virtual void UpdateProjMatrix() = 0;
public:
	Camera()
	{
		position = glm::vec3(0, 0, -1.0f);
		viewMatrix = glm::mat4(1);
		projectionMatrix = glm::mat4(1);
		viewportMatrix = glm::mat4(1);
	}
	virtual ~Camera()
	{

	}

	virtual const glm::mat4& ViewMatrix() const { return viewMatrix; }
	virtual	const glm::mat4& ProjectionMatrix() const { return projectionMatrix; }
	virtual	glm::vec3 Position() const { return position; }
	virtual void SetPosition(glm::vec3 position)
	{
		this->position = position;
		UpdateViewMatrix();
		UpdateProjMatrix();
	}
};

class OrthographicCamera : public Camera
{
protected:
	float width, height;
	float left, right, bottom, top;
	float near, far;
	float zNear, zFar;
	void UpdateViewMatrix() override
	{
		glm::mat4 T = glm::translate(glm::mat4(1), -position);
		viewMatrix = T;
	}
	virtual void UpdateProjMatrix() override
	{
		std::cout << left << "|" << right << "|" << bottom << "|" << top << "|" << zNear << "|" << zFar << std::endl;
		projectionMatrix = glm::ortho(left, right, bottom, top, zNear, zFar);
	}
public:
	OrthographicCamera(float width, float height, float near = 0, float far = 100)
		:Camera(), width(width), height(height), near(near), far(far)
	{
		left = position.x - 0.5f * width;
		right = left + width;
		bottom = position.y - 0.5f * height;
		top = bottom + height;
		zNear = position.z + near;
		zFar = position.z + far;
		UpdateViewMatrix();
		UpdateProjMatrix();
	}
	~OrthographicCamera()
	{

	}
	float Width() const { return width; }
	float Height() const { return height; }
	float Near() const { return near; }
	float Far() const { return far; }
	void SetWidth(float width)
	{
		this->width = width;
		left = position.x - 0.5f * width;
		right = left + width;
		UpdateViewMatrix();
	}
	void SetHeight(float height)
	{
		this->height = height;
		bottom = position.y - 0.5f * height;
		top = bottom + height;
		UpdateViewMatrix();
	}
	void SetNear(float near)
	{
		this->near = near;
		zNear = position.z + near;
		UpdateViewMatrix();
	}
	void SetFar(float far)
	{
		this->far = far;
		zFar = position.z + far;
		UpdateViewMatrix();
	}
};