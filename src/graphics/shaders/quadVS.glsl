layout (location = 0) in vec3 inPosMesh;
layout (location = 1) in vec2 inTexturePos;
layout (location = 2) in vec3 inNormalVectorMesh;

out vec2 texturePos;

void main()
{
	texturePos = inTexturePos;
	gl_Position = vec4(inPosMesh, 1);
}
