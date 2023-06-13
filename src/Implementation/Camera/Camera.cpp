 #include <Rasterizer.hpp>
#include "Camera.hpp"

namespace Rasterizer
{
	Camera::Camera()
	{
		this->position = { 0.0f, 0.0f, 0.0f };
		this->Update();
	}

	void Camera::SetFov(float fov)
	{
		this->fov = fov;
	}

	float Camera::GetFov() const
	{
		return this->fov;
	}

	void Camera::SetAspectRatio(float aspectRatio)
	{
		this->aspectRatio = aspectRatio;
	}

	float Camera::GetAspectRatio() const
	{
		return this->aspectRatio;
	}
	
	void Camera::SetZFar(float zfar)
	{
		this->zFar = zfar;
	}

	float Camera::GetZFar() const
	{
		return this->zFar;
	}

	void Camera::SetZNear(float znear)
	{
		this->zNear = znear;
	}

	float Camera::GetZNear() const
	{
		return this->zNear;
	}

	void Camera::SetPitch(float pitch)
	{
		this->pitch = pitch;
		this->Update();
	}

	float Camera::GetPitch() const
	{
		return this->pitch;
	}

	void Camera::SetYaw(float yaw)
	{
		this->yaw = yaw;
		this->Update();
	}

	float Camera::GetYaw() const
	{
		return this->yaw;
	}

	void Camera::Translate(Vec3<float> delta)
	{
		this->position = this->position + delta;
	}

	void Camera::TranslateFront(float speed)
	{
		this->position = this->position + (this->front * speed);
	}

	void Camera::TranslateRight(float speed)
	{
		this->position = this->position + (this->right * speed);
	}

	void Camera::TranslateUp(float speed)
	{
		this->position = this->position + (this->up * speed);
	}

	Vec3<float> Camera::GetFront() const
	{
		return this->front;
	}
	
	void Camera::ApplyToVertex(Vec3<float>& vertex)
	{
		vertex = vertex - this->position;

		vertex = Math::RotateY(vertex, -this->yaw);
		vertex = Math::RotateX(vertex, this->pitch);
	}

	void Camera::Update()
	{
		if (this->pitch > 89.0f)
			this->pitch = 89.0f;
		else if (this->pitch < -89.0f)
			this->pitch = -89.0f;

		const Vec3<float> front(
			sin(Math::Radians(this->yaw)) * cos(Math::Radians(this->pitch)),
			sin(Math::Radians(this->pitch)),
			cos(Math::Radians(this->pitch)) * cos(Math::Radians(this->yaw))
		);

		this->front = Math::Normalize(front);
		this->right = Math::Normalize(Math::Cross(this->front, { 0.0f, 1.0f, 0.0f }));
		this->up = Math::Normalize(Math::Cross(this->right, this->front));
	}
}