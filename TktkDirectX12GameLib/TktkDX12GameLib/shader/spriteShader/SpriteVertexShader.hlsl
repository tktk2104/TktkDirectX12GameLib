cbuffer SpriteMaterialBuffer : register(b0)
{
	float4 blendRate;
	float2 screenSize;
	float2 pad;
};

cbuffer SpriteTransformBuffer : register(b1)
{
	float3x3	worldMatrix;
	float2		textureUvOffset;
	float2		textureUvMulRate;
	float2		textureSize;
	float2		spriteCenterRate;
	
};

struct VS_INPUT
{
	float4 position : POSITION;
};

struct VS_OUTPUT
{
	float2 texcoord : TEXCOORD0;
	float4 position : SV_POSITION;
};

VS_OUTPUT main(VS_INPUT input)
{
	VS_OUTPUT output;

	output.position = input.position;
	output.position.z = 1.0;
	output.position.xy *= textureSize;
	output.position.xy -= (spriteCenterRate * textureSize);
	output.position.xyz = mul(worldMatrix, output.position.xyz);
	
	output.position.xy = output.position.xy * float2(2.0 / screenSize.x, 2.0 / -screenSize.y) + float2(-1.0, 1.0);
	output.texcoord.xy = (input.position.xy * textureUvMulRate) + textureUvOffset;

	return output;
}