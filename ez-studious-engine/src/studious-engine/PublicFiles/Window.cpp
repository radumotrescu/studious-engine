#include "Window.h"
namespace SE {
	Window::Window(std::string name, int width, int height)
		: m_width(width),
		m_height(height),
		m_name(name)
	{
		if (!init())
		{
			glfwTerminate();
		}
	}

	auto Window::getWidth() const -> int
	{
		return m_width;
	}

	auto Window::init() -> bool
	{
		if (!glfwInit())
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

		if (glewInit() != GLEW_OK)
		{
			MessageBox(nullptr, "Failed to initialize GLEW", "Error", MB_OK | MB_ICONERROR);

			return false;
		}

		glClearColor(1.0f, 0.0f, 1.0f, 1.0f);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		return true;
	}


	auto Window::clear() -> void const
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	auto Window::getHeight() const -> int
	{
		return m_height;
	}

	auto Window::getWindow() const -> GLFWwindow*
	{
		return *this->m_window.get();
	}

	auto Window::closed() const -> bool
	{
		return glfwWindowShouldClose(*this->m_window.get()) != 0;
	}

	auto Window::update() -> void
	{
		glfwSwapBuffers(*this->m_window.get());
		glfwGetFramebufferSize(*this->m_window.get(), &this->m_width, &this->m_height);
		glfwPollEvents();
	}

	Window::~Window()
	{
		glfwTerminate();
	}

}
