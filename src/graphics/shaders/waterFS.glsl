#define EPS 1e-9

uniform vec3 cameraPos;
uniform sampler2D colorSampler;
uniform sampler2D depthSampler;
uniform ivec2 viewportSize;
uniform float nearPlane;
uniform float farPlane;
uniform float waterLevel;
uniform float waterTransparencyDepth;

out vec4 outColor;

float depthToClipZ(float depth);

void main()
{
	vec2 fragPos = vec2(gl_FragCoord.x / viewportSize.x, gl_FragCoord.y / viewportSize.y);
	vec3 color = texture(colorSampler, fragPos).rgb;
	float landDepth = texture(depthSampler, fragPos).r;

	float landClipZ = depthToClipZ(landDepth);
	float waterDepth = gl_FragCoord.z;
	float waterClipZ = depthToClipZ(waterDepth);
	float depth = (cameraPos.y - waterLevel) * (landClipZ - waterClipZ) / waterClipZ;
	float alpha = depth / waterTransparencyDepth;
	outColor = vec4(color, alpha);
}

float depthToClipZ(float depth)
{
	return -2 * farPlane * nearPlane /
		((2 * depth - 1) * (farPlane - nearPlane) - farPlane - nearPlane);
}
