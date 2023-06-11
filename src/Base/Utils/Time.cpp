#include <Rasterizer.hpp>
#include "Time.hpp"

namespace Rasterizer {
namespace Utils {
namespace Time {

	double GetTimestamp()
	{
		return glfwGetTime();
	}
}}}
