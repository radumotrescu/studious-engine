#pragma once

#include <glew.h>
#include <iostream>
#include <string>
#include <array>
#include <fstream>
#include <sstream>

#include "Mat4.h"

class Shader {
public:
	GLuint m_shaderID;

	Shader();
	Shader(const std::string& vert, const std::string& frag);
	auto enable() ->void const;
	auto disable()->void const;
	auto setUniformMat4(const std::string& name, const mat4& matrix)->void;
	~Shader();

private:
	std::string m_vertexPath="";
	std::string m_fragmentPath="";

	auto getUniformLocation(const std::string& name)->GLint;
	auto load() ->GLuint;
};