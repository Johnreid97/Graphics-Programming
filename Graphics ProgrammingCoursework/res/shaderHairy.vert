#version 400

layout (location = 0) in vec3 VertexPosition;
layout (location = 2) in vec3 VertexNormal;

uniform mat4 transform;


vec3 v_norm;

out vec4 v_pos; 

void main()
{
	gl_Position = transform * vec4(VertexPosition, 1.0);
	v_pos = vec4(VertexPosition, 1.0);
	mat3 normalMatrix = mat3(transpose(inverse(transform)));
	v_norm = normalize(vec3(transform * vec4(normalMatrix * VertexNormal, 0.0)));
}