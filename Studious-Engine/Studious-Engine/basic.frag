#version 330 core

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
}