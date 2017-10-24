#pragma once

#include <glew.h>
#include <iostream>
#include <string>
#include <array>
#include <fstream>
#include <sstream>

#include "Mat4.h"
#include "Vec2.h"

namespace SE
{
	class Shader 
	{
	public:
		GLuint m_shaderID;

		Shader();
		Shader(const std::string& vert, const std::string& frag);
		auto enable() const ->void;
		auto disable() const -> void;
		auto setUniformMat4(const std::string& name, const mat4& matrix) const ->void;
		auto setUniform1i(const std::string& name, const int value) const ->void;
		auto setUniform1f(const GLchar* name, float value) const ->void;
		auto setUniform2f(const GLchar* name, const vec2& vector) const ->void;
		auto setUniform3fv(const GLchar*name, const std::array<float, 30>& arr) const ->void;
		auto setUniform3f(const GLchar* name, const vec3& vector) const ->void;

		~Shader();

	private:
		std::string m_vertexPath = "";
		std::string m_fragmentPath = "";

		auto getUniformLocation(const std::string& name) const ->GLint;
		auto load()->GLuint;
	};

}