
cbuffer BillboardBuffer : register(b0)
{
	float3		billboardPosition;
	float		billboardAngle;
	float2		billboardScale;
	float2		textureUvOffset;
	float2		textureUvMulRate;
	float2		textureSize;
	float2		textureCenterRate;
	float2		pad;
	float4x4    viewMatrix;
	float4x4    projectionMatrix;
	float4		blendRate;
};

// 出力頂点構造体
struct PS_INPUT
{
	float2 texcoord : TEXCOORD0;
	float4 position : SV_POSITION;
};

Texture2D		TextureMapTexture : register(t0);
SamplerState	TextureMapSampler : register(s0);

// ピクセルシェーダ
float4 main(PS_INPUT input) : SV_Target
{
	return TextureMapTexture.Sample(TextureMapSampler, input.texcoord) * blendRate;
}