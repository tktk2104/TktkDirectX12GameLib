
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

	float Y = dot(col.rgb, float3(0.299, 0.587, 0.114));

	float4 monochromeCol = float4(Y, Y, Y, 1.0);

	return (monochromeCol * effectRate) + (col * (1.0 - effectRate));
}