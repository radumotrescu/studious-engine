#include "Shader.h"


namespace SE {
	auto Shader::getUniformLocation(const std::string & name) -> GLint
	{
		return glGetUniformLocation(m_shaderID, name.data());
	}

	auto Shader::enable() -> void const
	{
		glUseProgram(m_shaderID);
	}

	Shader::Shader(const std::string & vert, const std::string & frag) :m_vertexPath(vert), m_fragmentPath(frag)
	{
		m_shaderID = load();
	}

	auto Shader::setUniformMat4(const std::string & name, const mat4 & matrix)->void
	{
		glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, matrix.elements);
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

		//std::string vertSourceString = readFile(m_vertexPath);
		//std::string fragSourceString = readFile(m_fragmentPath);

		//const char* vertSource = vertSourceString.c_str();
		//const char* fragSource = fragSourceString.c_str();

		const char* vertexSource =
			R"glsl(#version 330 core	
layout(location=0 ) in vec4 position;
layout(location=1 ) in vec4 color;
	
//out vec4 pos;

uniform mat4 pr_matrix;
uniform mat4 vw_matrix = mat4(1.0);
uniform mat4 ml_matrix = mat4(1.0);

out DATA
{
	vec4 position;
	vec4 color;
}vs_out;

void main()
{
    //colorV = color;
    //gl_Position = vec4(position);
	//vs_out.position=gl_Position;

	gl_Position=pr_matrix * vw_matrix * ml_matrix * position;
	vs_out.position=ml_matrix * position;
	vs_out.color=color;	
})glsl";

		const char* fragmentSource =
			R"glsl(#version 330 core
layout (location = 0) out vec4 outColor;	

uniform vec4 colour=vec4(1.0,0.0,0.0,1.0);
uniform vec2 lpos=vec2(0.0,0.0);


 in DATA
{
	vec4 position;
	vec4 color;
} fs_in;
   
void main()
{
		//float intensity = 1.0 / length(fs_in.color.xy - lpos)*1.0;
		//outColor = vec4(fs_in.color) * intensity;
		outColor = vec4(fs_in.color);
})glsl";

		glShaderSource(vertex, 1, &vertexSource, NULL);
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

		glShaderSource(fragment, 1, &fragmentSource, NULL);
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

	Shader::Shader()
	{
		m_shaderID = load();
	}

	Shader::~Shader()
	{
		glDeleteProgram(m_shaderID);
	}

}
