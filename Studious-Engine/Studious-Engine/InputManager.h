#pragma once

#include <unordered_map>

#include "Sprite.h"
#include "GLFW/glfw3.h"

class InputManager
{
public:
	static InputManager& getInstance();

	static void init(GLFWwindow* window);
	static void registerSpriteAction(int key, Sprite sprite);

	InputManager(InputManager const&) = delete;
	void operator=(InputManager const&) const = delete;

private:
	InputManager();

	static std::unordered_multimap<int, Sprite> m_sprites;

	static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
};

