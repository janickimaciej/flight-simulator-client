layout (location = 0) in vec3 inPosMesh;

uniform mat4 modelSubmodelMatrix;
uniform mat4 projectionViewMatrix;

void main()
{
	gl_Position = projectionViewMatrix * modelSubmodelMatrix * vec4(inPosMesh, 1);
}
