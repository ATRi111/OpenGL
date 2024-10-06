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
	virtual void UpdateProjectionMatrix() = 0;
public:
	Camera()
		:position(0, 0, 10), viewMatrix(1), projectionMatrix(1), viewportMatrix(1)
	{

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
		UpdateProjectionMatrix();
	}
};

class OrthographicCamera : public Camera
{
protected:
	float width, height;
	float near, far;
	void UpdateViewMatrix() override
	{
		glm::mat4 T = glm::translate(glm::mat4(1), -position);
		viewMatrix = T;
	}
	virtual void UpdateProjectionMatrix() override
	{
		projectionMatrix = glm::ortho(-0.5f * width, 0.5f * width, -0.5f * height, 0.5f * height, near, far);
	}
public:
	OrthographicCamera(float width, float height, float near = 1, float far = 100)
		:Camera(), width(width), height(height), near(near), far(far)
	{
		UpdateViewMatrix();
		UpdateProjectionMatrix();
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
		UpdateViewMatrix();
	}
	void SetHeight(float height)
	{
		this->height = height;
		UpdateViewMatrix();
	}
	void SetNear(float near)
	{
		this->near = near;
		UpdateViewMatrix();
	}
	void SetFar(float far)
	{
		this->far = far;
		UpdateViewMatrix();
	}
};