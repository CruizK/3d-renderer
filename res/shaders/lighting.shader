#vertex
#version 450 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in vec3 aNormal;

out vec2 TexCoord;
out vec3 FragPos;
out vec3 Normal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	gl_Position = projection * view * model * vec4(aPos, 1.0);
	FragPos = vec3(model * vec4(aPos, 1.0));
	TexCoord = aTexCoord;
	Normal = mat3(transpose(inverse(model))) * aNormal;
}

#fragment
#version 450 core
out vec4 FragColor;

in vec2 TexCoord;
in vec3 FragPos;
in vec3 Normal;

struct Material {

	vec3 ambient;
	sampler2D diffuse;
	vec3 specular;
	float shininess;
};

struct Light {
	vec3 position;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	float constant;
	float linear;
	float quadratic;
};

uniform Light light;
uniform Material material;

uniform vec3 viewPos;

void main()
{
	vec3 color = texture(material.diffuse, TexCoord).rgb;

	// ambient
	vec3 ambient = light.ambient * color * material.ambient;
	//vec3 ambient = color * 0.1;

	//diffuse
	// Make the normal vector, a unit vector
	vec3 norm = normalize(Normal);
	// Get the unit vector of the light direction
	// Note this is pointing from Frag to Lightpos, because vector subtraction will start at b and go to a
	vec3 lightDir = normalize(light.position - FragPos);
	// dot will give cos(theta), in the dot product method, since both are unit vectors
	// cos(theta) will be relative to the normal vector (in a cube's case pointing straight upward). Meaning the unit circle will start at the normal vector
	// So if the light dir is directly above, it will be cos(theta) = 1, if the difference is 45 degrees it will be cos(theta) = 0.5
	float diff = max(dot(lightDir, norm), 0.0);
	vec3 diffuse = light.diffuse * (diff * color);
	//vec3 diffuse = diff * color;

	vec3 specular = vec3(0.0);
	if (diff != 0.0)
	{
		// Get the unit vector for viewDir
		vec3 viewDir = normalize(viewPos - FragPos);
		// Addition of two vectors will give us the halfway of that vector, then we normalize it
		vec3 halfwayVec = normalize(viewDir + lightDir);
		// We then get the angle between the normal and the halfway due to them being unit vectors
		// And then take that or zero (as to ignore negative values) and take it to an abitrrary power
		float spec = pow(max(dot(norm, halfwayVec), 0.0), 32.0);
		specular = light.specular * (spec * material.specular);
		//specular = (spec * vec3(0.3));
	}

	float distance = length(light.position - FragPos);
	float attenuation = 1.0/ (light.constant + light.linear * distance + light.quadratic * (distance * distance));
	ambient *= attenuation;
	diffuse *= attenuation;
	specular *= attenuation;
	
	FragColor = vec4(ambient + diffuse + specular, 1.0);
}