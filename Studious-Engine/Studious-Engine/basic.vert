#version 330 core

layout(location=0 ) in vec4 position;
layout(location=1 ) in vec4 color;
	
out vec4 pos;

out DATA
{
	vec4 position;
	vec4 color;
}vs_out;

void main()
{
    //colorV = color;
    gl_Position = vec4(position);
	vs_out.position=gl_Position;
	vs_out.color=color;	
}