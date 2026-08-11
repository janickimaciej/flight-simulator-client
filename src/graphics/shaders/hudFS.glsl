in vec2 texturePos;

uniform sampler2D textureSampler;

out vec4 outColor;

void main()
{
	vec4 textureColor = texture(textureSampler, texturePos);
	outColor = vec4(0, 0.68, 0.05, textureColor.a);
}
