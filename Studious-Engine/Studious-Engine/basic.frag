#version 330 core

layout (location = 0) out vec4 outColor;

 uniform vec3 Color=vec3(1.0,0.0,0.0);
 uniform vec2 lpos=vec2(0.0,0.0);

 in vec4 pos;
   
void main()
{

	//outColor=vec4(Color,1.0);

		float intensity = 1.0 / length(pos.xy - lpos)*0.5;
		outColor = vec4(Color,1.0) * intensity;
}