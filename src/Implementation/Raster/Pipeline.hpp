#pragma once
#include <Rasterizer.hpp>

namespace Rasterizer {
namespace Pipeline {
		
	static void Project(Vec3<float>& point, float fov, float aspectRatio)
	{
		point.x = (point.x * fov)  / -point.z;
		point.y = (point.y * fov) / -point.z;

		point.x *= aspectRatio;
	}

	static void ScreenSpace(Vec3<float>& point, const Vec2<float>& size)
	{
		point.x = (point.x + 1) * size.x * 0.5f;
		point.y = (1 - point.y) * size.y * 0.5f;
	}

	static bool IsOutsidePlanes(const Vec3<float>& point, float zNear, float zFar)
	{
		return (point.z < zNear || point.z > zFar);
	}
	
	static bool IsOutsideScreen(const Vec3<float>& p1, const Vec3<float>& p2, const Vec3<float>& p3, float width, float height)
	{
		return ((p1.x < 0 && p2.x < 0 && p3.x < 0) || (p1.x > width && p2.x > width && p3.x > width) || (p1.y < 0 && p2.y < 0 && p3.y < 0) || (p1.y > height && p2.y > height && p3.y > height));
	}

	static Vec3<float> GetWeights(const Vec3<float>& p0, const Vec3<float>& p1, const Vec3<float>& p2, const Vec2<int>& p)
	{
		return { Math::Edge(p1, p2, p), Math::Edge(p2, p0, p), Math::Edge(p0, p1, p) };
	}

	static Vec3<float> InterpolateAttribute(const Vec3<float>& a1, const Vec3<float>& a2, const Vec3<float>& a3, const Vec3<float>& w)
	{
		return { w.x * a1.x + w.y * a2.x + w.z * a3.x,  w.x * a1.y + w.y * a2.y + w.z * a3.y, w.x * a1.z + w.y * a2.z + w.z * a3.z };
	}

	static Vec2<float> InterpolateAttribute(const Vec2<float>& a1, const Vec2<float>& a2, const Vec2<float>& a3, const Vec3<float>& w)
	{
		return { w.x * a1.x + w.y * a2.x + w.z * a3.x,  w.x * a1.y + w.y * a2.y + w.z * a3.y };
	}

	static float InterpolateAttribute(const float& a1, const float& a2, const float& a3, const Vec3<float>& w)
	{
		return { w.x * a1 + w.y * a2 + w.z * a3};
	}

	static float IsCulled(const Vec3<float>& p1, const Vec3<float>& p2, const Vec3<float>& p3, const Vec3<float>& front)
	{
		Vec3<float> v1 = p2 - p1;
		Vec3<float> v2 = p3 - p1;

		Vec3<float> normal = {
			(v1.y * v2.z) - (v1.z * v2.y),
			(v1.z * v2.x) - (v1.x * v2.z),
			(v1.x * v2.y) - (v1.y * v2.x)
		};

		float diff = Math::Dot(Math::Normalize(front), Math::Normalize(normal));

		return 0.0f <= diff;
	}
}}