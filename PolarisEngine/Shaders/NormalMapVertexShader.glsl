#version 410

layout (location = 0) in vec3 vPosition;
layout (location = 1) in vec3 vNormal;
layout (location = 2) in vec2 vTextCoord;
layout (location = 3) in vec3 vTangent;
layout (location = 4) in vec3 vBitangent;

uniform mat4 mModelView;
uniform mat4 mModelViewIT;
uniform mat4 matrixMVP;
uniform vec3 lightPos;
uniform vec3 lightDir;

out vec3 tangentPos;
out vec2 textCoord;

out vec3 lightPosTangent;
out vec3 lightDirTangent;

void main ()
{	
	vec3 modelViewTangent = normalize( vec3( mModelViewIT * vec4(vTangent, 0.0) ) );
	vec3 modelViewBitangent = normalize( vec3( mModelViewIT * vec4(vBitangent, 0.0) ) );
	vec3 normal = normalize (vec3 (mModelViewIT * vec4(vNormal, 0.0 ) ) );

	mat3 TBN = transpose(mat3(modelViewTangent, modelViewBitangent, normal));

	tangentPos = TBN * vec3(mModelView * vec4(vPosition, 1.0));

	lightPosTangent = TBN * lightPos;
	lightDirTangent = TBN * lightDir;

	gl_Position = matrixMVP * vec4 ( vPosition, 1.0 );
	textCoord = vTextCoord;
};