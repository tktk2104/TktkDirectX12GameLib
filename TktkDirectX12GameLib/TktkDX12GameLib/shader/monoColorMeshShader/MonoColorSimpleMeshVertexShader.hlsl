
// �J�����̍s��̏��
cbuffer CameraBuffer : register(b0)
{
	float4x4    ViewMatrix;
	float4x4    ProjectionMatrix;
};

// ���͒��_���
struct VS_INPUT
{
	float4		Position		: POSITION;
	float3		Normal			: NORMAL;
	float2		TexCoord		: TEXCOORD;
	int4		BlendIndices	: BLENDINDICES;
	float4		BlendWeight		: BLENDWEIGHT;
	float3		Tangent			: TANGENT;
	float3		Binormal		: BINORMAL;

	float4x4	WorldMatrix		: WORLDMATRIX;
	float4		AlbedoColor		: ALBEDOCOLOR;
	uint		InstanceId      : SV_InstanceID;
};

// �o�͒��_���
struct VS_OUTPUT
{
	float4 Position     : SV_POSITION;
	float4 AlbedoColor	: ALBEDOCOLOR;
};

VS_OUTPUT main(VS_INPUT Input)
{
	VS_OUTPUT Output;

	// �y���̒��_���W�̍��W�ϊ��z
	// �萔�o�b�t�@�Ŏ擾�������[���h�s����g���č��W�ϊ�����
	float4 WorldPosition = mul(Input.WorldMatrix, Input.Position);
	// �萔�o�b�t�@�Ŏ擾�����r���[�s����g���č��W�ϊ�����
	float4 ViewPosition = mul(ViewMatrix, WorldPosition);

	// �p�[�X�y�N�e�B�u��Ԃł̒��_���W���v�Z
	Output.Position = mul(ProjectionMatrix, ViewPosition);

	// �A���x�h�J���[�����̂܂ܓn��
	Output.AlbedoColor = Input.AlbedoColor;

	return Output;
}