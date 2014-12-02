#version 150

out vec4 FragColor;
in vec3 vertexNormalOut;
in vec3 cameraDirectionOut;

void main()
{
	FragColor = vec4(vertexNormalOut,1.0f);
}