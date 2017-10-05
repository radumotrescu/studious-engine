#version 330 core

layout (location = 0) out vec4 outColor;

 uniform vec3 Color=vec3(1.0,0.0,0.0);
 uniform vec2 lpos=vec2(0.0,0.0);

 in vec4 pos;

 in DATA
{
	vec4 position;
	vec4 color;
} fs_in;
   
void main()
{

	//outColor=vec4(Color,1.0);

		float intensity = 1.0 / length(fs_in.color.xy - lpos)*0.5;
		outColor = vec4(fs_in.color) * intensity;
}