#include "InputManager.h"

namespace SE {
	std::unordered_multimap<int, std::function<void()>> InputManager::m_actionKey;

	InputManager::InputManager()
	{
	}

	auto InputManager::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) -> void
	{
		const auto range = m_actionKey.equal_range(key);

		for (auto it = range.first; it != range.second; ++it)
		{
			it->second();
		}
	}

	auto InputManager::getInstance() -> InputManager&
	{
		static InputManager instance;

		return instance;
	}

	auto InputManager::init(GLFWwindow* window) -> void
	{
		glfwSetKeyCallback(window, InputManager::keyCallback);
	}

	auto InputManager::registerSpriteAction(std::function<void()> action, int key) -> void
	{
		m_actionKey.insert(std::make_pair(key, action));
	}

}
