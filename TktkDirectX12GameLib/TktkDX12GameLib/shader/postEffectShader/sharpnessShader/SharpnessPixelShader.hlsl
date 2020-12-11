
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
	float w, h, levels;

	renderTargetTexture.GetDimensions(0, w, h, levels);

	float dx = 1.0 / w;
	float dy = 1.0 / h;

	float4 col = renderTargetTexture.Sample(renderTargetSampler, input.texcoord);

	/*
	各ピクセルの重み（中心が元のピクセル）
	 0, -1,  0
	-1,  5, -1
	 0, -1, -0
	*/

	// 周囲４ピクセルの色を元のピクセルの色に足す
	float4 sharpnessCol = float4(0.0, 0.0, 0.0, 0.0);
	sharpnessCol += renderTargetTexture.Sample(renderTargetSampler, input.texcoord + float2( 0.0,		-2.0 * dy)) * -1.0;
	sharpnessCol += renderTargetTexture.Sample(renderTargetSampler, input.texcoord + float2(-2.0 * dx,	 0.0))		* -1.0;
	sharpnessCol += col * 5.0;
	sharpnessCol += renderTargetTexture.Sample(renderTargetSampler, input.texcoord + float2( 2.0 * dx,	 0.0))		* -1.0;
	sharpnessCol += renderTargetTexture.Sample(renderTargetSampler, input.texcoord + float2( 0.0,		 2.0 * dy)) * -1.0;

	return (sharpnessCol * effectRate) + (col * (1.0 - effectRate));
}