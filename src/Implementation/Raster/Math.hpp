#pragma once
#include <Rasterizer.hpp>

#define PI 3.14159265358979323846

namespace Rasterizer {
namespace Math {
	
	static Vec3<float> Cross(const Vec3<float>& p1, const Vec3<float>& p2)
	{
		return { p1.y * p2.z - p1.z * p2.y,  p1.z * p2.x - p1.x * p2.z, p1.x * p2.y - p1.y * p2.x };
	}

	static float Dot(const Vec3<float>& p1, const Vec3<float>& p2)
	{
		return p1.x * p2.x + p1.y * p2.y + p1.z * p2.z;
	}

	static float Mag(const Vec3<float>& p)
	{
		return std::sqrt(p.x * p.x + p.y * p.y + p.z * p.z);
	}

	static Vec3<float> Normalize(const Vec3<float>& p)
	{
		float mag = Mag(p);

		return { p.x / mag, p.y / mag, p.z / mag };
	}

	static float Radians(const float degrees)
	{
		return degrees * (PI / 180);
	}

	static Vec3<float> RotateX(const Vec3<float>& p ,float angle)
	{
		float radians = Radians(angle);

		float cosTheta = std::cos(radians); 
		float sinTheta = std::sin(radians);

		float rotY = p.y * cosTheta - p.z * sinTheta;
		float rotZ = p.y * sinTheta + p.z * cosTheta;

		return { p.x, rotY, rotZ };
	}

	static Vec3<float> RotateY(const Vec3<float>& p, float angle)
	{
		float radians = Radians(angle);

		float cosTheta = std::cos(radians); 
		float sinTheta = std::sin(radians);

		float rotZ = p.z * cosTheta - p.x * sinTheta;
		float rotX = p.z * sinTheta + p.x * cosTheta;

		return { rotX, p.y, rotZ };
	}

	static Vec3<float> RotateZ(const Vec3<float>& p, float angle)
	{
		float radians = Radians(angle);

		float cosTheta = std::cos(radians); 
		float sinTheta = std::sin(radians); 

		float rotX = p.x * cosTheta - p.y * sinTheta;
		float rotY = p.x * sinTheta + p.y * cosTheta;

		return { rotX, rotY, p.z };
	}

	static float Edge(const Vec3<float>& p1, const Vec3<float>& p2, const Vec2<int>& p3)
	{
		return (p3.x - p1.x) * (p2.y - p1.y) - (p3.y - p1.y) * (p2.x - p1.x);
	}

	static float Edge(const Vec3<float>& p1, const Vec3<float>& p2, const Vec3<float>& p3)
	{
		return (p3.x - p1.x) * (p2.y - p1.y) - (p3.y - p1.y) * (p2.x - p1.x);
	}

	static Vec3<float> Cast(const Vec3<int>& value)
	{
		return { (float)value.x, (float)value.y, (float)value.z };
	}

	static Vec2<float> Cast(const Vec2<int>& value)
	{
		return { (float)value.x, (float)value.y };
	}

	static Vec3<int> Cast(const Vec3<float>& value)
	{
		return { (int)value.x, (int)value.y, (int)value.z };
	}

	static Vec2<int> Cast(const Vec2<float>& value)
	{
		return { (int)value.x, (int)value.y };
	}
}}