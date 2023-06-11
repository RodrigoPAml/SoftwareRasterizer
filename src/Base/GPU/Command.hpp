#pragma once
#include <Rasterizer.hpp>

namespace Rasterizer {
namespace GPU {
namespace Command {

	/// <summary>
	/// Controls the Vsync.
	/// </summary>
	void EnableVSync();
	void DisableVSync();

	/// <summary>
	/// Swtich the view port
	/// </summary>
	void SwitchViewPort(const Vec2<int>& pos, const Vec2<int>& size);

	/// <summary>
	/// Clears current framebuffer
	/// </summary>
	void Clear();
}}}
