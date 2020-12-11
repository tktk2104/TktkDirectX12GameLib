
// 定数バッファ
cbuffer ConstantBuffer : register(b0)
{
	float effectRate;
};

Texture2D		renderTargetTexture : register(t0);
SamplerState	renderTargetSampler : register(s0);

struct PSInput
{
	float2 texcoord : TEXCOORD0;
	float4 position : SV_POSITION;
};

float4 main(PSInput input) : SV_TARGET
{
	float4 col = renderTargetTexture.Sample(renderTargetSampler, input.texcoord);

	float4 negaCol = float4(1.0 - col.rgb, col.a);

	return (negaCol * effectRate) + (col * (1.0 - effectRate));
}