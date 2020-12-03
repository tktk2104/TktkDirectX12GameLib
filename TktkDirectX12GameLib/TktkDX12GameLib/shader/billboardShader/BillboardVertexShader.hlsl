
// �J�����̍s��̏��
cbuffer CameraBuffer : register(b0)
{
	float4x4    ViewMatrix;
	float4x4    ProjectionMatrix;
};

struct VS_INPUT
{
	float4 position				: POSITION;

	float3 billboardPosition	: BILLBOARDPOSITION;
	float  billboardAngle		: BILLBOARDANGLE;
	float2 billboardScale		: BILLBOARDSCALE;
	float2 textureUvOffset		: UVOFFSET;
	float2 textureUvMulRate		: UVMULRATE;
	float2 textureSize			: TEXTURESIZE;
	float2 textureCenterRate	: TEXTURECENTERRATE;
	float2 pad					: PAD;
	float4 blendRate			: BLENDRATE;
};

// �o�͒��_�\����
struct VS_OUTPUT
{
	float4 position		: SV_POSITION;
	float2 texcoord		: TEXCOORD0;
	float4 blendRate	: BLENDRATE;
};

// ���_�V�F�[�_�[
VS_OUTPUT main(VS_INPUT input)
{
	VS_OUTPUT output;

	output.position		= input.position;
	output.position.xy *= float2(1.0f, input.textureSize.y / input.textureSize.x);
	output.position.xy -= float2(input.textureCenterRate.x, input.textureCenterRate.y * (input.textureSize.y / input.textureSize.x));
	output.position.xy *= input.billboardScale;

	float2 rotate;
	rotate.x = output.position.x * cos(input.billboardAngle) - output.position.y * sin(input.billboardAngle);
	rotate.y = output.position.x * sin(input.billboardAngle) + output.position.y * cos(input.billboardAngle);

	output.position.xy = rotate;

	// �r���[�̋t�ϊ����s���i�r���[�ϊ���ɃJ�����̐��ʂ������j
	output.position.xyz = mul(output.position.xyz, (float3x3)ViewMatrix);
	output.position.xyz += input.billboardPosition;

	// �r���[�ϊ�
	output.position = mul(ViewMatrix, output.position);

	// �����ϊ�
	output.position = mul(ProjectionMatrix, output.position);

	output.texcoord.xy = ((input.position.xy * input.textureUvMulRate) + input.textureUvOffset);
	output.texcoord.y = 1.0 - output.texcoord.y;

	output.blendRate = input.blendRate;

	return output;
}

