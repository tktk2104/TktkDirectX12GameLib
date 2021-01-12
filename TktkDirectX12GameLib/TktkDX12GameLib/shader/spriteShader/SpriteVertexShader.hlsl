
cbuffer ScreenSizeBuffer : register(b0)
{
	float2		ScreenSize;
	float2		Pad;
};

struct VS_INPUT
{
	float4		position			: POSITION;

	float3x3	worldMatrix			: WORLDMATRIX;
	float2		textureUvOffset		: UVOFFSET;
	float2		textureUvMulRate	: UVMULRATE;
	float2		textureSize			: TEXTURESIZE;
	float2		textureCenterRate	: TEXTURECENTERRATE;
	float4		blendRate			: BLENDRATE;
};

struct VS_OUTPUT
{
	float4 position		: SV_POSITION;
	float2 texcoord		: TEXCOORD0;
	float4 blendRate	: BLENDRATE;
};

VS_OUTPUT main(VS_INPUT input)
{
	VS_OUTPUT output;

	output.position		= input.position;
	output.position.z	= 1.0;
	output.position.xy *= input.textureSize;
	output.position.xy -= (input.textureCenterRate * input.textureSize);
	output.position.xyz = mul(input.worldMatrix, output.position.xyz);
	
	output.position.xy = output.position.xy * float2(2.0 / ScreenSize.x, 2.0 / -ScreenSize.y) + float2(-1.0, 1.0);
	output.texcoord.xy = (input.position.xy * input.textureUvMulRate) + input.textureUvOffset;
	
	output.blendRate = input.blendRate;

	return output;
}