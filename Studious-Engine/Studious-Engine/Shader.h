#pragma once

#include <GL\glew.h>
#include <iostream>
#include <string>
#include <array>
#include <fstream>
#include <sstream>

class Shader {

private:
	std::string m_vertexPath;
	std::string m_fragmentPath;

public:
	GLuint m_shaderID;
	auto enable() ->void const;
	auto disable()->void const;

	~Shader();
	Shader(const std::string& vert, const std::string& frag);

private:
	auto load() ->GLuint;
};