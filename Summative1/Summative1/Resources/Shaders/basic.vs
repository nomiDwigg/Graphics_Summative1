#version 460 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 colour;
layout (location = 2) in vec2 texture;

out vec3 fragColour;
out vec2 fragTexture;

void main()
{
	gl_Position = vec4(pos, 1.0f);
	fragColour = colour;
	fragTexture = texture;
}
