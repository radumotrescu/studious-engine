#pragma once

#include <windows.h>
#include <glew.h>
#include <glfw3.h>
#include <iostream>
#include <memory>

class Window
{

public:
	Window(std::string name, int width, int height);
	auto getWidth() const -> int;
	auto getHeight() const -> int;
	auto getWindow() const -> GLFWwindow*;
	auto closed() const -> bool;
	auto update() -> void;
	auto clear()->void const;
	~Window();

private:
	int m_width, m_height;
	bool m_closed;
	std::string m_name;
	std::unique_ptr<GLFWwindow*> m_window;

	auto init() -> bool;
};

