#version 460 core

in vec3 fragColour;
in vec2 fragTexture;

out vec4 Colour;

uniform sampler2D tex;
uniform vec2 coords;

void main()
{
	vec2 tempTexCoords = fragTexture + coords;
	Colour = texture(tex, tempTexCoords);
}