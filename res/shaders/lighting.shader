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

uniform sampler2D uTexture;
uniform vec3 lightPos;
uniform vec3 objectColor;
uniform vec3 viewPos;
uniform vec3 lightColor;

void main()
{
	// ambient
	float ambient = 0.1;

	//diffuse
	// Make the normal vector, a unit vector
	vec3 norm = normalize(Normal);
	// Get the unit vector of the light direction
	// Note this is pointing from Frag to Lightpos, because vector subtraction will start at b and go to a
	vec3 lightDir = normalize(lightPos - FragPos);
	// dot will give cos(theta), in the dot product method, since both are unit vectors
	// cos(theta) will be relative to the normal vector (in a cube's case pointing straight upward). Meaning the unit circle will start at the normal vector
	// So if the light dir is directly above, it will be cos(theta) = 1, if the difference is 45 degrees it will be cos(theta) = 0.5
	float diffuse = max(dot(norm, lightDir), 0.0);
	
	float specular = 0.0;
	if (diffuse != 0.0)
	{
		// specular
		float specularStrength = 0.5;
		// Get the unit vector for viewDir
		vec3 viewDir = normalize(viewPos - FragPos);
		// Addition of two vectors will give us the halfway of that vector, then we normalize it
		vec3 halfwayVec = normalize(viewDir + lightDir);
		// We then get the angle between the normal and the halfway due to them being unit vectors
		// And then take that or zero (as to ignore negative values) and take it to an abitrrary power
		float specAmount = pow(max(dot(norm, halfwayVec), 0.0), 16);
		specular = specAmount * specularStrength;
	}


	vec3 result = (ambient + diffuse + specular) * lightColor * objectColor;
	FragColor = vec4(result, 1.0);
}