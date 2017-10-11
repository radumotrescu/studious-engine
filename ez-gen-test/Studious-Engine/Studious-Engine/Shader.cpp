#include "Shader.h"


auto Shader::enable() -> void const
{
	glUseProgram(m_shaderID);
}



Shader::Shader(const std::string & vert, const std::string & frag) :m_vertexPath(vert), m_fragmentPath(frag)
{
	m_shaderID = load();
}

auto readFile(const std::string& path) -> std::string
{
	std::ifstream fin(path);
	std::stringstream ss;
	ss << fin.rdbuf();
	return ss.str();
}

GLuint Shader::load()
{
	GLuint program = glCreateProgram();
	GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);

	std::string vertSourceString = readFile(m_vertexPath);
	std::string fragSourceString = readFile(m_fragmentPath);

	const char* vertSource = vertSourceString.c_str();
	const char* fragSource = fragSourceString.c_str();

	glShaderSource(vertex, 1, &vertSource, NULL);
	glCompileShader(vertex);

	GLint result;
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE)
	{
		GLint length;
		glGetShaderiv(vertex, GL_INFO_LOG_LENGTH, &length);
		std::array<char, 1024> error;
		glGetShaderInfoLog(vertex, length, &length, &error[0]);
		std::cout << "Failed to compile vertex shader!" << std::endl << &error[0] << std::endl;
		glDeleteShader(vertex);
		return 0;
	}

	glShaderSource(fragment, 1, &fragSource, NULL);
	glCompileShader(fragment);

	glGetShaderiv(fragment, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE)
	{
		GLint length;
		glGetShaderiv(fragment, GL_INFO_LOG_LENGTH, &length);
		std::array<char, 1024> error;
		glGetShaderInfoLog(fragment, length, &length, &error[0]);
		std::cout << "Failed to compile fragment shader!" << std::endl << &error[0] << std::endl;
		glDeleteShader(fragment);
		return 0;
	}
	glBindFragDataLocation(program, 0, "outColor");


	glAttachShader(program, vertex);
	glAttachShader(program, fragment);

	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vertex);
	glDeleteShader(fragment);

	return program;

}
auto Shader::disable() -> void const
{
	glUseProgram(0);
}

Shader::~Shader()
{
	glDeleteProgram(m_shaderID);
}

