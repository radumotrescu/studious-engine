#pragma once

#include <GL\glew.h>
#include <iostream>
#include <string>
#include <array>
#include <fstream>
#include <sstream>

#include "Mat4.h"

class Shader {

private:
	std::string m_vertexPath;
	std::string m_fragmentPath;
	
public:
	GLuint m_shaderID;
	auto enable() ->void const;
	auto disable()->void const;
	
	Shader();
	~Shader();
	Shader(const std::string& vert, const std::string& frag);
	auto setUniformMat4(const std::string& name, const mat4& matrix)->void;

private:
	auto getUniformLocation(const std::string& name)->GLint;
	auto load() ->GLuint;
};