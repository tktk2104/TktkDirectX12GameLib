
// 定数バッファ
cbuffer ConstantBuffer : register(b0)
{
	float2 drawGameAreaSize;
	float2 screenSize;
};

struct VSInput
{
	float4 position	: POSITION;
};

struct VSOutput
{
	float2 texcoord : TEXCOORD0;
	float4 position : SV_POSITION;
};

VSOutput main(VSInput input)
{
	VSOutput output;

	output.position		= input.position;
	output.position.z	= 1.0;
	output.position.xy	*= drawGameAreaSize;
	//output.position.xy	-= drawGameAreaSize * 0.5;
	output.position.xy	+= (screenSize - drawGameAreaSize) * 0.5;
	output.position.xy	= output.position.xy * float2(2.0 / screenSize.x, 2.0 / -screenSize.y) + float2(-1.0, 1.0);
	output.texcoord.xy = input.position.xy;
	return output;
}