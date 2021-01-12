struct PS_INPUT
{
	float4 position		: SV_POSITION;
	float2 texcoord		: TEXCOORD0;
	float4 blendRate	: BLENDRATE;
};

Texture2D		TextureMapTexture : register(t0);
SamplerState	TextureMapSampler : register(s0);

float4 main(PS_INPUT input) : SV_Target
{
	return TextureMapTexture.Sample(TextureMapSampler, input.texcoord)* input.blendRate;
}