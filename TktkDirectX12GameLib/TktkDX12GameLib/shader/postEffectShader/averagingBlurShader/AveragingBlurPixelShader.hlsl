
// �萔�o�b�t�@
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

	// ���͂W�s�N�Z���̐F�����̃s�N�Z���̐F�ɑ���
	float4 ret = float4(0.0, 0.0, 0.0, 0.0);
	ret += renderTargetTexture.Sample(renderTargetSampler, input.texcoord + float2(-2.0 * dx,	-2.0 * dy));
	ret += renderTargetTexture.Sample(renderTargetSampler, input.texcoord + float2( 0.0,		-2.0 * dy));
	ret += renderTargetTexture.Sample(renderTargetSampler, input.texcoord + float2( 2.0 * dx,	-2.0 * dy));
	ret += renderTargetTexture.Sample(renderTargetSampler, input.texcoord + float2(-2.0 * dx,	 0.0));
	ret += col;
	ret += renderTargetTexture.Sample(renderTargetSampler, input.texcoord + float2( 2.0 * dx,	 0.0));
	ret += renderTargetTexture.Sample(renderTargetSampler, input.texcoord + float2(-2.0 * dx,	 2.0 * dy));
	ret += renderTargetTexture.Sample(renderTargetSampler, input.texcoord + float2( 0.0,		 2.0 * dy));
	ret += renderTargetTexture.Sample(renderTargetSampler, input.texcoord + float2( 2.0 * dx,	 2.0 * dy));

	// ���͂̃s�N�Z���̕��ς��o��
	float4 blurCol = ret / 9.0;

	return (blurCol * effectRate) + (col * (1.0 - effectRate));
}