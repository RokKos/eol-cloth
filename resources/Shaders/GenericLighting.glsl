#type vertex
#version 330 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec3 a_Normal;
layout(location = 2) in vec2 a_TexCoord;

uniform mat4 u_ViewProjection;
uniform mat4 u_Transform;

out vec3 v_Normal;

void main()
{
	v_Normal = a_Normal;
	gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
}

#type fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec3 v_Normal;

uniform sampler2D u_Texture;

uniform vec3 u_DiffuseColor;
uniform vec3 u_SpecularColor;
uniform float u_SpecularScatering;
uniform vec3 u_AmbientColor;
uniform vec3 u_AmbientIntensity;

void main()
{
	vec3 light_color = u_AmbientColor * u_AmbientIntensity;
	//light_color += u_DiffuseColor * 

	color = vec4(light_color, 1.0f); 
}