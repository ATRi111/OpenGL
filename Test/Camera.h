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
	glm::vec3 rotation;
	float near, far;

	void UpdateViewMatrix()
	{
		glm::mat4 M(1);

		M = glm::rotate(M, glm::radians(rotation.x), glm::vec3(1, 0, 0));
		M = glm::rotate(M, glm::radians(rotation.y), glm::vec3(0, 1, 0));
		M = glm::rotate(M, glm::radians(rotation.z), glm::vec3(0, 0, 1));
		M = glm::translate(M, -position);
		viewMatrix = M;
	}
	virtual void UpdateProjectionMatrix() = 0;
public:
	Camera()
		:position(0, 0, 0), rotation(0, 0, 0), near(0), far(1000)
	{
		UpdateViewMatrix();
		//此处不可调用虚函数
	}
	virtual ~Camera()
	{

	}

	virtual const glm::mat4& ViewMatrix() const { return viewMatrix; }
	virtual	const glm::mat4& ProjectionMatrix() const { return projectionMatrix; }

	virtual	glm::vec3 Position() const { return position; }
	virtual void SetPosition(glm::vec3 position)
	{
		if (this->position != position)
		{
			this->position = position;
			UpdateViewMatrix();
			UpdateProjectionMatrix();
		}
	}

	virtual	glm::vec3 Rotation() const { return rotation; }
	virtual void Rotate(glm::vec3 deltaAngle)
	{
		rotation = rotation + deltaAngle;
		UpdateViewMatrix();
		UpdateProjectionMatrix();
	}

	float Near() const { return near; }
	void SetNear(float near)
	{
		this->near = near;
		UpdateViewMatrix();
	}

	float Far() const { return far; }
	void SetFar(float far)
	{
		this->far = far;
		UpdateViewMatrix();
	}
};

class OrthographicCamera : public Camera
{
protected:
	float width, height;

	virtual void UpdateProjectionMatrix() override
	{
		projectionMatrix = glm::ortho(-0.5f * width, 0.5f * width, -0.5f * height, 0.5f * height, near, far);
	}
public:
	OrthographicCamera()
		:Camera(), width(16), height(9)
	{
		projectionMatrix = glm::ortho(-0.5f * width, 0.5f * width, -0.5f * height, 0.5f * height, near, far);
	}
	~OrthographicCamera()
	{

	}
	float Width() const { return width; }
	float Height() const { return height; }
	
	void SetWidth(float width)
	{
		if (this->width != width)
		{
			this->width = width;
			UpdateProjectionMatrix();
		}
	}
	void SetHeight(float height)
	{
		if (this->height != height)
		{
			this->height = height;
			UpdateProjectionMatrix();
		}
	}
};

class PerspectiveCamera : Camera
{
protected:
	float fov;		//视角场
	float aspect;	//宽高比

	virtual void UpdateProjectionMatrix() override
	{
		projectionMatrix = glm::perspective(glm::radians(fov), aspect, near, far);
	}

public:
	PerspectiveCamera()
		: Camera(), fov(60), aspect(1.6f)
	{
		projectionMatrix = glm::perspective(glm::radians(fov), aspect, near, far);
	}

	float Fov() const { return fov; }
	void SetFov(float fov)
	{
		if (this->fov != fov)
		{
			this->fov = fov;
			UpdateProjectionMatrix();
		}
	}

	float Aspect() const { return aspect; }
	void SetAspect(float aspect)
	{
		if (this->aspect != aspect)
		{
			this->aspect = aspect;
			UpdateProjectionMatrix();
		}
	}
};