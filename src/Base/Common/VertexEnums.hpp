#pragma once
#include <Rasterizer.hpp>

namespace Rasterizer {
namespace GPU {

	/// <summary>
	/// Represents how data will be used in GPU memory.
	/// </summary>
	enum class DataUse
	{
		STREAM_DRAW = GL_STREAM_DRAW,
		STREAM_READ = GL_STREAM_READ,
		STREAM_COPY = GL_STREAM_COPY,
		STATIC_DRAW = GL_STATIC_DRAW,
		STATIC_READ = GL_STATIC_READ,
		STATIC_COPY = GL_STATIC_COPY,
		DYNAMIC_DRAW = GL_DYNAMIC_DRAW,
		DYNAMIC_READ = GL_DYNAMIC_READ,
		DYNAMIC_COPY = GL_DYNAMIC_COPY
	};

	/// <summary>
	/// The type of a vertex buffer.
	/// </summary>
	enum class VertexBufferType
	{
		BYTE = GL_BYTE,
		UBYTE = GL_UNSIGNED_BYTE,
		SHORT = GL_SHORT,
		USHORT = GL_UNSIGNED_SHORT,
		INT = GL_INT,
		UINT = GL_UNSIGNED_INT,
		HALF_FLOAT = GL_HALF_FLOAT,
		FLOAT = GL_FLOAT,
		DOUBLE = GL_DOUBLE,
		INT_2_10_10_10_REV = GL_INT_2_10_10_10_REV,
		UINT_2_10_10_10_REV = GL_UNSIGNED_INT_2_10_10_10_REV
	};

	/// <summary>
	/// Represents how the data will be interpreted to draw.
	/// </summary>
	enum class DrawingType
	{
		POINTS = GL_POINTS,
		LINES = GL_LINES,
		LINE_LOOP = GL_LINE_LOOP,
		LINE_STRIP = GL_LINE_STRIP,
		TRIANGLES = GL_TRIANGLES,
		TRIANGLE_STRIP = GL_TRIANGLE_STRIP,
		TRIANGLE_FAN = GL_TRIANGLE_FAN,
		LINE_ADJACENCY = GL_LINES_ADJACENCY,
		LINE_STRIP_ADJACENCY = GL_LINE_STRIP_ADJACENCY,
		TRIANGLES_ADJACENCY = GL_TRIANGLES_ADJACENCY,
		TRIANGLE_STRIP_ADJACENCY = GL_TRIANGLE_STRIP_ADJACENCY,
	};
}}