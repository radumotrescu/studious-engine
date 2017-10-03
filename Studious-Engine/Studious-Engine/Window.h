#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <windows.h>
#include <iostream>
#include <memory>

class Window
{
private:
	int m_width, m_height;
	bool m_closed;

	std::string m_name;
	std::unique_ptr<GLFWwindow*> m_window;

	auto init() -> bool;

public:
	Window(std::string name, int width, int height);

	inline auto getWidth() const -> auto { return m_width; }
	inline auto getHeight() const -> auto { return m_height; }

	auto closed() const -> bool;
	auto update() -> void;

	~Window();
};

