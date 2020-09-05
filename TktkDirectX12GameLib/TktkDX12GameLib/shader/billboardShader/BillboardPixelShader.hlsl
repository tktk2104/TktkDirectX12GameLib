
cbuffer BillboardMaterialBuffer : register(b0)
{
	float4 blendRate;
};

// �o�͒��_�\����
struct PS_INPUT
{
	float2 texcoord : TEXCOORD0;
	float4 position : SV_POSITION;
};

// �e�N�X�`��
Texture2D		TextureMapTexture : register(t0);
SamplerState	TextureMapSampler : register(s0);

// �s�N�Z���V�F�[�_
float4 main(PS_INPUT input) : SV_Target
{
	return TextureMapTexture.Sample(TextureMapSampler, input.texcoord) * blendRate;
}