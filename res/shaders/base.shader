#vertex
#version 430 core
layout (location = 0) in vec3 aPos;

void main()
{
	gl_Position = vec4(aPos.xyz, 1.0);
}

#fragment
#version 430 core
out vec4 FragColor;

void main()
{
	FragColor = vec4(1.0, 0.5, 0.2, 1.0);
}