
struct VSInput
{
	float4 position	: POSITION;
};

struct VSOutput
{
	float2 texcoord : TEXCOORD0;
	float4 position : SV_POSITION;
};

VSOutput main(VSInput input)
{
	VSOutput output;
	output.position = input.position;
	output.position.x -= 0.5;
	output.position.y -= 0.5;
	output.position.x *= 2.0;
	output.position.y *= -2.0;
	output.texcoord.xy = input.position.xy;
	return output;
}