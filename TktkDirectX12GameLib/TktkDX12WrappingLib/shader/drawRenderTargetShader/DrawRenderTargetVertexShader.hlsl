
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
	output.texcoord.xy = input.position.xy;
	return output;
}