
Texture2D		renderTargetTexture : register(t0);
SamplerState	renderTargetSampler : register(s0);

struct PSInput
{
	float2 texcoord : TEXCOORD0;
	float4 position : SV_POSITION;
};

float4 main(PSInput input) : SV_TARGET
{
	return float4(renderTargetTexture.Sample(renderTargetSampler, input.texcoord));
}