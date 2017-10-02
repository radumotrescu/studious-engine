#include "Window.h"

bool Window::init()
{
	if(!glfwInit())
	{
		MessageBox(nullptr, "Failed to initialize GLFW", "Error", MB_OK | MB_ICONERROR);

		return false;
	}

	this->m_window = glfwCreateWindow(this->m_height, this->m_width, this->m_name, nullptr, nullptr);

	if (!this->m_window)
	{
		MessageBox(nullptr, "Failed to create window", "Error", MB_OK | MB_ICONERROR);

		return false;
	}

	glfwMakeContextCurrent(this->m_window);

	return true;
}

Window::Window(const char* name, int width, int height)
	: m_name(name),
	m_width(width),
	m_height(height)
{
	if(!init())
	{
		glfwTerminate();
	}
}

bool Window::closed() const
{
	return glfwWindowShouldClose(this->m_window);
}

void Window::update()
{
	glfwSwapBuffers(this->m_window);
	glfwGetFramebufferSize(this->m_window, &this->m_width, &this->m_height);
	glfwPollEvents();
}

Window::~Window()
{
	delete this->m_name;
	glfwTerminate();
}
