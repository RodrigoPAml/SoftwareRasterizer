#pragma once

// GLAD
#include <glad/glad.h>

// GLFW3
#include <GLFW/glfw3.h>

// ImGui
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

// C++ Headers
#include <iostream>
#include <string>
#include <chrono>
#include <algorithm>
#include <stack>
#include <tuple>
#include <functional>
#include <filesystem>
#include <exception>
#include <unordered_map>
#include <sstream>
#include <vector>
#include <ostream>
#include <mutex>
#include <fstream>
#include <memory>
#include <queue>
#include <any>
#include <set>
#include <map>

// Includes

#include <Base/Vector/Vec2.hpp>
#include <Base/Vector/Vec3.hpp>
#include <Base/Vector/Vec4.hpp>

#include <Base/Common/WindowStructs.hpp>
#include <Base/Common/GuiEnums.hpp>

#include <Base/Common/InputEnums.hpp>
#include <Base/Common/TextureEnums.hpp>
#include <Base/Common/TextureStructs.hpp>

#include <Base/Window/Window.hpp>
#include <Base/Input/Mouse.hpp>
#include <Base/Input/Keyboard.hpp>

#include <Base/Utils/Image.hpp>
#include <Base/Utils/Directory.hpp>
#include <Base/Utils/Time.hpp>

#include <Base/GPU/Texture.hpp>

#include <Base/Window/GUI.hpp>

#include <Base/GPU/PixelBuffer.hpp>
#include <Base/GPU/Command.hpp>

#include <Base/Common/VertexEnums.hpp>
#include <Base/Common/VertexStructs.hpp>

#include <Base/GPU/Shader.hpp>
#include <Base/GPU/Vertex.hpp>

#include <Base/Drawing/TextureRenderer.hpp>

#include <Base/Importer/Material.hpp>
#include <Base/Importer/Mesh.hpp>
#include <Base/Importer/Object.hpp>
#include <Base/Importer/Importer.hpp>

#include <Implementation/Enums/DrawModeEnum.hpp>
#include <Implementation/Raster/Math.hpp>
#include <Implementation/Camera/Camera.hpp>
#include <Implementation/Raster/Pipeline.hpp>
#include <Implementation/Raster/Raster.hpp>