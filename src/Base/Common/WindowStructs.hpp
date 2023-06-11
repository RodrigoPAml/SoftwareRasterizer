#pragma once
#include <Rasterizer.hpp>

namespace Rasterizer {
namespace Window {

	/// <summary>
	/// Initial window configuration.
	/// </summary>
	struct WindowConfiguration
	{
		std::string windowName = "Software Rasterizer";

		Vec2<float> windowPosition = { 40, 40 }, windowSize = { 800, 600 };

		std::uint8_t windowMSAA = 8;

		unsigned int openGlVersionMin = 3;
		unsigned int openGlVersionMax = 4;
	};
}}