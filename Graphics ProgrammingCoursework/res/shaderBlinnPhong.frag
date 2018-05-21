#version 400
out vec4 FragColor;
 
uniform vec3 lightPos;
uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 viewPos;

//uniform bool blinn;

in vec3 v_norm;
in vec4 v_pos;

void main()
{
// ambient
	float ambientStrength = 0.1;
	vec3 ambient = ambientStrength * lightColor;

	//diffuse
	vec3 norm = normalize(v_norm);
	vec3 lightDir = normalize(lightPos *lightColor);
	float diff = max(dot(lightDir, norm), 0.0);
	vec3 diffuse = diff*lightColor;

	//Specular

	vec3 viewDir = normalize(viewPos - v_norm);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = 0.0;


	vec3 halfwayDir = normalize (lightDir + viewDir);
	spec = pow(max(dot(norm,halfwayDir), 0.0), 32);

	vec3 specular = vec3(0.3) * spec* lightColor;
	vec3 result = (ambient + diffuse + specular) * objectColor;

    FragColor = vec4(result, 1.0);
}

