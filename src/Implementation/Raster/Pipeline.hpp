#pragma once
#include <Rasterizer.hpp>

namespace Rasterizer {
namespace Pipeline {
		
	static void Project(Vec3<float>& point, float fov, float aspectRatio)
	{
		point.x = (point.x * fov) / -point.z;
		point.y = (point.y * fov) / -point.z;

		point.x *= aspectRatio;
	}

	static void ScreenSpace(Vec3<float>& point, const Vec2<float>& size)
	{
		point.x = (point.x + 1) * size.x * 0.5f;
		point.y = (1 - point.y) * size.y * 0.5f;
	}

	static bool IsOutsidePlanes(Vec3<float>& point, float zNear, float zFar)
	{
		return (point.z < zNear || point.z > zFar);
	}
	
	static Vec3<float> GetWeights(const Vec3<float>& p0, const Vec3<float>& p1, const Vec3<float>& p2, const Vec2<int>& p3)
	{
		return { Math::Edge(p1, p2, p3), Math::Edge(p2, p0, p3), Math::Edge(p0, p1, p3) };
	}

	static Vec3<float> InterpolateAttribute(const Vec3<float>& a1, const Vec3<float>& a2, const Vec3<float>& a3, const Vec3<float>& w)
	{
		return { w.x * a1.x + w.y * a2.x + w.z * a3.x,  w.x * a1.y + w.y * a2.y + w.z * a3.y, w.x * a1.z + w.y * a2.z + w.z * a3.z };
	}
}}