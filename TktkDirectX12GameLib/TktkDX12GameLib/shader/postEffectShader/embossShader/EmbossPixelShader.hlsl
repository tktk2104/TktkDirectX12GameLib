
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

	/*
	�e�s�N�Z���̏d�݁i���S�����̃s�N�Z���j
	 2,  1,  0
	 1,  1, -1
	 0, -1, -2
	*/

	// ���͂W�s�N�Z���̐F�����̃s�N�Z���̐F�ɑ���
	float4 embossCol = float4(0.0, 0.0, 0.0, 0.0);
	embossCol += renderTargetTexture.Sample(renderTargetSampler, input.texcoord + float2(-2.0 * dx,	-2.0 * dy)) *  2.0;
	embossCol += renderTargetTexture.Sample(renderTargetSampler, input.texcoord + float2( 0.0,		-2.0 * dy));
	/* �E��͖��� */
	embossCol += renderTargetTexture.Sample(renderTargetSampler, input.texcoord + float2(-2.0 * dx,	 0.0));
	embossCol += col;
	embossCol += renderTargetTexture.Sample(renderTargetSampler, input.texcoord + float2( 2.0 * dx,	 0.0))		* -1.0;
	/* �����͖��� */
	embossCol += renderTargetTexture.Sample(renderTargetSampler, input.texcoord + float2( 0.0,		 2.0 * dy)) * -1.0;
	embossCol += renderTargetTexture.Sample(renderTargetSampler, input.texcoord + float2( 2.0 * dx,	 2.0 * dy)) * -2.0;

	return (embossCol * effectRate) + (col * (1.0 - effectRate));
}