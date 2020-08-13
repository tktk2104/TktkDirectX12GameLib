cbuffer ConstantBuffer : register(b0)
{
	float3x3 worldMatrix;
	float4 lineColor;
	float2 screenSize;
	float2 pad2;
};

struct PS_INPUT
{
	float4 position : SV_POSITION;
};

float4 main(PS_INPUT input) : SV_Target
{
	return lineColor;
}