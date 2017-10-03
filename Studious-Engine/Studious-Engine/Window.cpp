#include "Window.h"

bool Window::init()
{
	if(!glfwInit())
	{
		MessageBox(nullptr, "Failed to initialize GLFW", "Error", MB_OK | MB_ICONERROR);

		return false;
	}

	this->m_window = std::make_unique<GLFWwindow*>(glfwCreateWindow(this->m_height, this->m_width, this->m_name.c_str(), nullptr, nullptr));

	if (!*this->m_window.get())
	{
		MessageBox(nullptr, "Failed to create window", "Error", MB_OK | MB_ICONERROR);

		return false;
	}

	glfwMakeContextCurrent(*this->m_window.get());
	
	return true;
}

Window::Window(std::string name, int width, int height)
	: m_width(width),
	m_height(height),
	m_name(name)
{
	if(!init())
	{
		glfwTerminate();
	}
}

bool Window::closed() const
{
	return glfwWindowShouldClose(*this->m_window.get());
}

void Window::update()
{
	glfwSwapBuffers(*this->m_window.get());
	glfwGetFramebufferSize(*this->m_window.get(), &this->m_width, &this->m_height);
	glfwPollEvents();
}

Window::~Window()
{
	glfwTerminate();
}
