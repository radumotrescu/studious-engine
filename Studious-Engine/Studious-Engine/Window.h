#pragma once

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

	bool init();

public:
	Window(std::string name, int width, int height);

	bool closed() const;
	void update();

	int width() const { return m_width; }
	int height() const { return m_height; }


	~Window();
};

