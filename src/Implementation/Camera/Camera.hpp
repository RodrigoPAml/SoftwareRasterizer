#pragma once
#include <Rasterizer.hpp>

namespace Rasterizer
{
	/// <summary>
	/// Manage the camera movements in the 3d software rasterization proccess
	/// </summary>
	class Camera
	{
	private:
		Vec3<float> position;

		Vec3<float> front = { 0, 0, 1 };
		Vec3<float> up = { 0, 0, 0 };
		Vec3<float> right = { 0, 0, 0 };

		float pitch = 0, yaw = 0;
		float zNear = 1.0f, zFar = 100, fov = 90.0f, aspectRatio = 8.0f/6.0f;
	public:
		Camera();

		void SetFov(float fov);
		float GetFov() const;

		void SetAspectRatio(float aspectRatio);
		float GetAspectRatio() const;

		void SetZFar(float zfar);
		float GetZFar() const;

		void SetZNear(float znear);
		float GetZNear() const;

		void SetPitch(float pitch);
		float GetPitch() const;

		void SetYaw(float yaw);
		float GetYaw() const;

		void Translate(Vec3<float> delta);
		void TranslateFront(float speed);
		void TranslateRight(float speed);
		void TranslateUp(float speed);

		Vec3<float> GetFront() const;

		// Apply transformation to vertex
		void ApplyToVertex(Vec3<float>& vertex);
	private:
		void Update();
	};
}