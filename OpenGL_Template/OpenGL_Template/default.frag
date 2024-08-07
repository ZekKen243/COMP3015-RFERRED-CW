#version 460 core
out vec4 FragColor;

// Inputs the color from Vertex Shader
in vec3 color;

void main()
{
	FragColor = vec4(color, 1.0f);
}