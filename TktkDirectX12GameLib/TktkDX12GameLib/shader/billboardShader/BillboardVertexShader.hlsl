
cbuffer BillboardMaterialBuffer : register(b0)
{
	float4 blendRate;
};

cbuffer BillboardTransformBuffer : register(b0)
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
};

struct VS_INPUT
{
	float4 position : POSITION;
};

// 出力頂点構造体
struct VS_OUTPUT
{
	float2 texcoord : TEXCOORD0;
	float4 position : SV_POSITION;
};

// 頂点シェーダー
VS_OUTPUT main(VS_INPUT input)
{
	VS_OUTPUT output;

	output.position		= input.position;
	output.position.xy *= textureSize;
	output.position.xy -= float2(textureCenterRate.x * textureSize.x, textureCenterRate.y * textureSize.y);
	output.position.xy *= billboardScale;

	float2 rotate;
	rotate.x = output.position.x * cos(billboardAngle) - output.position.y * sin(billboardAngle);
	rotate.y = output.position.x * sin(billboardAngle) + output.position.y * cos(billboardAngle);

	output.position.xy = rotate;

	// ビューの逆変換を行う（ビュー変換後にカメラの正面を向く）
	output.position.xyz = mul(output.position.xyz, (float3x3)viewMatrix);
	output.position.xyz += billboardPosition;

	// ビュー変換
	output.position = mul(viewMatrix, output.position);

	// 透視変換
	output.position = mul(projectionMatrix, output.position);

	output.texcoord.xy = (input.position.xy * textureUvMulRate) + textureUvOffset;

	return output;
}

