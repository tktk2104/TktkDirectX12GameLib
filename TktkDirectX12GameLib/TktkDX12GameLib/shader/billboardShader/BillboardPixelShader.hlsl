
cbuffer BillboardMaterialBuffer : register(b0)
{
	float4 blendRate;
};

// 出力頂点構造体
struct PS_INPUT
{
	float2 texcoord : TEXCOORD0;
	float4 position : SV_POSITION;
};

// テクスチャ
Texture2D		TextureMapTexture : register(t0);
SamplerState	TextureMapSampler : register(s0);

// ピクセルシェーダ
float4 main(PS_INPUT input) : SV_Target
{
	return TextureMapTexture.Sample(TextureMapSampler, input.texcoord) * blendRate;
}