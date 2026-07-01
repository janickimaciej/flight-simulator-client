// ... – vector in global coordinate system

in vec2 texturePos;

uniform sampler2D textureSampler;

out vec4 outColor;

void main()
{
	vec4 color = texture(textureSampler, texturePos);
	float threshold = 0.01;
	if (color.a < 0.01)
	{
		discard;
	}

	outColor = vec4(0, 0.68, 0.05, 1);
}
