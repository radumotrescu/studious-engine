#include "InputManager.h"
#include <algorithm>

std::unordered_multimap<int, Sprite> InputManager::m_sprites;

InputManager::InputManager()
{
}

void InputManager::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	const auto range = m_sprites.equal_range(key);

	for(auto it = range.first; it != range.second; ++it)
	{
		it->second.action();
	}
}

InputManager& InputManager::getInstance()
{
	static InputManager instance;

	return instance;
}

void InputManager::init(GLFWwindow* window)
{
	glfwSetKeyCallback(window, InputManager::keyCallback);
}


void InputManager::registerSpriteAction(int key, Sprite sprite)
{
	m_sprites.emplace(std::make_pair(key, sprite));
}

