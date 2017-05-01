// =========
// retina.fs
// =========

#version 130

in vec2 UV;

out vec4 outColor;

uniform sampler2D textureSampler;

void main()
{
	outColor = texture(textureSampler, UV);
}