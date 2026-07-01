// ...Mesh – vector in mesh coordinate system
// ... – vector in global coordinate system

layout (location = 0) in vec3 inPosMesh;
layout (location = 1) in vec2 inTexturePos;
layout (location = 2) in vec3 inNormalVectorMesh;

uniform mat4 modelSubmodelMatrix;
uniform mat4 projectionViewMatrix;

out vec4 pos;
out vec2 texturePos;

void main()
{
	pos = modelSubmodelMatrix * vec4(inPosMesh, 1);
	texturePos = inTexturePos;
	gl_Position = projectionViewMatrix * pos;
}
