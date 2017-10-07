#pragma once

#include <unordered_map>

#include "GLFW/glfw3.h"
#include <functional>

class InputManager
{
public:
	static auto getInstance() -> InputManager&;

	static auto init(GLFWwindow* window) -> void;
	static auto registerSpriteAction(std::function<void(void)> ,int) -> void;

	InputManager(InputManager const&) = delete;
	void operator=(InputManager const&) const = delete;

private:
	InputManager();

	static std::unordered_multimap<int, std::function<void(void)>> m_actionKey;

	static auto keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) -> void;
};
