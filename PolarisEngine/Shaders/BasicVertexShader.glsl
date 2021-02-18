#version 410

layout (location = 0) in vec3 vPosition;
layout (location = 1) in vec3 vNormal;
layout (location = 2) in vec2 vTextCoord;

uniform mat4 mModelView;
uniform mat4 mModelViewIT;
uniform mat4 matrixMVP;

out vec3 position;
out vec3 normal;
out vec2 textCoord;

void main ()
{
	textCoord = vTextCoord;

	normal = vec3 (mModelViewIT * vec4 (vNormal, 0.0 ) );
	position = vec3 (mModelView * vec4 (vPosition, 1.0 ) ); 

	gl_Position = matrixMVP * vec4 ( vPosition, 1.0 );
};