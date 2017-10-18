#version 330 core

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
}