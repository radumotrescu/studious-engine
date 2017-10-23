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

	auto Shader::setUniform1i(const std::string & name, const int value) -> void
	{
		glUniform1i(getUniformLocation(name), value);
	}
	void Shader::setUniform1f(const GLchar* name, float value)
	{
		glUniform1f(getUniformLocation(name), value);
	}

	void Shader::setUniform2f(const GLchar* name, const vec2& vector)
	{
		glUniform2f(getUniformLocation(name), vector.x, vector.y);
	}
	void Shader::setUniform3f(const GLchar* name, const vec3& vector)
	{
		glUniform3f(getUniformLocation(name), vector.x, vector.y, vector.z);
	}

	void Shader::setUniform3fv(const GLchar*name, const std::array<float, 30>& arr)
	{
		glUniform3fv(getUniformLocation(name), 10, arr.data());
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
layout(location=2 ) in vec2 textureCoord;
	
//out vec4 pos;

uniform mat4 pr_matrix;
uniform mat4 vw_matrix = mat4(1.0);
uniform mat4 ml_matrix = mat4(1.0);

out DATA
{
	vec4 position;
	vec4 color;
	vec2 textureCoord;
}vs_out;

void main()
{
    //colorV = color;
    //gl_Position = vec4(position);
	//vs_out.position=gl_Position;

	gl_Position=pr_matrix * vw_matrix * ml_matrix * position;
	vs_out.position=ml_matrix * position;
	vs_out.textureCoord=textureCoord;
	vs_out.color=color;	
})glsl";

		const char* fragmentSource =

			R"glsl(#version 330 core
layout (location = 0) out vec4 outColor;	

uniform vec4 colour=vec4(1.0,0.0,0.0,1.0);
uniform vec2 lpos=vec2(0.0,0.0);
uniform vec3 lcolor=vec3(1.0,1.0,1.0);
uniform float lintensity=1.0f;
uniform float lradius=1.0f;


in DATA
{
	vec4 position;	
	vec4 color;
	vec2 textureCoord;
} fs_in;

uniform bool ambientLight=true;																															   
uniform sampler2D tex;
uniform vec2 scrollingOffset=vec2(0.1,0.1);
uniform bool lightEnabled=false;
uniform bool affectedByLighting=false;

void main()
{
	if(lightEnabled==true){
	
	float distance = length(lpos - fs_in.position.xy);
	float attenuation = 1.0 / distance*lradius;

	//outColor = texture(tex, fs_in.textureCoord)*vec4(attenuation,attenuation,attenuation,pow(attenuation,lintensity))*vec4(fs_in.color);
if(affectedByLighting==true)
	
	outColor = texture(tex, vec2(scrollingOffset.x+fs_in.textureCoord.x,scrollingOffset.y+fs_in.textureCoord.y))*vec4(attenuation,attenuation,attenuation,pow(attenuation,lintensity))*vec4(fs_in.color);
else
 
	outColor = texture(tex, vec2(scrollingOffset.x+fs_in.textureCoord.x,scrollingOffset.y+fs_in.textureCoord.y))*vec4(fs_in.color);
	}
else
{

	outColor = texture(tex, vec2(scrollingOffset.x+fs_in.textureCoord.x,scrollingOffset.y+fs_in.textureCoord.y))*vec4(fs_in.color);
}

})glsl";
		const int shaderNumber = 1;
		const int shaderLenght = 0;
		glShaderSource(vertex, shaderNumber, &vertexSource, shaderLenght);
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

		glShaderSource(fragment, shaderNumber, &fragmentSource, shaderLenght);
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
