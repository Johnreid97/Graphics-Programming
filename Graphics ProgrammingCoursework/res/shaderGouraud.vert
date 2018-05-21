#version 400

layout (location = 0) in vec3 VertexPosition;
layout (location = 2) in vec3 VertexNormal;

out vec3 LightingColor;

uniform mat4 transform;
uniform vec3 lightPos;
uniform vec3 viewPos;
uniform vec3 lightColor;



void main()
{
	gl_Position = transform * vec4(VertexPosition, 1.0);

	vec3 v_pos = vec3(VertexPosition);
	vec3 v_norm = mat3(transpose(inverse(transform))) * VertexNormal;
	
	// ambient
	float ambientStrength = 0.1f;
	vec3 ambient = ambientStrength * lightColor;

	//diffuse
	vec3 norm = normalize(v_norm);
	vec3 lightDir = normalize(lightPos - v_pos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff*lightColor;

	//Specular
	float specularStrength = 1.0;
	vec3 viewDir = normalize(viewPos - v_pos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
	vec3 specular = specularStrength * spec* lightColor;

	LightingColor = ambient + diffuse + specular;

	
}

