#pragma once

#include <glew.h>
#include <iostream>
#include <string>
#include <array>
#include <fstream>
#include <sstream>

#include "Mat4.h"
#include "Vec2.h"

namespace SE {


	class Shader {
	public:
		GLuint m_shaderID;

		Shader();
		Shader(const std::string& vert, const std::string& frag);
		auto enable() ->void const;
		auto disable()->void const;
		auto setUniformMat4(const std::string& name, const mat4& matrix)->void;
		auto setUniform1i(const std::string& name, const int value)->void;
		auto setUniform1f(const GLchar* name, float value)->void;
		auto setUniform2f(const GLchar* name, const vec2& vector)->void;
		auto setUniform3fv(const GLchar*name, const std::array<float, 30>& arr)->void;
		auto setUniform3f(const GLchar* name, const vec3& vector)->void;

		~Shader();

	private:
		std::string m_vertexPath = "";
		std::string m_fragmentPath = "";

		auto getUniformLocation(const std::string& name)->GLint;
		auto load()->GLuint;
	};

}