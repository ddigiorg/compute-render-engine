// =========
// retina.vs
// =========

#version 130

in vec2 vertexXY;
in vec2 vertexUV;

out vec2 UV;

uniform mat4 viewMatrix;
uniform mat4 projMatrix;

void main()
{
	gl_Position = viewMatrix * projMatrix * vec4(vertexXY.x, vertexXY.y, 0.0, 1.0);
	UV = vertexUV;
}